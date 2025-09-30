#include "DebugAnimationPane.h"
#include "AbstractAnimation.h"
#include "imgui.h"
#include "FloatAnim.h"
#include "EasingCurve.h"
#include <vector>

void ImAnim::RenderDebugAnimationPane()
{
    // Static variables to preserve the state of the debug pane between frames.
    static float animatedValue = 0.0f;
    static ImAnim::FloatAnim animation(&animatedValue);

    static int selectedEasingIndex = static_cast<int>(ImAnim::EasingCurve::Type::OutQuad);
    static float duration = 1.0f;
    static float amplitude = 1.0f;
    static float period = 0.3f;
    static float overshoot = 1.70158f;
    static bool repeatAnimation = true;

    if(ImGui::Begin("Animation Debug Pane"))
    {
        // --- Top Section (Controls) ---

        if(ImGui::Combo(
               "Easing Function",
               &selectedEasingIndex,
               ImAnim::EasingCurve::TYPE_STRINGS,
               IM_ARRAYSIZE(ImAnim::EasingCurve::TYPE_STRINGS)
           ))
        {
            if(animation.isRunning())
            {
                animation.stop();
            }
        }

        ImGui::SliderFloat("Duration (s)", &duration, 0.1f, 5.0f, "%.2f");

        // --- Conditional Sliders for specific easing types ---
        const char* selectedName = ImAnim::EasingCurve::TYPE_STRINGS[selectedEasingIndex];
        if(strstr(selectedName, "Elastic") || strstr(selectedName, "Bounce"))
        {
            ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 2.0f);
        }
        if(strstr(selectedName, "Elastic"))
        {
            ImGui::SliderFloat("Period", &period, 0.1f, 1.0f);
        }
        if(strstr(selectedName, "Back"))
        {
            ImGui::SliderFloat("Overshoot", &overshoot, 0.0f, 5.0f);
        }

        ImGui::Checkbox("Repeat", &repeatAnimation);
        ImGui::Spacing();

        // --- Action Buttons ---
        ImGui::Columns(2, nullptr, false);

        if(ImGui::Button("Play Animation", ImVec2(-1, 0)))
        {
            animation.stop();

            animation.setStartValue(0.0f);
            animation.setEndValue(1.0f);
            animation.setDuration(duration);
            animation.setLoopCount(repeatAnimation ? -1 : 1);
            animation.setEasingCurve(
                static_cast<ImAnim::EasingCurve::Type>(selectedEasingIndex),
                amplitude,
                period,
                overshoot
            );

            animation.start();
        }

        ImGui::NextColumn();

        if(ImGui::Button("Stop", ImVec2(-1, 0)))
        {
            animation.stop();
        }

        ImGui::Columns(1);

        ImGui::Separator();
        ImGui::Spacing();

        // --- Bottom Section (Visualization) ---
        ImGui::Text("Easing Function Shape:");
        {
            ImAnim::EasingCurve curve(static_cast<ImAnim::EasingCurve::Type>(selectedEasingIndex));
            curve.setAmplitude(amplitude);
            curve.setPeriod(period);
            curve.setOvershoot(overshoot);

            std::vector<float> points;
            points.reserve(101);
            for(int i = 0; i <= 100; ++i)
            {
                points.push_back(static_cast<float>(curve.calculateValueForProgress(i / 100.0)));
            }
            ImGui::PlotLines(
                "##easing_graph",
                points.data(),
                (int)points.size(),
                0,
                nullptr,
                -0.5f,
                1.5f,
                ImVec2(ImGui::GetContentRegionAvail().x, 80)
            );
        }

        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Live Animation Progress:");
        ImGui::ProgressBar(animatedValue, ImVec2(-1.0f, 0.0f));
        ImGui::Text("Current Value: %.3f", animatedValue);
    }
    ImGui::End();

    animation.update();
}