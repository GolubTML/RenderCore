#pragma once

namespace rc
{
    enum class Key
    {
        // Letters
        Q, W, E, R, T, Y, U, I, O, P,
        A, S, D, F, G, H, J, K, L,
        Z, X, C, V, B, N, M,

        // Functional keys (maybe not all here)
        Esc, Tab, Left_Shift, Right_Shift,
        Left_Control, Right_Control, Left_Alt, Right_Alt,
        Super, Space, Return, Backspace,

        // Numbers
        Key_0, Key_1, Key_2, Key_3, Key_4, Key_5, Key_6, Key_7, Key_8, Key_9
    };

    enum class MouseButton
    {
        Left, Right, Middle
    };

    static int toGLFW(Key k);

    namespace Input
    {
        bool IsKeyPressed(Key key);
        bool IsKeyDown(Key key);
        bool IsKeyRelease(Key key);
    }
}