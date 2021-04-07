#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <cassert>

namespace PattyEngine {
    template<class T> class Manager {
        public:
            // Manager constructor that does nothing by default.
            Manager() {}      
            // Virtual destructor that clears the map.            
            virtual ~Manager() {            
                for(auto t : this->map) {
                    delete t.second;
                }
                this->map.clear();
            }

            // Initializer for Manager, returns true by default.
            virtual bool init() { return true; }    
            // Kill the Manager, does nothing by default.        
            virtual bool kill() {}                          
            // Add a string/object pair to the map.
            virtual bool add(std::string name, T* obj) {
                map[name] = obj;
            }
            // Get the specific object given a string.
            virtual T* get(std::string name) {
                return map[name];
            }
            // Populate a list with pointers to all objects.
            virtual void getAll(std::list<T*>& allObjs) {
                for(auto& obj : map) {
                    allObjs.push_back(obj.second);
                }
            }
        protected:
            // Map that stores string/object pairs.
            std::unordered_map<std::string, T*> map;
    };
}