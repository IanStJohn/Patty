#include "Game.hpp"
#include "Object.hpp"
#include "Model.hpp"

#include <glm/gtx/quaternion.hpp>

#include <fstream>

namespace PattyEngine {
    GLuint loadBMP(const char *imagepath) {
        // Data read from the header of the BMP file
        unsigned char header[54]; // Each BMP file begins by a 54-bytes header
        unsigned int dataPos;     // Position in the file where the actual data begins
        unsigned int width, height;
        unsigned int imageSize;   // = width*height*3
        // Actual RGB data
        unsigned char * data;

        // Open the file
        FILE * file = fopen(imagepath,"rb");
        if (!file){printf("Image could not be opened\n"); return 0;}

        if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
            printf("Not a correct BMP file\n");
            return false;
        }

        if ( header[0]!='B' || header[1]!='M' ){
            printf("Not a correct BMP file\n");
            return 0;
        }

        // Read ints from the byte array
        dataPos    = *(int*)&(header[0x0A]);
        imageSize  = *(int*)&(header[0x22]);
        width      = *(int*)&(header[0x12]);
        height     = *(int*)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos==0)      dataPos=54; // The BMP header is done that way

        // Create a buffer
        data = new unsigned char [imageSize];

        // Read the actual data from the file into the buffer
        fread(data,1,imageSize,file);

        //Everything is in memory now, the file can be closed
        fclose(file);

        // Create one OpenGL texture
        GLuint textureID;
        glGenTextures(1, &textureID);

        // "Bind" the newly created texture : all future texture functions will modify this texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        // Give the image to OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        return textureID;
    }

    bool Model::create(std::string meshName, const char *texImgPath) {
        mesh = getGame()->getSceneManager()->getActiveScene()->getMeshManager()->get(meshName);
        assert(mesh);
        textureID = loadBMP(texImgPath);
        return true;
    }

    bool Model::draw() {
        glm::mat4 projection = getGame()->getSceneManager()->getActiveScene()->getCamera()->getProjection();
        glm::mat4 view = getGame()->getSceneManager()->getActiveScene()->getCamera()->getView();
        glm::mat4 mvp = projection * view * model;
        
        GLuint MatrixID = glGetUniformLocation(getGame()->getProgramID(), "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        GLuint colorID = glGetUniformLocation(getGame()->getProgramID(), "v_rgba");
        glUniform4fv(colorID, 1, &rgba[0]);

        

        // static TTF_Font* font = NULL;
        // if(font == NULL) {
        //     font = TTF_OpenFont("fonts/Demo_ConeriaScript.ttf", 72);
        //     if(font == NULL) printf("! Error: Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        //     else {
        //         SDL_Surface* surface = TTF_RenderText_Blended(font, "Hello", SDL_Color {255, 255, 255, 255});
        //         if(surface != nullptr) {
        //             GLint colors = surface->format->BytesPerPixel;
        //             GLenum textureFormat;
                    
        //             if(colors == 4) textureFormat = (surface->format->Rmask == 0x000000ff) ? GL_RGBA : GL_BGRA;
        //             else textureFormat = (surface->format->Rmask == 0x000000ff) ? GL_RGB : GL_BGR;
                    
        //             glEnable(GL_TEXTURE_2D); glEnable(GL_BLEND);
        //             glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //             GLuint texture_id = 0;
        //             glGenTextures(1, &texture_id); glBindTexture(GL_TEXTURE_2D, texture_id);
        //             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //             glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //             glTexImage2D(GL_TEXTURE_2D, 0, colors, surface->w, surface->h, 0, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);
        //         }
        //     }
        // }

        glBindTexture(GL_TEXTURE_2D, textureID);

        mesh->draw();
    }

    void Model::update() {
        glm::mat4 parentModelMatrix = parent != NULL ? parent->getModelMatrix() : glm::mat4(1.0f);
        model = parentModelMatrix * glm::translate(glm::mat4(1.0f), position) * glm::toMat4(glm::quat(rotation)) * glm::scale(glm::mat4(1.0f), scale);
        this->draw();
        for(auto &child : children) child->update();
    }

    bool ModelManager::create(std::string name, std::string meshName, std::string texImgPath, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::vec4 rgba, Object *parent) {
        Model *model = new Model(name, parent, position, scale, rotation, rgba);
        assert(model);
        if(!model->create(meshName, texImgPath.c_str())) return false;
        this->add(name, model);
        return true;
    }
}