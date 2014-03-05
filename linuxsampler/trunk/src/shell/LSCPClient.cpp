/*
 * LSCP Shell
 *
 * Copyright (c) 2014 Christian Schoenebeck
 *
 * This program is part of LinuxSampler and released under the same terms.
 */

#include "LSCPClient.h"

#include <strings.h>

LSCPClient::LSCPClient() :
    Thread(false, false, 1, -1),
    hSocket(-1), m_callback(NULL), m_errorCallback(NULL),
    m_multiLineExpected(false), m_multiLineComplete(false)
{
}

LSCPClient::~LSCPClient() {
    disconnect();
}

bool LSCPClient::connect(String host, int port) {
    m_lineBuffer.clear();
    m_lines.clear();
    // resolve given host name
    hostent* server = ::gethostbyname(host.c_str());
    if (!server) {
        std::cerr << "Error: Could not resolve host \"" << host << "\".\n";
        return false;
    }
    // create local TCP socket
    hSocket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (hSocket < 0) {
        std::cerr << "Error: Could not create local socket.\n";
        return false;
    }
    // TCP connect to server
    sockaddr_in addr;
    bzero((char*)&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char*)&addr.sin_addr.s_addr, server->h_length);
    addr.sin_port = htons(port);
    if (::connect(hSocket, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Error: Could not connect to host \"" << host << "\".\n";
        std::cerr << "Is linuxsampler running and listening on port " << port << " ?\n";
        disconnect();
        return false;
    }
    StartThread();
    return true; // success
}

void LSCPClient::disconnect() {
    if (hSocket >= 0) {
        StopThread();
        ::close(hSocket);
        hSocket = -1;
    }
}

bool LSCPClient::isConnected() const {
    return hSocket >= 0;
}

bool LSCPClient::send(char c) {
    String s;
    s += c;
    return send(s);
}

bool LSCPClient::send(String s) {
    if (!isConnected()) return false;
    int n = ::write(hSocket, &s[0], s.size());
    return n == s.size();
}

String LSCPClient::sendCommandSync(String s) {
    m_linesMutex.Lock();
    m_lines.clear();
    m_linesMutex.Unlock();

    m_sync.Set(true);
    if (!send(s + "\n")) return "";
    m_sync.WaitIf(true);

    m_linesMutex.Lock();
    String sResponse = m_lines.back();
    m_lines.clear();
    m_linesMutex.Unlock();

    return sResponse;
}

optional<String> LSCPClient::popLine() {
    String s;
    LockGuard guard(m_linesMutex);
    if (m_lines.empty()) return optional<String>::nothing;
    s = m_lines.front();
    m_lines.pop_front();
    //FIXME: this is incorrect when having multiple complete messages in the queue
    if (m_multiLineExpected && s.substr(0, 1) == ".")
        m_multiLineExpected = m_multiLineComplete = false;
    return s;
}

optional<String> LSCPClient::lookAheadLine(int index) {
    LockGuard guard(m_linesMutex);
    if (index < 0 || index >= m_lines.size())
        return optional<String>::nothing;
    std::list<String>::iterator it = m_lines.begin();
    for (int i = 0; i < index; ++i) ++it;
    String s = *it;
    return s;
}

bool LSCPClient::messageComplete() {
    if (!lineAvailable()) return false;
    LockGuard guard(m_linesMutex);
    if (!m_multiLineExpected) return true;
    return m_multiLineComplete;
}

bool LSCPClient::multiLine() {
    //FIXME: returns falsely "true" in case the first message is single-line response but there is already a multi-line response in the FIFO
    return m_multiLineExpected;
}

bool LSCPClient::lineAvailable() const {
    return !m_lines.empty(); // is thread safe
}

void LSCPClient::setCallback(Callback_t fn) {
    m_callback = fn;
}

void LSCPClient::setErrorCallback(Callback_t fn) {
    m_errorCallback = fn;
}

optional<String> LSCPClient::receiveLine() {
    if (!isConnected()) return optional<String>::nothing;
    for (char c; true; ) {
        int n = ::read(hSocket, &c, 1);
        if (n < 1) return optional<String>::nothing;
        if (c == '\r') continue;
        if (c == '\n') {
            String s = m_lineBuffer;
            m_lineBuffer.clear();
            return s;
        }
        //printf("->%c\n", c);
        m_lineBuffer += c;
    }
    return optional<String>::nothing;
}

int LSCPClient::Main() {
    static const String multiLineKey = LSCP_SHK_EXPECT_MULTI_LINE;
    while (true) {
        optional<String> pLine = receiveLine();
        if (pLine) {
            String s = *pLine;
            //printf("->line '%s'\n", s.c_str());
            m_linesMutex.Lock();
            if (s.substr(0, multiLineKey.length()) == multiLineKey) {
                m_multiLineExpected = true;
                m_multiLineComplete = false;
            } else {
                if (m_multiLineExpected && s.substr(0, 1) == ".") {
                    m_multiLineComplete = true;
                }
                m_lines.push_back(s);
            }
            m_linesMutex.Unlock();

            if (m_sync.GetUnsafe()) m_sync.Set(false);
            else if (m_callback) (*m_callback)(this);
        } else if (m_errorCallback) (*m_errorCallback)(this);
        TestCancel();
    }
    return 0; // just to avoid a warning with some old compilers
}
