#include "Game.hpp"

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

namespace PattyEngine {
    // Game Singleton
    Game* gGame = NULL;
    Game* getGame() { return gGame; }
    void setGame(Game* game) { gGame = game; }

    bool Game::init(const std::string name) {
        // Init Flag - Set to true by default.
        bool success = true;

        // Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		    success = false;
        } else {
            //Use OpenGL 3.1 core
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            // Create Window
            gWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            if(gWindow == NULL) {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			    success = false;
            } else {
                // Create Context
                gContext = SDL_GL_CreateContext(gWindow);
                if(gContext == NULL) {
                    printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				    success = false;
                } else {
                    // Initialize GLEW
                    glewExperimental = GL_TRUE;
                    GLenum glewError = glewInit();
                    if(glewError != GLEW_OK) printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));

                    // Use Vsync
                    if (SDL_GL_SetSwapInterval(1) < 0) printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

                    // Initialize Font
                    if( TTF_Init() == -1 ) {
						printf("ERROR: SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					}

                    // Initialize Audio
                    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
						printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
						success = false;
					}

                    // Initialize OpenGL
                    if(!initGL()) {
                        printf("Unable to initialize OpenGL!\n");
                        success = false;
                    }
                }
            }
        }

        return success;
    }

    std::string readFile(const char *filePath) {
        std::string content = "";
        std::ifstream fileStream(filePath, std::ios::in);

        if(!fileStream.is_open()) printf("Could not read file %s. File does not exist.", filePath);
        else {
            std::string line = "";
            while(!fileStream.eof()) {
                std::getline(fileStream, line);
                content.append(line + "\n");
            }
            fileStream.close();
        }
        
        return content;
    }
    
    bool Game::initGL() {
        bool success = true;                                                        // Success Flag

        gProgramID = glCreateProgram();                                             // Generate Program

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);                     // Create Vertex Shader
        std::string vertexShaderString = readFile("shaders/vertex.glsl");           // Get Vertex Source
        const GLchar* vertexShaderSource = vertexShaderString.c_str();
        glShaderSource(vertexShader, 1 , &vertexShaderSource, NULL);                // Set Vertex Source
        glCompileShader(vertexShader);                                              // Compile Vertex Source

        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);           // Check Vertex Shader for Errors

        if(vShaderCompiled != GL_TRUE) success = false;
        else {
            glAttachShader(gProgramID, vertexShader);                               // Attach Vertex Shader
            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);             // Create Fragment Shader
            std::string fragmentShaderString = readFile("shaders/fragment.glsl");   // Get Fragment Source
            const GLchar* fragmentShaderSource = fragmentShaderString.c_str();
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);         // Set Fragment Source
            glCompileShader(fragmentShader);                                        // Compile Fragment Source
            
            GLint fShaderCompiled = GL_FALSE;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);     // Check Fragment Shader for Errors

            if(fShaderCompiled != GL_TRUE) success = false;
            else {
                glAttachShader(gProgramID, fragmentShader);                         // Attach Fragment Shader
                glBindFragDataLocation(gProgramID, 0 ,"outColor");
                glLinkProgram(gProgramID);                                          // Link Program

                GLint programSuccess = GL_TRUE;
                glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
                if(programSuccess != GL_TRUE)  success = false;                     // Check if Link was Successful
                else {
                    glClearColor(0.f, 0.f, 0.f, 1.f);
                    glEnable(GL_DEPTH_TEST);
                    glDepthFunc(GL_LESS);
                    glEnable(GL_CULL_FACE);
                }
            }
        }

        return success;
    }

    bool Game::loadMedia() {
        bool success = true;

        // Load Scene, therefor loading meshes and models...
        sceneManager.add("scene001", new Scene());
        scene = sceneManager.getActiveScene();
        if(!scene->create("scenes/scene001.txt")) {
            printf("Couldn't load scene!\n");
            success = false;
        }

        return success;
    }

    void Game::run() {
        glUseProgram(gProgramID); //Bind program

        // Main Loop Flag
        quit = false;

        sceneManager.getActiveScene()->init();

        // While Application is Running
        while(!quit) {
            // Clear Color Buffer and Depth Buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
            
            sceneManager.getActiveScene()->update();

            // Update Screen
            SDL_GL_SwapWindow(gWindow);
        }

        glUseProgram(NULL); //Unbind program
        glDeleteProgram(gProgramID);

        // Disable Text Input
		SDL_StopTextInput();
    }

    void Game::close() {
        // Deallocate Program
        glDeleteProgram(gProgramID);

        // Destroy Window
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;

        // Quit SDL Subsystems
        SDL_Quit();
    }
}