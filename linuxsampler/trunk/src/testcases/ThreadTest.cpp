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


// WaitingThread

ThreadTest::WaitingThread::WaitingThread() : Thread(false, 0, -4) {
}

int ThreadTest::WaitingThread::Main() {
    while (true) condition.WaitIf(false);
}


// ThreadTest

// Check if Thread class actually deploys a thread
void ThreadTest::testThreadRunning() {
    dummythread.StartThread();
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(dummythread.wasRunning);
    CPPUNIT_ASSERT(dummythread.IsRunning());
}

// Check if SignalStopThread() method actually stops the thread
void ThreadTest::testSignalStopThread() {
    dummythread.SignalStopThread();
    usleep(40000); // wait 40ms
    CPPUNIT_ASSERT(!dummythread.IsRunning());
}

// Check if the thread can be relaunched
void ThreadTest::testRelaunchThread() {
    dummythread.StartThread();
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(dummythread.wasRunning);
    CPPUNIT_ASSERT(dummythread.IsRunning());
    dummythread.StopThread();
    usleep(25000); // wait 25ms
    dummythread.wasRunning = false;
    dummythread.StartThread();
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(dummythread.wasRunning);
    CPPUNIT_ASSERT(dummythread.IsRunning());
}

// Check if the StopThread() method actually stops the thread and doesn't freeze the calling thread which wants to stop it
void ThreadTest::testStopThread() {
    HelperThread* phelper = new HelperThread(&dummythread);
    phelper->StartThread(); // let the helper thread kill the dummy thread
    usleep(25000); // wait 25ms
    CPPUNIT_ASSERT(!dummythread.IsRunning());
    CPPUNIT_ASSERT(phelper->returnedFromDummyStop);
    if (phelper) delete phelper;
}

// Check if the thread can be stopped even when it's waiting for a condition
void ThreadTest::testThreadKillableWhenWaiting() {
    WaitingThread waitingthread;
    waitingthread.SignalStartThread();
    usleep(50000); // wait 50ms
    CPPUNIT_ASSERT(waitingthread.IsRunning());
    waitingthread.SignalStopThread();
    usleep(40000); // wait 40ms
    CPPUNIT_ASSERT(!waitingthread.IsRunning());
}
