#include "RenderCore/rcInput.hpp"
#include "RenderCore/rcInternal.hpp"

#include "RenderCore/core/rcWindow.hpp"

namespace rc
{
    int toGLFW(Key k)
    {
        switch (k)
        {
            case Key::Q: return GLFW_KEY_Q;
            case Key::W: return GLFW_KEY_W;
            case Key::E: return GLFW_KEY_E;
            case Key::R: return GLFW_KEY_R;
            case Key::T: return GLFW_KEY_T;
            case Key::Y: return GLFW_KEY_Y;
            case Key::U: return GLFW_KEY_U;
            case Key::I: return GLFW_KEY_I;
            case Key::O: return GLFW_KEY_O;
            case Key::P: return GLFW_KEY_P;
            case Key::A: return GLFW_KEY_A;
            case Key::S: return GLFW_KEY_S;
            case Key::D: return GLFW_KEY_D;
            case Key::F: return GLFW_KEY_F;
            case Key::G: return GLFW_KEY_G;
            case Key::H: return GLFW_KEY_H;
            case Key::J: return GLFW_KEY_J;
            case Key::K: return GLFW_KEY_K;
            case Key::L: return GLFW_KEY_L;
            case Key::Z: return GLFW_KEY_Z;
            case Key::X: return GLFW_KEY_X;
            case Key::C: return GLFW_KEY_C;
            case Key::V: return GLFW_KEY_V;
            case Key::B: return GLFW_KEY_B;
            case Key::N: return GLFW_KEY_N;
            case Key::M: return GLFW_KEY_M;

            case Key::Key_0: return GLFW_KEY_0;
            case Key::Key_1: return GLFW_KEY_1;
            case Key::Key_2: return GLFW_KEY_2;
            case Key::Key_3: return GLFW_KEY_3;
            case Key::Key_4: return GLFW_KEY_4;
            case Key::Key_5: return GLFW_KEY_5;
            case Key::Key_6: return GLFW_KEY_6;
            case Key::Key_7: return GLFW_KEY_7;
            case Key::Key_8: return GLFW_KEY_8;
            case Key::Key_9: return GLFW_KEY_9;

            case Key::Esc: return GLFW_KEY_ESCAPE;
            case Key::Tab: return GLFW_KEY_TAB;

            case Key::Left_Shift: return GLFW_KEY_LEFT_SHIFT;
            case Key::Right_Shift: return GLFW_KEY_RIGHT_SHIFT;

            case Key::Left_Control: return GLFW_KEY_LEFT_CONTROL;
            case Key::Right_Control: return GLFW_KEY_RIGHT_CONTROL;

            case Key::Left_Alt: return GLFW_KEY_LEFT_ALT;
            case Key::Right_Alt: return GLFW_KEY_RIGHT_ALT;

            case Key::Super: return GLFW_KEY_HOME;
            case Key::Space: return GLFW_KEY_SPACE;
            case Key::Return: return GLFW_KEY_ENTER;
            case Key::Backspace: return GLFW_KEY_BACKSPACE;
        }

        return 0;
    }

    namespace Input
    {
        bool IsKeyPressed(Key key)
        {
            return glfwGetKey(Internal::gWindow->getWindowHandle(), toGLFW(key)) == GLFW_PRESS;
        }

        bool IsKeyDown(Key key)
        {
            int k = toGLFW(key);

            return Internal::currentKeys[k] && !Internal::previousKeys[k];
        }

        bool IsKeyRelease(Key key)
        {
            int k = toGLFW(key);

            return !Internal::currentKeys[k] && Internal::previousKeys[k];
        }
    }
}