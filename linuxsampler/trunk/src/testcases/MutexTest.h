#ifndef __LS_MUTEXTEST_H__
#define __LS_MUTEXTEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// needed for sleep() and usleep() calls
#include <unistd.h>

// the Mutex class we want to test
#include "../common/Mutex.h"

// we need an additional thread to test the Mutex class
#include "../common/Thread.h"

class MutexTest : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(MutexTest);
    CPPUNIT_TEST(testLockAndUnlockBySingleThread);
    CPPUNIT_TEST(testLock);
    CPPUNIT_TEST(testUnlock);
    CPPUNIT_TEST(testDoubleLock);
    CPPUNIT_TEST_SUITE_END();

    private:
        class ConcurrentThread : public Thread {
            public:
                int resource;
                Mutex mutex;

                ConcurrentThread();
                int Main();
        };
    public:
        void setUp();
        void tearDown();

        void testLockAndUnlockBySingleThread();
        void testLock();
        void testUnlock();
        void testDoubleLock();
};

#endif // __LS_MUTEXTEST_H__
