#ifndef __LS_LSCPTEST_H__
#define __LS_LSCPTEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string>
#include <vector>

#include "../Sampler.h"
#include "../network/lscpserver.h"

using namespace std;

class LSCPTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(LSCPTest);
    CPPUNIT_TEST(printTestSuiteName);
    CPPUNIT_TEST(testLaunchLSCPServer);
    CPPUNIT_TEST(testConnectToLSCPServer);
    CPPUNIT_TEST(test_ADD_CHANNEL);
    CPPUNIT_TEST(test_GET_CHANNELS);
    CPPUNIT_TEST(test_REMOVE_CHANNEL);
    CPPUNIT_TEST(testShutdownLSCPServer);
    CPPUNIT_TEST_SUITE_END();

    private:
        bool launchLSCPServer();
        bool shutdownLSCPServer();

        bool connectToLSCPServer();
        bool closeConnectionToLSCPServer();

        void sendCommandToLSCPServer(string cmd);
        string receiveSingleLineAnswerFromLSCPServer();
        vector<string> receiveMultiLineAnswerFromLSCPServer();
        string receiveAnswerFromLSCPServer(string delimiter);
    public:
        void setUp();
        void tearDown();

        void printTestSuiteName();

        void testLaunchLSCPServer();
        void testConnectToLSCPServer();
        void test_ADD_CHANNEL();
        void test_GET_CHANNELS();
        void test_REMOVE_CHANNEL();
        void testShutdownLSCPServer();
};

#endif // __LS_LSCPTEST_H__
