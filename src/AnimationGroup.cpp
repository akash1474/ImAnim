#include "AnimationGroup.h"
#include <algorithm>

void ImAnim::AnimationGroup::addAnimation(AbstractAnimation* pAnimation)
{
    if(pAnimation != nullptr)
    {
        m_vecAnimations.push_back(pAnimation);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::AnimationGroup::clear() { m_vecAnimations.clear(); }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ImAnim::AbstractAnimation* ImAnim::AnimationGroup::getAnimationAt(int nIndex) const
{
    AbstractAnimation* pAnimation = nullptr;

    if((nIndex >= 0) && (nIndex < m_vecAnimations.size()))
    {
        pAnimation = m_vecAnimations[nIndex];
    }

    return pAnimation;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int ImAnim::AnimationGroup::getAnimationCount() const
{
    return static_cast<int>(m_vecAnimations.size());
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void ImAnim::AnimationGroup::insertAnimation(int nIndex, AbstractAnimation* pAnimation)
{
    if(pAnimation == nullptr)
    {
        return;
    }

    if(nIndex < 0)
    {
        nIndex = 0;
    }

    if(nIndex >= m_vecAnimations.size())
    {
        m_vecAnimations.push_back(pAnimation);
    }
    else
    {
        m_vecAnimations.insert(m_vecAnimations.begin() + nIndex, pAnimation);
    }
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int ImAnim::AnimationGroup::removeAnimation(AbstractAnimation* pAnimation)
{
    int nRemoveCount = 0;

    for(auto iter = m_vecAnimations.begin(); iter != m_vecAnimations.end();)
    {
        if(*iter == pAnimation)
        {
            iter = m_vecAnimations.erase(iter);
            nRemoveCount++;
        }
        else
        {
            ++iter;
        }
    }

    return nRemoveCount;
}


void ImAnim::AnimationGroup::start()
{
    if(m_nLoopCount == 0 || m_eAnimationState == State::Running)
    {
        return;
    }
    m_eAnimationState = State::Running;
    m_nCurrentLoop = 0;
    onStartAnimation();
}

void ImAnim::AnimationGroup::stop()
{
    if(m_eAnimationState != State::Stopped)
    {
        m_eAnimationState = State::Stopped;
        m_nCurrentLoop = 0;
        onStopAnimation();
    }
}
