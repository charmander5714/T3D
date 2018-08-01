#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "SDLGraphicsProgram.h"
#include "Sphere.h"

using namespace std;

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


//Loops forever!
void SDLGraphicsProgram::loop(){


// ---------- Assigns textures to markers ------------//
        MarkerType currType;
        markerNodes.clear();


        for (int i = 0; i < 64; i++) {
                markerNodes.push_back(new SceneNode(new Sphere())); //TODO
        }

        for (int j = 0; j < 64; j++) {
                markerNodes[j]->getLocalTransform().loadIdentity();
        }

        SceneNode* root;

        //loads textures for scenenodes
        for (int i = 0; i < 4; i++) {
                Layer currLayer = game.getLayer(i);
                for (int j = 0; j < 16; j++) {
                        currType = currLayer.getMarkerType(j);
                        switch (currType) {
                        case Naught:
                                markerNodes[i * 16 + j]->getObject()->LoadTexture("rock.ppm");
                                break;
                        case Cross:
                                markerNodes[i * 16 + j]->getObject()->LoadTexture("sun.ppm");
                                break;
                        case Empty:
                                markerNodes[i * 16 + j]->getObject()->LoadTexture("earth.ppm");
                                break;
                        }
                }
        }







//---------- creates marker (Scenenode) associations for placement in board grid -----//

        root = markerNodes[0];

        renderer->setRoot(root);

        fillBoard(0);


        // Main loop flag
        // If this is quit = 'true' then the program terminates.
        bool quit = false;
        // Event handler that handles various events in SDL
        // that are related to input and output
        SDL_Event e;
        SDL_Event f;
        // Enable text input
        SDL_StartTextInput();

        // Set a default speed for the camera
        float cameraSpeed = 0.05f;

        // tick is just an arbitrary counter to generate orbits
        int tick = 0;

        bool buttonState = false;

        glm::vec3 boardCenter = findBoardCenter();
        cout << "board center: "<< boardCenter.x <<" " << boardCenter.y << " " << boardCenter.z << endl;
        cout << "z: " << boardCenter.z - rotateWorldRadius << endl;
        renderer->camera->warpCamera(glm::vec3(boardCenter.x, -boardCenter.y, boardCenter.z - rotateWorldRadius));


        while(!quit) {



                // nothing exciting
                if (tick == 64) {
                        tick = 0;
                }
                markerNodes[tick]->getObject()->LoadTexture("sun.ppm");
                tick++;



                //Handle events on queue
                while(SDL_PollEvent( &e ) != 0) {
                        // User posts an event to quit
                        // An example is hitting the "x" in the corner of the window.
                        if(e.type == SDL_QUIT) {
                                quit = true;
                        }


                        if (e.type==SDL_MOUSEBUTTONDOWN) {
                                buttonState = true;
                                //cout << "is true\n";

                        }

                        else if(e.type==SDL_MOUSEBUTTONUP) {
                                buttonState = false;
                                //cout << "is false\n";
                        }

                        if (e.type==SDL_MOUSEMOTION && buttonState) {
                                //    cout << "mouse motion detected" << endl;

                                // Handle mouse movements
                                int mouseX = e.motion.x;
                                int mouseY = e.motion.y;
                                float mouseDelta = renderer->camera->getMouseDelta(mouseX, mouseY).x; // in rads

                                renderer->camera->warpCamera(glm::vec3(boardCenter.x, -boardCenter.y, boardCenter.z - rotateWorldRadius));
                                markerNodes[0]->getLocalTransform().rotate(mouseDelta, 0.0f, boardCenter.y, 0.0f);


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

void SDLGraphicsProgram::add3R(int rowRoot) { //1D
        //cout << "filling row..." << endl;
        for (int i = 1; i <= 4; i++) {
                //cout << rowRoot << "  ";

                if (i != 4) {
                        markerNodes[rowRoot]->AddChild(markerNodes[rowRoot+1]);
                }


                if (i != 1) { // original root node
                        markerNodes[rowRoot]->getLocalTransform().translate(sphereSpacing, 0.0f, 0.0f);
                }

                rowRoot = rowRoot + 1;
        }
}

void SDLGraphicsProgram::fillLayer(int layerRoot) { //2D
        //cout << "filling layer..." << endl;
        for (int i = 1; i <= 4; i++) {
                //cout << layerRoot << endl;
                if (i != 4) {
                        markerNodes[layerRoot]->AddChild(markerNodes[layerRoot + 4]);
                }

                if (i != 1) { // original root node
                        markerNodes[layerRoot]->getLocalTransform().translate(0.0f,0.0f,sphereSpacing);
                }
                add3R(layerRoot);
                layerRoot = layerRoot + 4;
        }

}

//root is 0
void SDLGraphicsProgram::fillBoard(int root) { //3D
        //cout << "filling board..." << endl;




        for (int i = 1; i <= 4; i++) {
                //cout << root << endl << endl;
                fillLayer(root);
                if (i != 4) {
                        markerNodes[root]->AddChild(markerNodes[root + 16]);
                }

                if (i != 1) { // original root node
                        markerNodes[root]->getLocalTransform().translate(0.0f,-sphereSpacing,0.0f);
                }
                root = root + 16;
        }
}

glm::vec3 SDLGraphicsProgram::findBoardCenter() {
        GLfloat* tMatrix = markerNodes[0]->getLocalTransform().getTransformMatrix();
        cout << "aaaaaaaaaaa: " << tMatrix[0] << endl;

        float xCenter = sphereSpacing * 3 / 2 + 0;
        float yCenter = sphereSpacing * 3 / 2 + 0;
        float zCenter = sphereSpacing * 3 / 2 + 0;

        return glm::vec3(xCenter, yCenter, zCenter);



}
