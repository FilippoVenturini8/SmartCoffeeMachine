#ifndef __POT_IMPL__
#define __POT_IMPL__

#include "potentiometer.h"

class PotImpl: public Pot {

    public:

        PotImpl(int pin);

        int getValue();

    private:
        int pin;

};

#endif
