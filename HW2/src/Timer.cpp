#include "Timer.h"

Timer::Timer() {
    cout<<"Timer::thread function starting..."<<endl;

    timerThread = thread([=]()
    {
        while (true)
        {
            // Check whether, at least there is an runnable task, and main already running
            if ((timerVector.size()!=0) && running)
            {
                // Sleep a while for the nearest task
                auto sleeping_time = min_time();
                this_thread::sleep_for(sleeping_time);

                if(!running)
                    break;
                
                chrono::duration<double> time;
                unique_lock<mutex> ulock(mutex1);

                // Doing tasks
                switch(timerVector[currentTime].getTimerType()){
                    case 1:
                        timerVector[currentTime].getCallback()();
                        time = CLOCK::now() - timerVector[currentTime].getTimePoint();
                        timerVector.erase(timerVector.begin()+currentTime);

                        break;

                    case 2:
                        timerVector[currentTime].getCallback()();
                        time = (timerVector[currentTime].getNextPoint() + timerVector[currentTime].getPeriodms()) - CLOCK::now();
                        timerVector[currentTime].setNextPoint (CLOCK::now());

                        break;

                    case 3:
                        time = (timerVector[currentTime].getNextPoint() + timerVector[currentTime].getPeriodms()) - CLOCK::now();
                        
                        timerVector[currentTime].setNextPoint (CLOCK::now());

                        if (CLOCK::now() >= timerVector[currentTime].getTimePoint())
                            timerVector.erase(timerVector.begin() + currentTime);
                        else
                            timerVector[currentTime].getCallback()();

                        break;

                    case 4:
                        timerVector[currentTime].getCallback()();
                        time = (timerVector[currentTime].getNextPoint()  + timerVector[currentTime].getPeriodms()) - CLOCK::now();

                        if (timerVector[currentTime].getPredicateFunc()())
                            timerVector[currentTime].setNextPoint(CLOCK::now());
                        else
                            timerVector.erase(timerVector.begin() + currentTime);		

                        break;
                }
                
                // Check deadline miss
                if ((int)(time.count()*1000)>10)
                    cerr<<"Deadline miss"<<endl;

            }
            // Tasks already are not registered.
			else{
                if(!running)
                    break;
                else
                {
                    unique_lock<mutex> ulock(mutex1);
                    cv.wait(ulock,[&]{return cvFlag;});
                    cvFlag = false;
                }
            }
        }
    });
}

Timer::~Timer(){

    cout<<"Timer::thread function terminating..."<<endl;
    {
        unique_lock<mutex> ulock(mutex1);
        cvFlag = true;
        running = false;
        cv.notify_one();
        ulock.unlock();
    }
    timerThread.join();
    
}

void Timer::registerTimer(const Timepoint &tp, const TTimerCallback &cb){
        
        unique_lock<mutex> ulock(mutex1);
        auto last = CLOCK::now();

        timerVector.push_back(TimerEntity(last, tp, cb));
        cvFlag = true;
        cv.notify_one();
}
void Timer::registerTimer(const Millisecs & period, const TTimerCallback &cb){
        
        unique_lock<mutex> ulock(mutex1);
        auto last = CLOCK::now();

        timerVector.push_back(TimerEntity(last, period, cb));
        cvFlag = true;
        cv.notify_one();   	
}
void Timer::registerTimer(const Timepoint &tp, const Millisecs & period, const TTimerCallback &cb){
        unique_lock<mutex> ulock(mutex1);
        auto last = CLOCK::now();

        timerVector.push_back(TimerEntity(last, tp, period, cb)); 	
        cvFlag = true;
        cv.notify_one();	
}
void Timer::registerTimer(const TPredicate &pred, const Millisecs & period, const TTimerCallback &cb){
        unique_lock<mutex> ulock(mutex1);
        auto last = CLOCK::now();

        timerVector.push_back(TimerEntity(last, pred, period, cb));
        cvFlag = true;
        cv.notify_one();
}

chrono::duration<double> Timer::min_time(){
    auto now = CLOCK::now();
    chrono::duration<double> time; 
    double min = DOUBLE_MAX;	
    
    for (int i = 0; i < timerVector.size(); i++)
    {	
        if(timerVector[i].getTimerType() == 1)
            time  = timerVector[i].getTimePoint() - now; 
        
        else
            time  = (timerVector[i].getNextPoint() + timerVector[i].getPeriodms()) - now;	

        if(min > time.count()){	
            currentTime = i;
            min = time.count();
        }	
    }

    return chrono::duration<double>(min);
}
