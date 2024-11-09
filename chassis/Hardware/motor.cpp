#include "motor.h"
using namespace Motor;
{
    
    void Motor_t::set_target(float target)
    {
        pid.target_update(target);
    }
} // namespace Motor;

