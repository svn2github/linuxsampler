#ifndef __LS_THREADTEST_H__
#define __LS_THREADTEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// needed for sleep() and usleep() calls
#include <unistd.h>

// the Thread class we want to test
#include "../common/Thread.h"

class ThreadTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(ThreadTest);
    CPPUNIT_TEST(testThreadRunning);
    CPPUNIT_TEST(testSignalStopThread);
    CPPUNIT_TEST(testRelaunchThread);
    CPPUNIT_TEST(testStopThread);
    CPPUNIT_TEST_SUITE_END();

    private:
        // this is our test implementation of the abstract base class Thread which we will use to test class Thread
        class DummyThread : public Thread {
            public:
                bool wasRunning; // this variable is false on startup and will be switched to true by the thread, so we can check if the thread actually runs

                DummyThread();
                int Main();
        } dummythread;

        // this is only a helper thread to avoid that the entire test case run hangs when we try to stop the dummy thread
        class HelperThread : public Thread {
            private:
                DummyThread* pDummyThread;
            public:
                bool returnedFromDummyStop;

                HelperThread(DummyThread* pDummyThread);
                int Main();
        };
    public:
        void setUp() {
        }

        void tearDown() {
        }

        void testThreadRunning();
        void testSignalStopThread();
        void testRelaunchThread();
        void testStopThread();
};

#endif // __LS_THREADTEST_H__
