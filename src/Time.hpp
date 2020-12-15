#pragma once

#include <SDL.h>
#include <GL/glew.h>

namespace PattyEngine {
    class Time {
        public:
            void init();
            void update();

            GLint timeAttribute;
            Uint64 now, last;
            double deltaTime;
            float time;
    };
}