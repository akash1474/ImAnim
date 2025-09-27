#include "FloatAnim.h"

namespace ImAnim
{

    FloatAnim::FloatAnim(float* pValue)
        : m_pValue(pValue)
    {
    }

    void FloatAnim::setStartValue(float fStartValue)
    {
        m_fStartValue = fStartValue;
    }

    void FloatAnim::setEndValue(float fEndValue)
    {
        m_fEndValue = fEndValue;
    }

    float FloatAnim::getStartValue() const
    {
        return m_fStartValue;
    }

    float FloatAnim::getEndValue() const
    {
        return m_fEndValue;
    }

    void FloatAnim::updateValueForProgress(double dProgress)
    {
        // Ensure the pointer is valid before trying to update the value.
        if (m_pValue)
        {
            // Linearly interpolate between the start and end values based on the progress.
            // The easing curve is handled by the parent AbstractAnimation class, which
            // modifies the dProgress value before it gets to this function.
            *m_pValue = m_fStartValue + (m_fEndValue - m_fStartValue) * static_cast<float>(dProgress);
        }
    }

} // namespace ImAnim