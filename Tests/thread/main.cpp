//
// Created by mohsen on 1/4/17.
//

#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex mutex;
std::condition_variable cv;

bool ready = false;

void bar() {
    ready = true;
    char *x = new char[INT32_MAX]{0};
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, nullptr);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, nullptr);
//    std::this_thread::sleep_for(std::chrono::seconds(5));
    cv.notify_all();
    while (true);
}

void foo() {
    std::thread *thread2 = new std::thread(bar);
    std::unique_lock<std::mutex> lck(mutex);
    pthread_cancel(thread2->native_handle());
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

int main(int argc, char **argv) {

    std::thread thread1(foo);
    thread1.join();
    std::this_thread::sleep_for(std::chrono::seconds(15));
    return 0;
}