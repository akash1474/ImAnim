#include "PauseAnimation.h"

ImAnim::PauseAnimation::PauseAnimation(float fDurationInSecs)
{
    setDuration(fDurationInSecs);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::PauseAnimation::updateValueForProgress(double dProgress)
{
    // Do nothing
}
