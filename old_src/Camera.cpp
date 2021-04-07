#include "Camera.hpp"
#include "Game.hpp"

namespace PattyEngine {
    void Camera::update() {
        Object::update();

        Input* input = getGame()->getSceneManager()->getActiveScene()->getInput();
        Time* time = getGame()->getSceneManager()->getActiveScene()->getTime();

        glm::vec3 parentPos = parent != NULL ? glm::vec3(parent->getModelMatrix()[3].x,parent->getModelMatrix()[3].y,parent->getModelMatrix()[3].z) : glm::vec3();

        horizontalAngle += input->mouseSpeed * time->deltaTime * float(-input->mouseX);
        verticalAngle += input->mouseSpeed * time->deltaTime * float(-input->mouseY);
        direction = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
        right = glm::vec3(sin(horizontalAngle - 3.14f/2.0f), 0, cos(horizontalAngle - 3.14f/2.0f));
        up = glm::cross(right, direction);
        projection = glm::perspective(glm::radians(initialFoV), (float) getGame()->getScreenWidth() / (float) getGame()->getScreenHeight(), nearClippingPlane, farClippingPlane);
        view = glm::lookAt(position + parentPos, parentPos + position + direction, up);

        parent->setRotation(glm::vec3(-verticalAngle, horizontalAngle, 0.0));
    }
}