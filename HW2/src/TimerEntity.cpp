	
 #include "TimerEntity.hpp"   
    
	TimerEntity::TimerEntity(const Timepoint &nextTp, const Timepoint &tp, const TTimerCallback &cb)
    :nextTp(nextTp), tp(tp), cb(cb), type(1)
    { }

    TimerEntity::TimerEntity(const Timepoint &nextTp, const Millisecs & period, const TTimerCallback &cb)
    :nextTp(nextTp), period(period), cb(cb), type(2)
    { }

    TimerEntity::TimerEntity(const Timepoint &nextTp, const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb):
    nextTp(nextTp), tp(tp), period(period), cb(cb), type(3)
    { }

    TimerEntity::TimerEntity(const Timepoint &nextTp, const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb)
    :nextTp(nextTp), p_func(pred), period(period), cb(cb), type(4)
    { }

    void TimerEntity::setTimePoint(const Timepoint &tp){
        this->tp = tp;
    }

    void TimerEntity::setNextPoint(const Timepoint &nextTp){
        this->nextTp = nextTp;
    }

    void TimerEntity::setPredicateFunc(const TPredicate &p_func){
        this->p_func = p_func;
    }

    void TimerEntity::setPeriodms(const Millisecs & period){
        this->period = period;
    }

    void TimerEntity::setCallback(const TTimerCallback &cb){
        this->cb = cb;
    }

    void TimerEntity::setTimerType(int type){
        this->type = type;
    }

    Timepoint TimerEntity::getTimePoint(){
        return tp;
    }

    Timepoint TimerEntity::getNextPoint(){
        return nextTp;
    }

    TPredicate TimerEntity::getPredicateFunc(){
        return p_func;
    }

    Millisecs TimerEntity::getPeriodms(){
        return period;
    }

    TTimerCallback TimerEntity::getCallback(){
        return cb;
    }

    int TimerEntity::getTimerType(){
        return type;
    }
	