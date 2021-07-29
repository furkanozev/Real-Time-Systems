#ifndef TIMERENTITY
#define TIMERENTITY

#include "ITimer.hpp"

using namespace std;

// Keeps timer task informations
class TimerEntity{
    private:
        Timepoint tp;
        Timepoint nextTp;
        TPredicate p_func;	
        Millisecs period;
        TTimerCallback cb;
        int type;	

    public:
        // For each type of timer task, create constructor
        TimerEntity(const Timepoint &nextTp, const Timepoint &tp, const TTimerCallback &cb);
        TimerEntity(const Timepoint &nextTp, const Millisecs & period, const TTimerCallback &cb);
        TimerEntity(const Timepoint &nextTp, const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb);
        TimerEntity(const Timepoint &nextTp, const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb);

        // Set and get operations
        void setTimePoint(const Timepoint &tp);
        void setNextPoint(const Timepoint &p_tp);
        void setPredicateFunc(const TPredicate &pred);
        void setPeriodms(const Millisecs & period);
        void setCallback(const TTimerCallback &cb);
        void setTimerType(int type);

        Timepoint getTimePoint();
        Timepoint getNextPoint();
        TPredicate getPredicateFunc();
        Millisecs getPeriodms();
        TTimerCallback getCallback();
        int getTimerType();
};

#endif