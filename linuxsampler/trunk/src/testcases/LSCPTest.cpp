#include "LSCPTest.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

CPPUNIT_TEST_SUITE_REGISTRATION(LSCPTest);

// Note:
// we have to declare all those variables which we want to use for all
// tests within this test suite static because there are side effects which
// occur on transition to the next test which would change the values of our
// variables
static Sampler*    pSampler    = NULL;
static LSCPServer* pLSCPServer = NULL;
static int         hSocket     = -1;
static FILE*       hServerIn   = NULL;

// split the multi line response string into the individual lines and remove the last (delimiter) line and the line feed characters in all lines
static vector<string> __ConvertMultiLineMessage(string msg) {
    vector<string> res;

    // erase the (dot) delimiter line
    static const string dotlinedelimiter = ".\r\n";
    string::size_type pos = msg.rfind(dotlinedelimiter);
    msg = msg.replace(pos, dotlinedelimiter.length(), "");

    // now split the lines
    static const string linedelimiter = "\r\n";
    while (true) {
        pos = msg.find(linedelimiter, 0);

        if (pos == string::npos) break; // if we're done

        // get the line without the line feed and put it at the end of the vector
        string line = msg.substr(0, pos);
        res.push_back(line);

        // remove the line from the input string
        pos += linedelimiter.length();
        msg = msg.substr(pos, msg.length() - pos);
    }

    return res;
}


// LSCPTest

// returns false if the server could not be launched
bool LSCPTest::launchLSCPServer() {
    const long timeout_seconds = 10; // we give the server max. 10 seconds to startup, otherwise we declare the startup as failed
    try {
        pSampler    = new Sampler;
        pLSCPServer = new LSCPServer(pSampler);
        pLSCPServer->StartThread();
        int res = pLSCPServer->WaitUntilInitialized(timeout_seconds);
        if (res < 0) throw;

        return true; // success
    }
    catch (...) {
        pSampler    = NULL;
        pLSCPServer = NULL;
        return false; // failure
    }
}

// returns false if the server could not be destroyed without problems
bool LSCPTest::shutdownLSCPServer() {
    try {
        pLSCPServer->StopThread();
        if (pLSCPServer) {
            delete pLSCPServer;
            pLSCPServer = NULL;
        }
        if (pSampler) {
            delete pSampler;
            pSampler = NULL;
        }
        return true; // success
    }
    catch (...) {
        return false; // failure
    }
}

// returns false if client connection to the LSCP server could not be established
bool LSCPTest::connectToLSCPServer() {
    const int iPort = LSCP_PORT; // LSCP server listening port (from lscpserver.h)
    hSocket = -1;

    hostent* pHost = gethostbyname("localhost");
    if (pHost == NULL) return false;

    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0) return false;

    sockaddr_in addr;
    memset((char*) &addr, 0, sizeof(sockaddr_in));
    addr.sin_family = pHost->h_addrtype;
    memmove((char*) &(addr.sin_addr), pHost->h_addr, pHost->h_length);
    addr.sin_port = htons((short) iPort);

    if (connect(hSocket, (sockaddr*) &addr, sizeof(sockaddr_in)) < 0) {
        close(hSocket);
        return false;
    }

    hServerIn = fdopen(hSocket, "r");

    return true;
}

bool LSCPTest::closeConnectionToLSCPServer() {
    //cout << "closeConnectionToLSCPServer()\n" << flush;
    hServerIn = NULL;
    if (hSocket >= 0) {
        close(hSocket);
        hSocket = -1;
    }
    return true;
}

// send a command to the LSCP server
void LSCPTest::sendCommandToLSCPServer(string cmd) {
    if (hSocket < 0) {
        cout << "sendCommandToLSCPServer() error: client socket not ready\n" << flush;
        return;
    }
    cmd += "\r\n";
    send(hSocket, cmd.c_str(), cmd.length(), 0);
}

// wait until LSCP server answers with a single line answer
string LSCPTest::receiveSingleLineAnswerFromLSCPServer() {
    string msg = receiveAnswerFromLSCPServer("\n");
    // remove the line feed at the end
    static const string linedelimiter = "\r\n";
    string::size_type pos = msg.rfind(linedelimiter);
    return msg.substr(0, pos);
}

// wait until LSCP server answers with a multi line answer
vector<string> LSCPTest::receiveMultiLineAnswerFromLSCPServer() {
    string msg = receiveAnswerFromLSCPServer("\n.\r\n");
    return __ConvertMultiLineMessage(msg);
}

// wait until LSCP server answers with the given \a delimiter token at the end
string LSCPTest::receiveAnswerFromLSCPServer(string delimiter) {
    if (!hServerIn) {
        cout << "receiveAnswerFromLSCPServer() error: client socket not ready\n" << flush;
        return "";
    }
    string message;
    char c;
    while ((c = fgetc(hServerIn)) != EOF) {
        message += c;
        string::size_type pos = message.rfind(delimiter); // ouch, but this is only a test case, right? ;)
        if (pos != string::npos) return message;
    }
    cout << "receiveAnswerFromLSCPServer() error: EOF reached\n" << flush;
    return "";
}



void LSCPTest::printTestSuiteName() {
    cout << "\b \nRunning LSCP Tests: " << flush;
}

void LSCPTest::setUp() {
}

void LSCPTest::tearDown() {
}



// Check if we can launch the LSCP Server (implies that there's no other instance running at the moment).
void LSCPTest::testLaunchLSCPServer() {
    //cout << "testLaunchLSCPServer()\n" << flush;
    CPPUNIT_ASSERT(launchLSCPServer());
}

// Check if we can connect a client connection to the LSCP server and close that connection without problems.
void LSCPTest::testConnectToLSCPServer() {
    //cout << "testConnectToLSCPServer()\n" << flush;
    sleep(1); // wait 1s
    CPPUNIT_ASSERT(connectToLSCPServer());
    sleep(2); // wait 2s
    CPPUNIT_ASSERT(closeConnectionToLSCPServer());
}

// Check "ADD CHANNEL" LSCP command.
void LSCPTest::test_ADD_CHANNEL() {
    sleep(1); // wait 1s
    CPPUNIT_ASSERT(connectToLSCPServer());

    sendCommandToLSCPServer("ADD CHANNEL");
    CPPUNIT_ASSERT(receiveSingleLineAnswerFromLSCPServer() == "OK[0]");

    sendCommandToLSCPServer("ADD CHANNEL");
    CPPUNIT_ASSERT(receiveSingleLineAnswerFromLSCPServer() == "OK[1]");

    sendCommandToLSCPServer("ADD CHANNEL");
    CPPUNIT_ASSERT(receiveSingleLineAnswerFromLSCPServer() == "OK[2]");
}

// Check "GET CHANNELS" LSCP command.
void LSCPTest::test_GET_CHANNELS() {
    sendCommandToLSCPServer("GET CHANNELS");
    string answer = receiveSingleLineAnswerFromLSCPServer();
    int initial_channels = atoi(answer.c_str());

    // add sampler channels and check if the count increases
    for (uint trial = 1; trial <= 3; trial++) {
        sendCommandToLSCPServer("ADD CHANNEL");
        answer = receiveSingleLineAnswerFromLSCPServer();
        sendCommandToLSCPServer("GET CHANNELS");
        answer = receiveSingleLineAnswerFromLSCPServer();
        int channels = atoi(answer.c_str());
        CPPUNIT_ASSERT(channels == initial_channels + trial);
    }
}

// Check "REMOVE CHANNEL" LSCP command.
void LSCPTest::test_REMOVE_CHANNEL() {
    // how many channels do we have at the moment?
    sendCommandToLSCPServer("GET CHANNELS");
    string answer = receiveSingleLineAnswerFromLSCPServer();
    int initial_channels = atoi(answer.c_str());

    // if there are no sampler channels yet, create some
    if (!initial_channels) {
        const uint create_channels = 4;
        for (uint i = 0; i < create_channels; i++) {
            sendCommandToLSCPServer("ADD CHANNEL");
            answer = receiveSingleLineAnswerFromLSCPServer();
        }
        initial_channels = create_channels;
    }

    // now remove the channels until there is no one left and check if we really need 'initial_channels' times to achieve that
    for (uint channels = initial_channels; channels; channels--) {
        sendCommandToLSCPServer("LIST CHANNELS");
        answer = receiveSingleLineAnswerFromLSCPServer();
        if (answer == "") CPPUNIT_ASSERT(false); // no sampler channel left already? -> failure

        // take the last channel number in the list which we will take to remove that sampler channel
        string::size_type pos = answer.rfind(",");
        string channel_to_remove = (pos != string::npos) ? answer.substr(pos + 1, answer.length() - (pos + 1)) /* "m,n,...,t */
                                                         : answer;                                   /* "k"        */

        //cout << " channel_to_remove: \"" << channel_to_remove << "\"\n" << flush;

        // remove that channel
        sendCommandToLSCPServer("REMOVE CHANNEL " + channel_to_remove);
        answer = receiveSingleLineAnswerFromLSCPServer();
        CPPUNIT_ASSERT(answer == "OK");
    }
    CPPUNIT_ASSERT(true); // success
}

// Check if we can shutdown the LSCP Server without problems.
void LSCPTest::testShutdownLSCPServer() {
    //cout << "testShutdownLSCPServer()\n" << flush;
    sleep(2); // wait 2s
    CPPUNIT_ASSERT(closeConnectionToLSCPServer());
    sleep(3); // wait 3s
    CPPUNIT_ASSERT(shutdownLSCPServer());
}
