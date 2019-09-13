#ifndef AAL01_TESTMANAGER_H_
#define AAL01_TESTMANAGER_H_

struct TimeMoment;

class TestManager {
public:
    using time_t = long long int;

    TestManager();
    virtual ~TestManager();

    virtual time_t timeTestResult();

protected:
    virtual void start();
    virtual void stop();

private:
    TimeMoment *startMoment;

    time_t deltaTime;
};

#endif // AAL01_TESTMANAGER_H_

