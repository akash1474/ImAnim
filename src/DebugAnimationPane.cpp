#include "DebugAnimationPane.h"
#include "imgui.h"
#include "FloatAnim.h"
#include "EasingCurve.h"
#include <vector>

void ImAnim::RenderDebugAnimationPane()
{
    static float animatedValue = 0.0f;
    static ImAnim::FloatAnim animation(&animatedValue);

    static int selectedEasingIndex = static_cast<int>(ImAnim::EasingCurve::Type::OutQuad);
    static float duration = 1.0f;
    static float amplitude = 1.0f;
    static float period = 0.3f;
    static float overshoot = 1.70158f;
    static bool repeatAnimation = true;
    static bool updated = false;

    if(ImGui::Begin("Animation Debug Pane"))
    {
        // --- Top Section (Controls) ---
        // Dropdown to select the easing function.
        if(ImGui::Combo(
               "Easing Function",
               &selectedEasingIndex,
               ImAnim::EasingCurve::TYPE_STRINGS,
               IM_ARRAYSIZE(ImAnim::EasingCurve::TYPE_STRINGS)
           ))
        {
            animation.stop();
        }

        // Slider to control the animation duration.
        if(ImGui::SliderFloat("Duration (s)", &duration, 0.1f, 5.0f, "%.2f"))
        {
            updated = true;
        }

        // --- Conditional Sliders ---
        const char* selectedName = ImAnim::EasingCurve::TYPE_STRINGS[selectedEasingIndex];
        if(strstr(selectedName, "Elastic") || strstr(selectedName, "Bounce"))
        {
            ImGui::SliderFloat("Amplitude", &amplitude, 0.0f, 2.0f);
            updated = true;
        }
        if(strstr(selectedName, "Elastic"))
        {
            ImGui::SliderFloat("Period", &period, 0.1f, 1.0f);
            updated = true;
        }
        if(strstr(selectedName, "Back"))
        {
            ImGui::SliderFloat("Overshoot", &overshoot, 0.0f, 5.0f);
            updated = true;
        }

        if(ImGui::Checkbox("Repeat", &repeatAnimation))
        {
            updated = true;
        }
        ImGui::Spacing();

        // Button to start the animation.
        if(ImGui::Button("Play Animation", ImVec2(-1, 0)) || updated)
        {
            animation.stop(); // Stop previous animation
            animation.setStartValue(0.0f);
            animation.setEndValue(1.0f);
            animation.setDuration(duration);

            // Set loop count based on the "Repeat" checkbox.
            // -1 means loop indefinitely. 1 means play once.
            animation.setLoopCount(repeatAnimation ? -1 : 1);

            animation.setEasingCurve(
                static_cast<ImAnim::EasingCurve::Type>(selectedEasingIndex),
                amplitude,
                period,
                overshoot
            );
            animation.start();
            updated = false;
        }

        ImGui::Separator();
        ImGui::Spacing();

        // --- Bottom Section (Visualization) ---
        ImGui::Text("Easing Function Shape:");
        // Graph the shape of the selected easing curve.
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

    // IMPORTANT: The animation object must be updated every frame for it to work.
    animation.update();
}
