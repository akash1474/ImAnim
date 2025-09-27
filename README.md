# ImAnim



A simple, Qt-style animation library for **ImGui** that uses easing functions to bring your UI to life.

## ✨ Features

- **Animate ImGui Properties**: Easily animate `ImVec2` and `ImVec4` values for positions, sizes, colors, and more.
- **Easing Functions**: A collection of standard easing curves (Linear, InOutQuad, etc.) to control animation acceleration.
- **Keyframe Support**: Define intermediate animation states between the start and end values.
- **Animation Groups**: Run animations in sequence or in parallel.
- **Looping & Duration**: Set animation duration and loop counts, including infinite loops.



## 🚀 Getting Started

To use ImAnim in your own project, simply copy the classes from this repository into your application's source code.



## 💡 Usage Examples

### Animating Text Color

Here’s a basic example of how to make text fade from white to red and loop forever. The animation is attached to an `ImVec4` variable that is then used by `ImGui::TextColored`.

```cpp
static ImVec4 vTextColor(1.0f, 1.0f, 1.0f, 1.0f);
static ImAnim::ImVec4Anim* pColorAnim = nullptr;

// Initialize and start the animation on the first frame
if (pColorAnim == nullptr) {
    // Create the animation and attach it to the ImVec4
    pColorAnim = new ImAnim::ImVec4Anim(&vTextColor);
    
    // Animate from white to red
    pColorAnim->setStartValue(ImVec4(1, 1, 1, 1));
    pColorAnim->setEndValue(ImVec4(1, 0, 0, 1));
    
    // Set animation properties
    pColorAnim->setDuration(1.0);      // Duration for a single loop (seconds)
    pColorAnim->setLoopCount(-1);      // Loop forever
    pColorAnim->setEasingCurve(ImAnim::EasingCurve::Type::Linear);
    pColorAnim->start();
} else {
    // On subsequent frames, update the animation
    pColorAnim->update();
}

ImGui::TextColored(vTextColor, "Colored Text");
```

> **Note:** To fade an object in or out, simply animate the alpha component of its color from `0.0` to `1.0` (fade in) or `1.0` to `0.0` (fade out).



### Animating Window Position with Keyframes

You can create more complex animations by defining **keyframes**. This example moves an ImGui window from left to right and then back to the start using a keyframe set at the halfway point (`0.5`).

```cpp
static ImVec2 vWinPos(20, 100);
static ImAnim::ImVec2Anim* pWinPosAnim = nullptr;

if (pWinPosAnim == nullptr) {
    // Create the animation and attach it to the ImVec2
    pWinPosAnim = new ImAnim::ImVec2Anim(&vWinPos);

    // Setup 3 keyframes: move from left to right, then back to the start
    pWinPosAnim->setStartValue(ImVec2(20, 100));          // Keyframe at 0.0
    pWinPosAnim->setKeyValueAt(0.5, ImVec2(400, 100));    // Keyframe at 50%
    pWinPosAnim->setEndValue(ImVec2(20, 100));            // Keyframe at 1.0
    
    // Set animation properties
    pWinPosAnim->setDuration(2.5);
    pWinPosAnim->setLoopCount(-1);
    pWinPosAnim->setEasingCurve(ImAnim::EasingCurve::Type::InOutQuad);
    pWinPosAnim->start();
} else {
    pWinPosAnim->update();
}

// Draw the window at the animated position
ImGui::SetNextWindowPos(vWinPos);
ImGui::Begin("Test Window");
ImGui::Text("Some text");
ImGui::End();
```

> **Note:** `setStartValue()` is a convenient alias for `setKeyValueAt(0.0, ...)`, and `setEndValue()` is an alias for `setKeyValueAt(1.0, ...)`.



### Grouping Animations

You can group animations to run them together, either one after another (**sequentially**) or at the same time (**in parallel**).



#### Sequential Animations

A `SequentialAnimationGroup` runs each animation in the order it was added. You can also add pauses between animations.

```cpp
// Create a group to run animations in a sequence
auto* pColorAnimGroup = new ImAnim::SequentialAnimationGroup();

// Animation 1: White to Red
auto* pColorAnim1 = new ImAnim::ImVec4Anim(&vText1Color);
pColorAnim1->setStartValue(ImVec4(1, 1, 1, 1));
pColorAnim1->setEndValue(ImVec4(1, 0, 0, 1));
pColorAnim1->setDuration(1.5);

// Animation 2: Red to Green
auto* pColorAnim2 = new ImAnim::ImVec4Anim(&vText2Color);
pColorAnim2->setStartValue(ImVec4(1, 0, 0, 1));
pColorAnim2->setEndValue(ImVec4(0, 1, 0, 1));
pColorAnim2->setDuration(1.5);

// A 2-second pause
auto* pPause = new ImAnim::PauseAnimation(2.0);

// Animation 3: Green to Blue
auto* pColorAnim3 = new ImAnim::ImVec4Anim(&vText3Color);
pColorAnim3->setStartValue(ImVec4(0, 1, 0, 1));
pColorAnim3->setEndValue(ImVec4(0, 0, 1, 1));
pColorAnim3->setDuration(1.5);

// Add the animations to the group
pColorAnimGroup->addAnimation(pColorAnim1);
pColorAnimGroup->addAnimation(pColorAnim2);
pColorAnimGroup->addAnimation(pPause);
pColorAnimGroup->addAnimation(pColorAnim3);

pColorAnimGroup->start();
```



#### Parallel Animations

A `ParallelAnimationGroup` starts all animations at the same time. The group is considered finished when its longest animation completes.

> See `testSequential.cpp` and `testParallel.cpp` in the repository for complete examples of animation groups.
