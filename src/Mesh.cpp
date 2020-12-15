#include "Game.hpp"
#include "Mesh.hpp"
#include <string.h>
#include <glm/glm.hpp>

namespace PattyEngine {
    // Returns true iif v1 can be considered equal to v2
    bool is_near(float v1, float v2){
        return fabs( v1-v2 ) < 0.01f;
    }

    // Searches through all already-exported vertices
    // for a similar one.
    // Similar = same position + same UVs + same normal
    bool getSimilarVertexIndex( glm::vec3 & in_vertex, glm::vec2 & in_uv, glm::vec3 & in_normal, 
                                std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals,
                                unsigned short & result 
    ){
        // Lame linear search
        for ( unsigned int i=0; i<out_vertices.size(); i++ ){
            if (
                is_near( in_vertex.x , out_vertices[i].x ) &&
                is_near( in_vertex.y , out_vertices[i].y ) &&
                is_near( in_vertex.z , out_vertices[i].z ) &&
                is_near( in_uv.x     , out_uvs     [i].x ) &&
                is_near( in_uv.y     , out_uvs     [i].y ) //&&
                // is_near( in_normal.x , out_normals [i].x ) &&
                // is_near( in_normal.y , out_normals [i].y ) &&
                // is_near( in_normal.z , out_normals [i].z )
            ){
                result = i;
                return true;
            }
        }
        // No other vertex could be used instead.
        // Looks like we'll have to add it to the VBO.
        return false;
    }

    bool Mesh::create(const char *filePath) {
        std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices, temp_normals, in_vertices, in_normals;
        std::vector<glm::vec2> temp_uvs, in_uvs;
        FILE* file;

        if((file = fopen(filePath, "r")) == NULL) return false;
        while(1) {
            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if(res == EOF) break;

            if(strcmp(lineHeader, "n") == 0) {
                char str[128];
                fscanf(file, "%s", str);
                this->name = str;
                glm::vec3 g;
            } else if(strcmp(lineHeader, "v") == 0) {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            } else if(strcmp(lineHeader, "vt") == 0) {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y);
                temp_uvs.push_back(uv);
            } else if(strcmp(lineHeader, "vn") == 0) {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
                temp_vertices.push_back(normal);
            } else if(strcmp(lineHeader, "f") == 0) {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(
                    file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
                    &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
                    &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
                    &vertexIndex[2], &uvIndex[2], &normalIndex[2]
                );
                if(matches != 9) return false;
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            }
        }

        // Convert indexing from 1 to 0...
        for(unsigned int i=0; i<vertexIndices.size(); i++) {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            in_vertices.push_back(vertex);
        }
        for(unsigned int i=0; i<uvIndices.size(); i++) {
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uv = temp_uvs[uvIndex-1];
            in_uvs.push_back(uv);
        }
        // for(unsigned int i=0; i<normalIndices.size(); i++) {
        //     unsigned int normalIndex = normalIndices[i];
        //     glm::vec3 normal = temp_normals[normalIndex-1];
        //     in_normals.push_back(normal);
        // }

        // For each input vertex
        for ( unsigned int i=0; i<in_vertices.size(); i++ ){

            // Try to find a similar vertex in out_XXXX
            unsigned short index;
            bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i], vertices, uvs, normals, index);

            if ( found ){ // A similar vertex is already in the VBO, use it instead !
                indices.push_back( index );
            }else{ // If not, it needs to be added in the output data.
                vertices.push_back( in_vertices[i]);
                uvs     .push_back( in_uvs[i]);
                // normals .push_back( in_normals[i]);
                indices .push_back( (unsigned short)vertices.size() - 1 );
            }
        }

        glBindVertexArray(vao);
       
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        return true;
    }

    bool Mesh::draw() {
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    }


    inline bool ends_with(std::string const & value, std::string const & ending) {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    bool MeshManager::create(const char *filePath) {
        Mesh* mesh = new Mesh();
        assert(mesh);
        if(!mesh->create(filePath)) return false;
        this->add(mesh->getName(), mesh);
        return true;
    }

    bool MeshManager::createFromDir(const char *dirPath) {
        DIR *dir;
        struct dirent *ent;
        std::string filePath;
        if((dir = opendir(dirPath)) != NULL) {
            /* print all the files and directories within directory */
            while ((ent = readdir(dir)) != NULL) {
                if(ends_with(ent->d_name, ".obj")) {
                    filePath = "";
                    filePath += dirPath;
                    filePath += ent->d_name;
                    create(filePath.c_str());
                }
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("");
            return EXIT_FAILURE;
        }
        return true;
    }
}