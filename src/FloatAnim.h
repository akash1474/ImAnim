#pragma once

#include "AbstractAnimation.h"

namespace ImAnim
{

    /**
     * @brief Performs an animation on a single float value.
     */
    class FloatAnim : public ImAnim::AbstractAnimation
    {
      public:
        /**
         * FloatAnim constructor.
         * @param pValue A pointer to the float value that this animation will modify.
         * If nullptr, an internal float will be used, and the value
         * can be retrieved with getCurrentValue().
         */
        explicit FloatAnim(float* pValue = nullptr);

        /**
         * FloatAnim destructor.
         */
        virtual ~FloatAnim() = default;

        /**
         * @brief Sets the starting animation value.
         * @param fStartValue This animation's starting value.
         */
        void setStartValue(float fStartValue);

        /**
         * @brief Sets the ending animation value.
         * @param fEndValue This animation's ending value.
         */
        void setEndValue(float fEndValue);

        /**
         * @brief Returns the starting animation value.
         * @return This animation's starting value.
         */
        [[nodiscard]] float getStartValue() const;

        /**
         * @brief Returns the ending animation value.
         * @return This animation's ending value.
         */
        [[nodiscard]] float getEndValue() const;

        /**
         * @brief Returns the current animated value.
         * @return The current value of the animation, whether it's managed
         * internally or by an external pointer.
         */
        [[nodiscard]] float getCurrentValue() const;

      protected:
        /**
         * @brief Updates the associated float value based on the current
         * animation progress. This is called automatically by the update() method.
         * @param dProgress The current progress of the animation (a value from 0.0 to 1.0).
         */
        void updateValueForProgress(double dProgress) override;

      private:
        /// A pointer to the float value that is being animated. Can be nullptr.
        float* m_pValue;

        /// The internal float value, used when m_pValue is nullptr.
        float m_internalValue{ 0.0f };

        /// The starting value for the animation.
        float m_fStartValue{ 0.0f };

        /// The ending value for the animation.
        float m_fEndValue{ 0.0f };
    };

} // namespace ImAnim