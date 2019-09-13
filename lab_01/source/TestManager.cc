#include "TestManager.h"

#include <chrono>

using nanosecs = std::chrono::duration<TestManager::time_t, std::nano>;

struct TimeMoment {
    std::chrono::high_resolution_clock::time_point value;
};

TestManager::TestManager() :
    startMoment(new TimeMoment),
    deltaTime(0)
{
}

TestManager::~TestManager() {
    delete startMoment;
}

TestManager::time_t TestManager::timeTestResult() {
    return deltaTime;
}

void TestManager::start() {
    startMoment->value = std::chrono::high_resolution_clock::now();
}

void TestManager::stop() {
    deltaTime = std::chrono::duration_cast<nanosecs>(std::chrono::high_resolution_clock::now() - startMoment->value).count();
}

