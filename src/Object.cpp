#include "Object.hpp"

namespace PattyEngine {
    void Object::update() {
        glm::mat4 parentModelMatrix = parent != NULL ? parent->getModelMatrix() : glm::mat4(1.0f);
        model = parentModelMatrix * glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), scale);

        for(auto &child : children) child->update();
    }
}