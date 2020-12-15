#pragma once

#include "Object.hpp"
#include "Model.hpp"

namespace PattyEngine {
    class Coin : public Object {
        public:
            Coin(
                std::string name, 
                Object *parent,
                glm::vec3 position = glm::vec3(), 
                glm::vec3 scale = glm::vec3(1.0f), 
                glm::vec3 rotation = glm::vec3()
            ) : Object(name, parent, position, scale, rotation) {
            }
            ~Coin() {}
            void create(std::string name);
            void update();
            void handle(SDL_Event *e) {}
        protected:
            Model *coinModel;
    };
}