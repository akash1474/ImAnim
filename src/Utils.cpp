#include "Utils.h"
#include <cmath>

bool ImAnim::Utils::nearlyEqual(double dValue1, double dValue2, double dTolerance)
{
    return fabs(dValue1 - dValue2) < dTolerance;
}
