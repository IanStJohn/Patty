#pragma once

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <GL/glu.h>

#ifdef _WIN32
#undef main
#endif

#include <stdio.h>
#include <string>

#include "Mesh.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include "Input.hpp"
#include "Time.hpp"

namespace PattyEngine {
    class Game;
    Game* getGame();
    void setGame(Game* game);

    class Game {
        public:
            Game(int width = 1920, int height = 1080) {
                gWindow = NULL;
                SCREEN_WIDTH = width;
                SCREEN_HEIGHT = height;
            }
            virtual ~Game(){ close(); }
            virtual bool init(const std::string name);
            virtual bool initGL();
            virtual bool loadMedia();
            virtual void run();
            virtual void close();

            GLuint getProgramID() { return gProgramID; }
            SDL_Window* getWindow() { return gWindow; }
            int getScreenWidth() { return SCREEN_WIDTH; }
            int getScreenHeight() { return SCREEN_HEIGHT; }
            void setQuit(bool quit) { this->quit = quit; }

            SceneManager* getSceneManager() { return &sceneManager; }

        protected:
            // Constant Screen Dimensions
            int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;

            bool quit;
            
            SDL_Window* gWindow;    // Main Window
            SDL_GLContext gContext; // OpenGL Context

            // Graphics Program
            GLuint gProgramID = 0;
            
            SceneManager sceneManager;
            Scene *scene;
    };
}