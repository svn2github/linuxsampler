#include "MutexTest.h"

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(MutexTest);


// ConcurrentThread

MutexTest::ConcurrentThread::ConcurrentThread() : Thread(false, 0, -4) {
    resource = 0;
}

int MutexTest::ConcurrentThread::Main() {
    mutex.Lock();
    resource++;
    mutex.Unlock();
}


// MutexTest

void MutexTest::setUp() {
}

void MutexTest::tearDown() {
}

void MutexTest::testLockAndUnlockBySingleThread() {
    ConcurrentThread t;
    t.StartThread();
    usleep(200000); // wait 200ms
    CPPUNIT_ASSERT(t.resource == 1);
}

void MutexTest::testLock() {
    ConcurrentThread t;
    t.mutex.Lock();
    t.SignalStartThread();
    usleep(400000); // wait 400ms
    CPPUNIT_ASSERT(t.resource == 0);
    t.mutex.Unlock();
}

void MutexTest::testUnlock() {
    CPPUNIT_ASSERT(true);
}

void MutexTest::testDoubleLock() {
    CPPUNIT_ASSERT(true);
}
