#include "ThreadTest.h"

#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION(ThreadTest);


// DummyThread

ThreadTest::DummyThread::DummyThread() : Thread(false, 0, -4) {
    wasRunning = false;
}

int ThreadTest::DummyThread::Main() {
    wasRunning = true;
    while (true) sleep (1000);
}


// HelperThread

ThreadTest::HelperThread::HelperThread(DummyThread* pDummyThread) : Thread(false, 0, -4) {
    returnedFromDummyStop = false;
    this->pDummyThread = pDummyThread;
}

int ThreadTest::HelperThread::Main() {
    pDummyThread->StopThread();
    returnedFromDummyStop = true;
}


// ThreadTest

void ThreadTest::testThreadRunning() {
    dummythread.StartThread();
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(dummythread.wasRunning);
    CPPUNIT_ASSERT(dummythread.IsRunning());
}

void ThreadTest::testSignalStopThread() {
    dummythread.SignalStopThread();
    usleep(40000); // wait 40ms
    CPPUNIT_ASSERT(!dummythread.IsRunning());
}

void ThreadTest::testRelaunchThread() {
    dummythread.wasRunning = false;
    dummythread.StartThread();
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(dummythread.wasRunning);
    CPPUNIT_ASSERT(dummythread.IsRunning());
}

void ThreadTest::testStopThread() {
    HelperThread* phelper = new HelperThread(&dummythread);
    phelper->StartThread(); // let the helper thread kill the dummy thread
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(!dummythread.IsRunning());
    CPPUNIT_ASSERT(phelper->returnedFromDummyStop);
    if (phelper) delete phelper;
}
