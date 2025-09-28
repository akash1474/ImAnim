#include "EasingCurve.h"
#include "Easing.h"
#include <algorithm>

ImAnim::EasingCurve::EasingCurve(EasingCurve::Type eType) : m_eType(eType) {}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double ImAnim::EasingCurve::calculateValueForProgress(double dProgress)
{
    double dValue = dProgress;
    dProgress = std::clamp(dProgress, 0.0, 1.0);

    switch(m_eType)
    {
    case Type::Linear: dValue = ImAnim::Easing::easeNone(dProgress); break;
    case Type::InQuad: dValue = ImAnim::Easing::easeInQuad(dProgress); break;
    case Type::OutQuad: dValue = ImAnim::Easing::easeOutQuad(dProgress); break;
    case Type::InOutQuad: dValue = ImAnim::Easing::easeInOutQuad(dProgress); break;
    case Type::OutInQuad: dValue = ImAnim::Easing::easeOutInQuad(dProgress); break;
    case Type::InCubic: dValue = ImAnim::Easing::easeInCubic(dProgress); break;
    case Type::OutCubic: dValue = ImAnim::Easing::easeOutCubic(dProgress); break;
    case Type::InOutCubic: dValue = ImAnim::Easing::easeInOutCubic(dProgress); break;
    case Type::OutInCubic: dValue = ImAnim::Easing::easeOutInCubic(dProgress); break;
    case Type::InQuart: dValue = ImAnim::Easing::easeInQuart(dProgress); break;
    case Type::OutQuart: dValue = ImAnim::Easing::easeOutQuart(dProgress); break;
    case Type::InOutQuart: dValue = ImAnim::Easing::easeInOutQuart(dProgress); break;
    case Type::OutInQuart: dValue = ImAnim::Easing::easeOutInQuart(dProgress); break;
    case Type::InQuint: dValue = ImAnim::Easing::easeInQuint(dProgress); break;
    case Type::OutQuint: dValue = ImAnim::Easing::easeOutQuint(dProgress); break;
    case Type::InOutQuint: dValue = ImAnim::Easing::easeInOutQuint(dProgress); break;
    case Type::OutInQuint: dValue = ImAnim::Easing::easeOutInQuint(dProgress); break;
    case Type::InSine: dValue = ImAnim::Easing::easeInSine(dProgress); break;
    case Type::OutSine: dValue = ImAnim::Easing::easeOutSine(dProgress); break;
    case Type::InOutSine: dValue = ImAnim::Easing::easeInOutSine(dProgress); break;
    case Type::OutInSine: dValue = ImAnim::Easing::easeOutInSine(dProgress); break;
    case Type::InExpo: dValue = ImAnim::Easing::easeInExpo(dProgress); break;
    case Type::OutExpo: dValue = ImAnim::Easing::easeOutExpo(dProgress); break;
    case Type::InOutExpo: dValue = ImAnim::Easing::easeInOutExpo(dProgress); break;
    case Type::OutInExpo: dValue = ImAnim::Easing::easeOutInExpo(dProgress); break;
    case Type::InCirc: dValue = ImAnim::Easing::easeInCirc(dProgress); break;
    case Type::OutCirc: dValue = ImAnim::Easing::easeOutCirc(dProgress); break;
    case Type::InOutCirc: dValue = ImAnim::Easing::easeInOutCirc(dProgress); break;
    case Type::OutInCirc: dValue = ImAnim::Easing::easeOutInCirc(dProgress); break;
    case Type::InElastic:
        dValue = ImAnim::Easing::easeInElastic(dProgress, m_dAmplitude, m_dPeriod);
        break;
    case Type::OutElastic:
        dValue = ImAnim::Easing::easeOutElastic(dProgress, m_dAmplitude, m_dPeriod);
        break;
    case Type::InOutElastic:
        dValue = ImAnim::Easing::easeInOutElastic(dProgress, m_dAmplitude, m_dPeriod);
        break;
    case Type::OutInElastic:
        dValue = ImAnim::Easing::easeOutInElastic(dProgress, m_dAmplitude, m_dPeriod);
        break;
    case Type::InBack: dValue = ImAnim::Easing::easeInBack(dProgress, m_dOvershoot); break;
    case Type::OutBack: dValue = ImAnim::Easing::easeOutBack(dProgress, m_dOvershoot); break;
    case Type::InOutBack: dValue = ImAnim::Easing::easeInOutBack(dProgress, m_dOvershoot); break;
    case Type::OutInBack: dValue = ImAnim::Easing::easeOutInBack(dProgress, m_dOvershoot); break;
    case Type::InBounce: dValue = ImAnim::Easing::easeInBounce(dProgress, m_dAmplitude); break;
    case Type::OutBounce: dValue = ImAnim::Easing::easeOutBounce(dProgress, m_dAmplitude); break;
    case Type::InOutBounce:
        dValue = ImAnim::Easing::easeInOutBounce(dProgress, m_dAmplitude);
        break;
    case Type::OutInBounce:
        dValue = ImAnim::Easing::easeOutInBounce(dProgress, m_dAmplitude);
        break;
    }

    return dValue;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double ImAnim::EasingCurve::getAmplitude() const { return m_dAmplitude; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double ImAnim::EasingCurve::getOvershoot() const { return m_dOvershoot; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

double ImAnim::EasingCurve::getPeriod() const { return m_dPeriod; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ImAnim::EasingCurve::Type ImAnim::EasingCurve::getType() const { return m_eType; }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::EasingCurve::setAmplitude(double dAmplitude)
{
    if(dAmplitude >= 0.0)
    {
        m_dAmplitude = dAmplitude;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::EasingCurve::setOvershoot(double dOvershoot)
{
    if(dOvershoot >= 0.0)
    {
        m_dOvershoot = dOvershoot;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::EasingCurve::setPeriod(double dPeriod)
{
    if(dPeriod >= 0.0)
    {
        m_dPeriod = dPeriod;
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::EasingCurve::setType(ImAnim::EasingCurve::Type eType) { m_eType = eType; }
