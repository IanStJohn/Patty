#pragma once

#include "Manager.hpp"
#include "Mesh.hpp"
#include "Object.hpp"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

namespace PattyEngine {
    class Model : public Object{
        public:
            Model(
                std::string name, 
                Object *parent = NULL,
                glm::vec3 position = glm::vec3(), 
                glm::vec3 scale = glm::vec3(1.0f), 
                glm::vec3 rotation = glm::vec3(),
                glm::vec4 rgba = glm::vec4(1.0f)
            ) : Object(name, parent, position, scale, rotation) {
                this->rgba = rgba;
            }
            ~Model() {}

            bool create(std::string meshName, const char *texImgPath);
            bool draw();
            void update();
            void handle(SDL_Event *e) {}

            glm::vec3 getPosition() { return position; }
            void setPosition(glm::vec3 position) { this->position = position; }
            glm::vec3 getScale() { return scale; }
            void setScale(glm::vec3 scale) { this->scale = scale; } 

        protected:
            std::string name;
            Mesh *mesh;
            glm::vec4 rgba;
            GLuint textureID;
    };
    class ModelManager : public Manager<Model> {
        public:
            ModelManager() {}
            bool create(std::string name, std::string meshName, std::string texImgPath, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::vec4 rgba = glm::vec4(1.0f), Object *parent = NULL);
    };
}