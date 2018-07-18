#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "SDLGraphicsProgram.h"
#include "Sphere.h"

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h){
        std::cout << "(SDLGraphicsProgram.cpp) Constructor Called\n";
        // Initialization flag
        bool success = true;
        // String to hold any errors that occur.
        std::stringstream errorStream;
        // The window we'll be rendering to
        gWindow = NULL;
        // Render flag

        // Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO)< 0) {
                errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
                success = false;
        }
        else{
                //Use OpenGL 3.3 core
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
                // We want to request a double buffer for smooth updating.
                SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
                SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

                //Create window
                gWindow = SDL_CreateWindow( "Lab",
                                            SDL_WINDOWPOS_UNDEFINED,
                                            SDL_WINDOWPOS_UNDEFINED,
                                            w,
                                            h,
                                            SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

                // Check if Window did not create.
                if( gWindow == NULL ) {
                        errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
                        success = false;
                }

                //Create an OpenGL Graphics Context
                gContext = SDL_GL_CreateContext( gWindow );
                if( gContext == NULL) {
                        errorStream << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << "\n";
                        success = false;
                }

                // Initialize GLAD Library
                if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
                        errorStream << "Failed to iniitalize GLAD and OpenGL\n";
                        success = false;
                }
        }

        // If initialization did not work, then print out a list of errors in the constructor.
        if(!success) {
                errorStream << "SDLGraphicsProgram::SDLGraphicsProgram - Failed to initialize!\n";
                std::string errors=errorStream.str();
                SDL_Log("%s\n",errors.c_str());
        }else{
                SDL_Log("SDLGraphicsProgram::SDLGraphicsProgram - No SDL, GLAD, or OpenGL, errors detected during initialization\n\n");
        }

        // SDL_LogSetAllPriority(SDL_LOG_PRIORITY_WARN); // Uncomment to enable extra debug support!
        getOpenGLVersionInfo();


        // Setup our Renderer
        renderer = new Renderer(w,h);
}


// Proper shutdown of SDL and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
        if(renderer!=nullptr) {
                delete renderer;
        }

        //Destroy window
        SDL_DestroyWindow( gWindow );
        // Point gWindow to NULL to ensure it points to nothing.
        gWindow = NULL;
        //Quit SDL subsystems
        SDL_Quit();
}



// ====================== Create the planets =============
Object* sphere12;
SceneNode* Moon6;

Object* sphere11;
SceneNode* Moon2;

Object* sphere10;
SceneNode* Moon5;

Object* sphere9;
SceneNode* Moon4;

Object* sphere8;
SceneNode* Moon3;

Object* sphere7;
SceneNode* Earth3;

Object* sphere5;
SceneNode* Moon1;

Object* sphere4;
SceneNode* Earth2;

// Create the Moon
Object* sphere3;
SceneNode* Moon;
// Create the Earth
Object* sphere2;
SceneNode* Earth;
// Create the Sun
Object* sphere;
SceneNode* Sun;
// ====================== Create the planets =============

//Loops forever!
void SDLGraphicsProgram::loop(){

        // ================== Initialize the planets ===============
        static float rotate = 0.0f;

        // Note: There is no Moon6.

        // Create Moon6
        sphere12 = new Sphere();
        Moon6 = new SceneNode(sphere12);

        // Create Moon2
        sphere11 = new Sphere();
        Moon2 = new SceneNode(sphere11);


        // Create Moon5
        sphere10 = new Sphere();
        Moon5 = new SceneNode(sphere10);

        // Create Moon4
        sphere9 = new Sphere();
        Moon4 = new SceneNode(sphere9);

        // Create Moon3
        sphere8 = new Sphere();
        Moon3 = new SceneNode(sphere8);

        //Create Earth3
        sphere7 = new Sphere();
        Earth3 = new SceneNode(sphere7);

        // Create Moon1
        sphere5 = new Sphere();
        Moon1 = new SceneNode(sphere5);

        //Create Earth2
        sphere4 = new Sphere();
        Earth2 = new SceneNode(sphere4);

        // Create Earth's Moon
        sphere3 = new Sphere();
        Moon = new SceneNode(sphere3);
        // Create the Earth
        sphere2 = new Sphere();
        Earth = new SceneNode(sphere2);
        // Create the Sun
        sphere = new Sphere();
        Sun = new SceneNode(sphere);

        // Load Textures
        sphere12->LoadTexture("rock.ppm");
        sphere11->LoadTexture("rock.ppm");
        sphere10->LoadTexture("rock.ppm");
        sphere9->LoadTexture("rock.ppm");
        sphere8->LoadTexture("rock.ppm");
        sphere7->LoadTexture("earth.ppm");
        sphere5->LoadTexture("rock.ppm");
        sphere4->LoadTexture("earth.ppm");
        sphere3->LoadTexture("rock.ppm");
        sphere2->LoadTexture("earth.ppm");
        sphere->LoadTexture("sun.ppm");

        // Add all parent/child relationships for SceneNodes

        //Make Moon6 a child of Moon5
        Moon5->AddChild(Moon6);

        // Make Moon4 a child of Earth3
        Earth3->AddChild(Moon4);

        // Make Earth3 and Moon3 children of Earth2
        Earth2->AddChild(Moon3);
        Earth2->AddChild(Earth3);

        // Make Moon2 a child of Moon
        Moon->AddChild(Moon2);

        // Make the Moon a child of the Earth
        Earth->AddChild(Moon);

        // Make the Earth Earth2 and Moon5 children of the Sun
        Sun->AddChild(Moon5);
        Sun->AddChild(Earth);
        Sun->AddChild(Earth2);
        //Sun->AddChild(Moon6);


        // Render our scene starting from the sun.
        renderer->setRoot(Sun);
        // ================== Use the planets ===============

        // Main loop flag
        // If this is quit = 'true' then the program terminates.
        bool quit = false;
        // Event handler that handles various events in SDL
        // that are related to input and output
        SDL_Event e;
        // Enable text input
        SDL_StartTextInput();

        // Set a default speed for the camera
        float cameraSpeed = 0.05f;

        // tick is just an arbitrary counter to generate orbits
        int tick = 0;

        // While application is running
        while(!quit) {

                tick++;

                if (tick == 361) {
                        tick = 1;
                }
                // =============== Move the planets =============================
                // Set up a little scene of objects
                rotate+=0.01f;

                // 1 degree = 0.0174533 rad

                Moon6->getLocalTransform().loadIdentity();
                Moon6->getLocalTransform().translate((float) (7.0 * sin(tick * 0.0174533)),(float) (-2.0 * cos(tick * 0.0174533)),(float) (7.0 * cos(tick * 0.0174533)));
                Moon6->getLocalTransform().scale(0.4f,0.44f,0.3f);
                Moon6->getLocalTransform().rotate(50*rotate,0.0f,1.0f,0.0f);

                Moon5->getLocalTransform().loadIdentity();
                Moon5->getLocalTransform().translate((float) (7.0 * cos(tick * 0.0174533)),(float) (2.0 * cos(tick * 0.0174533)),(float) (7.0 * sin(tick * 0.0174533)));
                Moon5->getLocalTransform().scale(0.45f,0.45f,0.45f);

                Moon4->getLocalTransform().loadIdentity();
                Moon4->getLocalTransform().translate((float) (2.0 * cos(tick * 0.0174533)),0.0f,(float) (2.0 * sin(tick * 0.0174533)));
                Moon4->getLocalTransform().scale(0.2f,0.2f,0.2f);
                Moon4->getLocalTransform().rotate(15*rotate,0.0f,1.0f,0.0f);

                Moon3->getLocalTransform().loadIdentity();
                Moon3->getLocalTransform().translate((float) (-2.5 * cos(tick * 2 * 0.0174533)),0.0f,(float) (-2.5 * sin(tick * 0.0174533)));
                Moon3->getLocalTransform().scale(0.4f,0.4f,0.4f);


                Earth3->getLocalTransform().loadIdentity();
                Earth3->getLocalTransform().translate((float) (5.0 * sin(tick * 0.0174533)),0.0f,(float) (5.0 * cos(tick * 0.0174533)));
                Earth3->getLocalTransform().scale(0.7f,0.7f,0.7f);
                Earth3->getLocalTransform().rotate(rotate,0.0f,1.0f,0.0f);

                Earth2->getLocalTransform().loadIdentity();
                Earth2->getLocalTransform().translate((float) (7.0 * sin(tick * 0.0174533)),0.0f,(float) (-7.0 * cos(tick * 0.0174533)));
                Earth2->getLocalTransform().scale(0.7f,0.7f,0.7f);
                Earth2->getLocalTransform().rotate(-7 * rotate,0.0f,1.0f,0.0f);

                Moon2->getLocalTransform().loadIdentity();
                Moon2->getLocalTransform().translate((float) (3.0 * cos(tick * 0.0174533)),0.0f,(float) (4.0 * sin(tick * 0.0174533)));
                Moon2->getLocalTransform().scale(0.25f,0.25f,0.25f);
                Moon2->getLocalTransform().rotate(30*rotate,0.0f,1.0f,0.0f);

                Moon->getLocalTransform().loadIdentity();
                Moon->getLocalTransform().translate((float) (5.0 * cos(tick * 0.0174533)),0.0f,(float) (-2.0 * sin(tick * 0.0174533)));
                Moon->getLocalTransform().scale(0.4f,0.4f,0.4f);
                Moon->getLocalTransform().rotate(-20*rotate,0.0f,1.0f,0.0f);

                Earth->getLocalTransform().loadIdentity();
                Earth->getLocalTransform().translate((float) (4.0 * cos(tick * 0.0174533)),0.0f,(float) (4.0 * sin(tick * 0.0174533)));
                Earth->getLocalTransform().scale(0.5f,0.5f,0.5f);
                Earth->getLocalTransform().rotate(-5 * rotate,0.0f,1.0f,0.0f);

                Sun->getLocalTransform().loadIdentity();
                Sun->getLocalTransform().translate((float) (3.0 * cos(tick * 0.0174533)),(float) (1.5 * cos(tick * 0.0174533)),(float) (-1.0 * sin(tick * 0.0174533) - 12.0f));
                Sun->getLocalTransform().rotate(rotate,0.0f,1.0f,0.0f);


                // =============== Move the planets =============================





                //Handle events on queue
                while(SDL_PollEvent( &e ) != 0) {
                        // User posts an event to quit
                        // An example is hitting the "x" in the corner of the window.
                        if(e.type == SDL_QUIT) {
                                quit = true;
                        }
                        // Handle keyboad input for the camera class
                        if(e.type==SDL_MOUSEMOTION) {
                                // Handle mouse movements
                                int mouseX = e.motion.x;
                                int mouseY = e.motion.y;
                                //renderer->camera->mouseLook(mouseX, mouseY);
                        }
                        switch(e.type) {
                        // Handle keyboard presses
                        case SDL_KEYDOWN:
                                switch(e.key.keysym.sym) {
                                case SDLK_LEFT:
                                        renderer->camera->moveLeft(cameraSpeed);
                                        break;
                                case SDLK_RIGHT:
                                        renderer->camera->moveRight(cameraSpeed);
                                        break;
                                case SDLK_UP:
                                        renderer->camera->moveForward(cameraSpeed);
                                        break;
                                case SDLK_DOWN:
                                        renderer->camera->moveBackward(cameraSpeed);
                                        break;
                                case SDLK_RSHIFT:
                                        renderer->camera->moveUp(cameraSpeed);
                                        break;
                                case SDLK_RCTRL:
                                        renderer->camera->moveDown(cameraSpeed);
                                        break;
                                }
                                break;
                        }
                } // End SDL_PollEvent loop.

                // Update our scene through our renderer
                renderer->Update();
                // Render our scene using our selected renderer
                renderer->Render();
                // Delay to slow things down just a bit!
                SDL_Delay(25);
                //Update screen of our specified window
                SDL_GL_SwapWindow(getSDLWindow());
                // system("read -p 'Press Enter to continue...' var");
        }

        //Disable text input
        SDL_StopTextInput();
}


// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::getSDLWindow(){
        return gWindow;
}

// Helper Function to get OpenGL Version Information
void SDLGraphicsProgram::getOpenGLVersionInfo(){
        SDL_Log("(Note: If you have two GPU's, make sure the correct one is selected)");
        SDL_Log("Vendor: %s",(const char*)glGetString(GL_VENDOR));
        SDL_Log("Renderer: %s",(const char*)glGetString(GL_RENDERER));
        SDL_Log("Version: %s",(const char*)glGetString(GL_VERSION));
        SDL_Log("Shading language: %s",(const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
}
