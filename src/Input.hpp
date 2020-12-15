#pragma once

#include <SDL.h>

namespace PattyEngine {
    class Input {
        public:
            void init();
            void update();

            const Uint8 *keyState;
            float mouseSpeed = 0.01f;
            int mouseX, mouseY;
    };
}