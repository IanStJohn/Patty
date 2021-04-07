#include "Input.hpp"
#include "Game.hpp"

namespace PattyEngine {
    void Input::init() {
        SDL_StartTextInput();
        SDL_SetWindowGrab((getGame()->getWindow()), SDL_TRUE);
        SDL_ShowCursor(1);
        SDL_SetRelativeMouseMode(SDL_TRUE);
        keyState = SDL_GetKeyboardState(NULL); 
    }

    void Input::update() {
        mouseX = 0, mouseY = 0;
        SDL_GetRelativeMouseState(&mouseX, &mouseY);
    }
}