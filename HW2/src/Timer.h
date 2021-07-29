#ifndef TIMER
#define TIMER

#include "TimerEntity.hpp"
#include "ITimer.hpp"
#include <iostream>
#include <thread>
#include <queue> 
#include <mutex>
#include <condition_variable>
#include <atomic>

#define DOUBLE_MAX 1.79769e+308

using namespace std;


class Timer : public ITimer
{
  private:
      vector<TimerEntity> timerVector;

      thread timerThread;
      mutex mutex1;
      condition_variable cv;

      atomic<int> currentTime{0};
      atomic<bool> running{true};

      bool cvFlag = false;
      chrono::duration<double> min_time();

  public:
      Timer();
      ~Timer();

      void registerTimer(const Timepoint &tp, const TTimerCallback &cb);
      void registerTimer(const Millisecs & period, const TTimerCallback &cb);
      void registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
      void registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);
};



#endif