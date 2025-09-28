#include "ParallelAnimationGroup.h"

float ImAnim::ParallelAnimationGroup::getDuration() const
{
    float fDurationInSecs = 0.0F;

    // Traverse our animations and find the one with the maximum duration
    for(const auto& pAnimation : m_vecAnimations)
    {
        int nLoopCount = pAnimation->getLoopCount();
        float fCurDurationInSecs = pAnimation->getDuration();
        if((nLoopCount < 0) || (fCurDurationInSecs < 0.0F))
        {
            // The animation has an infinite time, so set the duration to -1
            // and break loop
            fDurationInSecs = -1.0F;
            break;
        }

        float fTotalDurationInSecs = (static_cast<float>(nLoopCount) * fCurDurationInSecs);
        if(fTotalDurationInSecs > fDurationInSecs)
        {
            // Save this duration as it is the current max duration
            fDurationInSecs = fTotalDurationInSecs;
        }
    }

    return fDurationInSecs;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::ParallelAnimationGroup::onStartAnimation()
{
    if(m_vecAnimations.empty())
    {
        // No animations so stop
        m_eAnimationState = State::Stopped;
        m_nCurrentLoop = 0;
        return;
    }

    // Start all our animations
    for(const auto& pAnimation : m_vecAnimations)
    {
        pAnimation->start();
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::ParallelAnimationGroup::onStopAnimation()
{
    // Make sure that all our animations are stopped
    for(const auto& pAnimation : m_vecAnimations)
    {
        pAnimation->stop();
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::ParallelAnimationGroup::update()
{
    if(m_eAnimationState != State::Running)
    {
        return;
    }

    // Update all our animations and check if any are still running
    bool bIsRunning = false;
    for(const auto& pAnimation : m_vecAnimations)
    {
        pAnimation->update();
        if(pAnimation->getState() == State::Running)
        {
            bIsRunning = true;
        }
    }

    if(!bIsRunning)
    {
        // Increment the loop
        m_nCurrentLoop++;
        if((m_nCurrentLoop >= m_nLoopCount) && (m_nLoopCount >= 0))
        {
            stop(); // Use the group's own stop method.
            return;
        }

        // Explicitly stop all children
        for(const auto& pAnimation : m_vecAnimations)
        {
            pAnimation->stop();
        }

        // Start all our animations since starting a new loop
        for(const auto& pAnimation : m_vecAnimations)
        {
            pAnimation->start();
        }
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::ParallelAnimationGroup::updateValueForProgress([[maybe_unused]] double dProgress) {}
