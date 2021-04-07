#include "Time.hpp"
#include "Game.hpp"

namespace PattyEngine {
    void Time::init() {
        last = 0;
        now = SDL_GetPerformanceCounter();
        deltaTime = 0;
        time = 0.0f;
        timeAttribute = glGetUniformLocation(getGame()->getProgramID(), "time");
    }

    void Time::update() {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
        time += .01f;
        glProgramUniform1f(getGame()->getProgramID(), timeAttribute, time);    
    }
}