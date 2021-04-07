#pragma once

#include "Object.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace PattyEngine {
    class Camera : public Object {
        public:
            Camera(
                std::string name, 
                Object *parent,
                float horizontalAngle = 3.14f,
                float verticalAngle = 0.0f,
                float initialFoV = 45.0f,
                float nearClippingPlane = 0.1f, 
                float farClippingPlane = 100.0f,
                glm::vec3 position = glm::vec3(), 
                glm::vec3 scale = glm::vec3(1.0f), 
                glm::vec3 rotation = glm::vec3()
            ) : Object(name, parent, position, scale, rotation) {
                this->horizontalAngle = horizontalAngle;
                this->verticalAngle = verticalAngle;
                this->initialFoV = initialFoV;
                this->nearClippingPlane = nearClippingPlane;
                this->farClippingPlane = farClippingPlane;
                projection = view = glm::mat4();
                direction = right = up = glm::vec3();
            }
            void update();
            void handle(SDL_Event *e) {}

            glm::mat4 getProjection() { return projection; }
            glm::vec3 getDirection() { return direction; }
            glm::vec3 getRight() { return right; }
            glm::mat4 getView() { return view; }
            void incrementPosition(glm::vec3 amount) { this->position += amount; }
        protected:
            glm::mat4 projection, view;
            glm::vec3 direction, right, up;
            float horizontalAngle = 3.14f;
            float verticalAngle = 0.0f;
            float initialFoV = 45.0f;
            float nearClippingPlane = 0.1f, farClippingPlane = 100.0f;
    };
}