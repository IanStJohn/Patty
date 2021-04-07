#include "Coin.hpp"

namespace PattyEngine {
    void Coin::update() {
        rotation += glm::vec3(1.0, 0.0, 0.0);

        glm::mat4 parentModelMatrix = parent != NULL ? parent->getModelMatrix() : glm::mat4(1.0f);
        model = parentModelMatrix * glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), scale);

        for(auto &child : children) child->update();
    }

    void Coin::create(std::string name) {
        coinModel = new Model(name, this, glm::vec3(), glm::vec3(1.0f), glm::vec3(), glm::vec4(1.0f));
        coinModel->create("Coin", "images/uvtemplate.bmp");
        this->children.push_back(coinModel);
    }
}