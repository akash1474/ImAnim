#pragma once

namespace ImAnim
{
    /**
     * @brief Renders the ImGui debug pane for visualizing and testing animations.
     * * Call this function every frame within your main application loop where you
     * handle ImGui rendering. It is self-contained and manages its own state.
     */
    void RenderDebugAnimationPane();
}