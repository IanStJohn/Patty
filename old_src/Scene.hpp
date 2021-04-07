#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include "Manager.hpp"
#include "Mesh.hpp"
#include "Object.hpp"
#include "Model.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Camera.hpp"
#include "Player.hpp"

namespace PattyEngine {
    class Scene {
        public:
            Scene() {
                active = true;
                music = NULL;
            }
            bool isActive() { return active; }
            bool create(const char *filePath);
            void init();
            void update();
            MeshManager* getMeshManager() { return &meshManager; }
            ModelManager* getModelManager() { return &modelManager; }
            Input* getInput() { return &input; }
            Time* getTime() { return &time; }
            Camera* getCamera() { return camera; }
            SDL_Event* getEvent() { return &e; }

            void handle();
        protected:
            bool active;
            MeshManager meshManager;
            ModelManager modelManager;
            ObjectManager objectManager;
            SDL_Event e;
            Input input;
            Time time;
            Camera *camera;
            Player *player;
            Mix_Music *music;      // Game Music
            float speed = 3.0f; // 3 units / second
    };

    class SceneManager : public Manager<Scene> {
        public:
            Scene* getActiveScene();
        protected:
            
    };
}