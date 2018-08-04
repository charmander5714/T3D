/** @file SDLGraphicsProgram.h
 *  @brief SDL Class used to setup input and setup of OpenGL.
 *
 *  This class is used for the initialization of SDL.
 *
 *  @author Mike
 *  @bug No known bugs.
 */

#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif



#include "Renderer.h"
#include "Game.h"
#include "globalVariables.h"

#include <vector>

using namespace std;

// Purpose:
// This class sets up a full graphics program using SDL
//
//


class SDLGraphicsProgram {
public:

// Constructor
SDLGraphicsProgram(int w, int h);
// Desctructor
~SDLGraphicsProgram();
// loop that runs forever
void loop();
// Get Pointer to Window
SDL_Window* getSDLWindow();
// Helper Function to Query OpenGL information.
void getOpenGLVersionInfo();

private:
// The window we'll be rendering to
SDL_Window* gWindow;
// OpenGL context
SDL_GLContext gContext;
// The Renderer responsible for drawing objects
// in OpenGL (Or whatever Renderer you choose!)
Renderer* renderer;

Game game;

vector<SceneNode*> markerNodes;

void fillRows(int rowRoot);

void fillLayers(int layerRoot);

void fillBoard(int root);

glm::vec3 findBoardCenter();

void initGame();

float sphereSpacing = 4.0f;

float cameraDistance = 30.0f;
};

#endif
