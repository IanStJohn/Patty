#pragma once

#include "Manager.hpp"
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

#include <dirent.h>

namespace PattyEngine {
    class Mesh {
        public:
            Mesh() {
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);
                glGenBuffers(1, &vbo[0]);
                glGenBuffers(1, &vbo[1]);
                glGenBuffers(1, &ebo);
            }
            ~Mesh() {
                glDeleteBuffers(1, &ebo);
                glDeleteBuffers(1, &vbo[0]);
                glDeleteBuffers(1, &vbo[1]);
                glDeleteVertexArrays(1, &vao);
            }
            bool create(const char *filePath);
            bool draw();
            std::string getName() { return name; }
        protected:
            std::string name;

            std::vector<glm::vec3> vertices;
            std::vector<glm::vec2> uvs;
            std::vector<glm::vec3> normals;
            std::vector<GLuint> indices;

            GLuint vao = 0;
            GLuint vbo[3];
            GLuint ebo;
    };
    class MeshManager : public Manager<Mesh> {
        public:
            MeshManager() {}
            bool create(const char *filePath);
            bool createFromDir(const char *dirPath);
    };
}