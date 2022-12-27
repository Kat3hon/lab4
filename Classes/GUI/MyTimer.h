#include "../GameLogic/ITimer.h"

class MyTimer: public ITimer {
    [[nodiscard]] float getCurrentTime() const override {
        return 1;
    }
};

