#pragma once

#include "Object.hpp"
#include "Model.hpp"

namespace PattyEngine {
    class Player : public Object {
        public:
            Player(
                std::string name, 
                Object *parent,
                glm::vec3 position = glm::vec3(), 
                glm::vec3 scale = glm::vec3(1.0f), 
                glm::vec3 rotation = glm::vec3()
            ) : Object(name, parent, position, scale, rotation) {

            }
            ~Player() {}
            void create();
            void update();
            void handle(SDL_Event *e);
        protected:
            float speed = 5.0;

            Model *timeBob;
            glm::vec4 timeRGBA;
    };
}