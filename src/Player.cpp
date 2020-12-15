#include "Player.hpp"
#include "Game.hpp"

namespace PattyEngine {
    void Player::update() {
        glm::mat4 parentModelMatrix = parent != NULL ? parent->getModelMatrix() : glm::mat4(1.0f);
        model = parentModelMatrix * glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), scale);

        for(auto &child : children) child->update();
    }

    void Player::handle(SDL_Event *e) {
        if (e->type == SDL_TEXTINPUT) {
            Scene *scene = getGame()->getSceneManager()->getActiveScene();
            Camera *camera = scene->getCamera();
            Time *time = scene->getTime();
            Input *input = scene->getInput();

            if(input->keyState[SDL_SCANCODE_W]) position += camera->getDirection() * ((float)time->deltaTime) * speed;
            if(input->keyState[SDL_SCANCODE_S]) position -= camera->getDirection() * ((float)time->deltaTime) * speed;
            if(input->keyState[SDL_SCANCODE_D]) position += camera->getRight() * ((float)time->deltaTime) * speed;
            if(input->keyState[SDL_SCANCODE_A]) position -= camera->getRight() * ((float)time->deltaTime) * speed;

            timeBob->draw();
        }
    }

    void Player::create() {
        timeRGBA = glm::vec4(0.0, 1.0, 0.0, 0.5);
        timeBob = new Model("time_bob", this, glm::vec3(-.2, .1, .5), glm::vec3(.05,.05,.05), glm::vec3(90.0,0.0,0.0), timeRGBA);
        timeBob->create("Sphere", "images/white.bmp");
        this->children.push_back(timeBob);
    }
}