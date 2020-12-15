#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

#include <SDL.h>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

namespace PattyEngine {
    class Object {
        public:
            Object( 
                std::string name, 
                Object *parent = NULL,
                glm::vec3 position = glm::vec3(), 
                glm::vec3 scale = glm::vec3(1.0f), 
                glm::vec3 rotation = glm::vec3()
            ) {
                this->name = name;
                this->position = position;
                this->scale = scale;
                this->rotation = rotation;
                this->parent = parent;
            }
            virtual ~Object() {}

            std::vector<Object*>* getChildren() { return &children; }
            Object* getParent() { return parent; }
            void setParent(Object* parent) { this->parent = parent; }
            glm::vec3 getPosition() { return position; }
            void setRotation(glm::vec3 rotation) { this->rotation = rotation; }
            glm::mat4 getModelMatrix() { return model; }
            virtual void update();
            virtual void handle(SDL_Event *e) = 0;
        protected:
            std::string name;
            glm::vec3 position;
            glm::vec3 scale;
            glm::vec3 rotation;
            glm::mat4 model;
            std::vector<Object*> children;
            Object *parent;
    };
    class ObjectManager {
        public:
            ObjectManager() {}
            ~ObjectManager() {}

            // Initializer for Manager, returns true by default.
            bool init() { return true; }    
            // Kill the Manager, does nothing by default.        
            bool kill() {}                          
            // Add a string/object pair to the map.
            bool add(std::string name, Object* obj) {
                map[name] = obj;
            }
            // Get the specific object given a string.
            Object* get(std::string name) {
                return map[name];
            }
            // Populate a list with pointers to all objects.
            void getAll(std::list<Object*>& allObjs) {
                for(auto& obj : map) {
                    allObjs.push_back(obj.second);
                }
            }
        protected:
            // Map that stores string/object pairs.
            std::unordered_map<std::string, Object*> map;
    };
}