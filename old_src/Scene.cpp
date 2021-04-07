#include "Scene.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Coin.hpp"

namespace PattyEngine {
    bool Scene::create(const char *filePath) {
        FILE* file;
        bool success = true;

        if((file = fopen(filePath, "r")) == NULL) return false;
        while(1) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if(res == EOF) return success;
            if(strcmp(lineHeader, "m_dir") == 0) {
                char meshDir[128];
                fscanf(file, "%s", meshDir);
                if(!meshManager.createFromDir(meshDir)) success = false;
            } else if(strcmp(lineHeader, "music") == 0) {
                char musicFilepath[128];
                fscanf(file, "%s\n", musicFilepath);
		        music = Mix_LoadMUS(musicFilepath);
            } else if(strcmp(lineHeader, "m") == 0) {
                glm::vec3 position, scale, rotation;
                glm::vec4 rgba;
                char name[128], parentName[128], meshName[128], texPath[128];
                fscanf(file, "%s %s %s %s p(%f %f %f) s(%f %f %f) r(%f %f %f) rgba(%f %f %f %f)\n", 
                    name, parentName, meshName, texPath,
                    &position.x, &position.y, &position.z, 
                    &scale.x, &scale.y, &scale.z,
                    &rotation.x, &rotation.y, &rotation.z,
                    &rgba.x, &rgba.y, &rgba.z, &rgba.w
                );
                if(!modelManager.create(name, meshName, texPath, position, scale, rotation, rgba)) success = false;
                if(strcmp(parentName, "-") == 0) {
                    objectManager.add(name, modelManager.get(name));
                } else {
                    objectManager.get(parentName)->getChildren()->push_back(modelManager.get(name));
                    modelManager.get(name)->setParent(objectManager.get(parentName));
                }
            } else if(strcmp(lineHeader, "c") == 0) {
                char name[128], parentName[128];
                glm::vec3 position, scale, rotation;
                float horiAng, vertAng, initFoV, nClipPlane, fClipPlane;
                fscanf(file, "%s %s p(%f %f %f) s(%f %f %f) r(%f %f %f) %f %f %f %f %f\n", 
                    name, parentName, 
                    &position.x, &position.y, &position.z, 
                    &scale.x, &scale.y, &scale.z,
                    &rotation.x, &rotation.y, &rotation.z,
                    &horiAng, &vertAng, 
                    &initFoV, &nClipPlane, &fClipPlane
                );
                camera = new Camera(name, strcmp(parentName, "-") != 0 ? objectManager.get(parentName) : NULL, horiAng, vertAng, initFoV, nClipPlane, fClipPlane, position, scale, rotation);
                if(strcmp(parentName, "-") != 0) objectManager.get(parentName)->getChildren()->push_back(camera);
            } else if(strcmp(lineHeader, "p") == 0) {
                char name[128], parentName[128];
                glm::vec3 position, scale, rotation;
                fscanf(file, "%s %s p(%f %f %f) s(%f %f %f) r(%f %f %f)\n", 
                    name, parentName, 
                    &position.x, &position.y, &position.z, 
                    &scale.x, &scale.y, &scale.z,
                    &rotation.x, &rotation.y, &rotation.z
                );
                player = new Player(name, NULL, position, scale, rotation);
                objectManager.add(name, player);
                player->create();
            } else if(strcmp(lineHeader, "coin") == 0) {
                char name[128], parentName[128];
                glm::vec3 position, scale, rotation;
                fscanf(file, "%s %s p(%f %f %f) s(%f %f %f) r(%f %f %f)\n", 
                    name, parentName, 
                    &position.x, &position.y, &position.z, 
                    &scale.x, &scale.y, &scale.z,
                    &rotation.x, &rotation.y, &rotation.z
                );
                Coin *coin = new Coin(name, NULL, position, scale, rotation);
                objectManager.add(name, coin);
                coin->create(name);
            } else if(strcmp(lineHeader, "#") == 0) {

            }
        }
    }

    void Scene::init() {
        if(music != NULL) Mix_FadeInMusic( music, -1, 5000);
        input.init();
        time.init();
    }

    void Scene::handle() {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT || input.keyState[SDL_SCANCODE_ESCAPE]) getGame()->setQuit(true);
            else if(e.type == SDL_TEXTINPUT) {
                std::list<Object *> objects;
                objectManager.getAll(objects);
                for(auto &object : objects) object->handle(&e);
            }
        }
    }

    void Scene::update() {
        time.update();
        input.update();

        handle();

        std::list<Object *> objects;
        objectManager.getAll(objects);
        for(auto &object : objects) object->update();
    }

    Scene* SceneManager::getActiveScene() {
        for(auto & m :  this->map) {
            Scene *s = (Scene *)m.second;
            if(s->isActive()) return s;
        }
        return NULL; //nothing found, all inactive?
    }
}