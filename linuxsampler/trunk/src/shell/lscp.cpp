/*
 * LSCP Shell
 *
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * This program is part of LinuxSampler and released under the same terms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "LSCPClient.h"
#include "KeyboardReader.h"
#include "TerminalCtrl.h"
#include "CFmt.h"
#include "CCursor.h"

#include "../common/global.h"
#include "../common/Condition.h"

#define LSCP_DEFAULT_HOST "localhost"
#define LSCP_DEFAULT_PORT 8888

using namespace std;
using namespace LinuxSampler;

static LSCPClient g_client;
static KeyboardReader g_keyboardReader;
static Condition g_todo;

static void printUsage() {
    cout << "lscp - The LinuxSampler Control Protocol (LSCP) Shell." << endl;
    cout << endl;
    cout << "Usage: lscp [-h HOSTNAME] [-p PORT]" << endl;
    cout << endl;
    cout << "   -h  Host name of LSCP server (default \"" << LSCP_DEFAULT_HOST << "\")." << endl;
    cout << endl;
    cout << "   -p  TCP port number of LSCP server (default " << LSCP_DEFAULT_PORT << ")." << endl;
    cout << endl;
}

// Called by the network reading thread, whenever new data arrived from the
// network connection.
static void onLSCPClientNewInputAvailable(LSCPClient* client) {
    g_todo.Set(true);
}

// Called by the keyboard reading thread, whenever a key stroke was received.
static void onNewKeyboardInputAvailable(KeyboardReader* reader) {
    g_todo.Set(true);
}

int main(int argc, char *argv[]) {
    String host = LSCP_DEFAULT_HOST;
    int port    = LSCP_DEFAULT_PORT;

    // parse command line arguments
    for (int i = 0; i < argc; ++i) {
        String s = argv[i];
        if (s == "-h" || s == "--host") {
            if (++i >= argc) {
                printUsage();
                return -1;
            }
            host = argv[i];
        } else if (s == "-p" || s == "--port") {
            if (++i >= argc) {
                printUsage();
                return -1;
            }
            port = atoi(argv[i]);
            if (port <= 0) {
                cerr << "Error: invalid port argument \"" << argv[i] << "\"\n";
                return -1;
            }
        } else if (s[0] == '-') { // invalid / unknown command line argument ...
            printUsage();
            return -1;
        }
    }

    // try to connect to the sampler's LSCP server and start a thread for
    // receiving incoming network data from the sampler's LSCP server
    g_client.setCallback(onLSCPClientNewInputAvailable);
    if (!g_client.connect(host, port)) return -1;
    String sResponse = g_client.sendCommandSync("SET SHELL INTERACT 1");
    if (sResponse.substr(0, 2) != "OK") {
        cerr << "Error: sampler too old, it does not support shell instructions\n";
        return -1;
    }

    // start a thread for reading from the local text input keyboard
    // (keyboard echo will be disabled as well to have a clean control on what
    // is appearing on the screen)
    g_keyboardReader.setCallback(onNewKeyboardInputAvailable);
    g_keyboardReader.startReading();
    
    // main thread's loop
    while (true) {
        // sleep until either new data from the network or from keyboard arrived
        g_todo.WaitIf(false);
        // immediately unset the condition variable and unlock it
        g_todo.Set(false);
        g_todo.Unlock();

        // did network data arrive?
        while (g_client.messageComplete()) {
            String line = *g_client.popLine();
            //printf("line '%s'\n", line.c_str());
            if (line.substr(0,4) == "SHU:") {
                int code = 0, n = 0;
                int res = sscanf(line.c_str(), "SHU:%d:%n", &code, &n);
                if (res >= 1) {                    
                    String s = line.substr(n);

                    String key = LSCP_SHK_GOOD_FRONT;
                    size_t i = s.find(key);
                    String sGood = s.substr(0, i);
                    String sBad  = s.substr(i + key.length());
                    //printf("line '%s' good='%s' bad='%s'\n", line.c_str(), sGood.c_str(), sBad.c_str());

                    CCursor cursor = CCursor::now();
                    cursor.toColumn(0);
                    cursor.clearLine();

                    CFmt cfmt;
                    if (code == LSCP_SHU_COMPLETE) cfmt.bold().green();
                    else cfmt.bold().white();
                    cout << sGood << flush;
                    cfmt.reset().red();
                    cout << sBad << flush;
                }
            } else if (line.substr(0,2) == "OK") { // single-line response expected ...
                cout << endl << flush;
                CFmt cfmt;
                cfmt.green();
                cout << line.substr(0,2) << flush;
                cfmt.reset();
                cout << line.substr(2) << endl << flush;
            } else if (line.substr(0,3) == "WRN") { // single-line response expected ...
                cout << endl << flush;
                CFmt cfmt;
                cfmt.yellow();
                cout << line.substr(0,3) << flush;
                cfmt.reset();
                cout << line.substr(3) << endl << flush;
            } else if (line.substr(0,3) == "ERR") { // single-line response expected ...
                cout << endl << flush;
                CFmt cfmt;
                cfmt.bold().red();
                cout << line.substr(0,3) << flush;
                cfmt.reset();
                cout << line.substr(3) << endl << flush;
            } else if (g_client.multiLine()) { // multi-line response expected ...
                cout << endl << flush;
                while (true) {                   
                   cout << line << endl << flush;
                   if (line.substr(0, 1) == ".") break;
                   if (!g_client.lineAvailable()) break;
                   line = *g_client.popLine();
                }
            } else {
                cout << endl << line << endl << flush;
            }
        }

        // did keyboard input arrive?
        while (g_keyboardReader.charAvailable()) {
            char c = g_keyboardReader.popChar();

            CFmt cfmt;
            cfmt.white();
            //std::cout << c << "(" << int(c) << ")" << std::endl << std::flush;
            if (c == KBD_BACKSPACE) {
                cout << "\b \b" << flush;
                c = '\b';
            } else if (c != '\n') { // don't apply RETURN stroke yet, since the typed command might still be corrected by the sampler
                cout << c << flush;
            }

            g_client.send(c);
        }
    }

    return 0;
}
