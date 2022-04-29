#ifndef __PIR_IMPL__
#define __PIR_IMPL__

#include "pir.h"

class PirImpl: public Pir{
    public:
        PirImpl(int pin);
        bool isDetected();
        bool isReady();
    private:
        int pin;
        long initTime;
};

#endif
