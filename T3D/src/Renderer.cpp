#include "Renderer.h"

// Sets the height and width of our renderer
Renderer::Renderer(unsigned int w, unsigned int h){
        //  std::cout << "(Renderer.cpp) Constructor called)\n";


        camera = new Camera();
        root = nullptr;
}

// Sets the height and width of our renderer
Renderer::~Renderer(){
        delete camera;
}

void Renderer::Update(){
        // Here we apply the projection matrix which creates perspective.
        // The first argument is 'field of view'
        // Then perspective
        // Then the near and far clipping plane.
        // Note I cannot see anything closer than 0.1f units from the screen.
        projectionMatrix = glm::perspective(45.0f,((float)SCREENWIDTH)/((float)SCREENHEIGHT),0.0f,100.0f);

        // Perform the update
        if(root!=nullptr) {
                // TODO: See if I can pass these by reference
                root->Update(projectionMatrix, camera);
        }
}

// Initialize clear color
// Setup our OpenGL State machine
// Then render the scene
void Renderer::Render(){

        // // What we are doing, is telling opengl to create a depth(or Z-buffer)
        // // for us that is stored every frame.
        // glMatrixMode(GL_MODELVIEW);
        // glEnable(GL_DEPTH_TEST);
        // glEnable(GL_TEXTURE_2D);
        // This is the background of the screen.
        glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);
        glClearColor( 0.01f, 0.01f, 0.01f, 1.f );
        // Clear color buffer and Depth Buffer
        // Remember that the 'depth buffer' is our
        // z-buffer that figures out how far away items are every frame
        // and we have to do this every frame!
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        // Nice way to debug your scene in wireframe!
        //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); /TODO: for epty ones wireframe?

        // Now we render our objects from our scenegraph
        if(root!=nullptr) {
                root->Draw();
        }



        glDisable(GL_DEPTH_TEST);
        //glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        //glPushMatrix();
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);
        glOrtho(0.0f, SCREENWIDTH, SCREENHEIGHT, 0.0f, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        //glPushMatrix();
        glLoadIdentity();

        drawButton();
        //glFlush();

        // glMatrixMode(GL_PROJECTION);
        // /glPopMatrix();
        // glMatrixMode(GL_MODELVIEW);
        // glPopMatrix();

}

void Renderer::drawButton() {
        glColor3f(1.0f,0.0f,0.0f);
        glBegin(GL_QUADS);
        glVertex2d(0,0);
        glVertex2d(0,50);
        glVertex2d(50,0);
        glVertex2d(50,50);
        glEnd();
        glPopMatrix();
}

// Determines what the root is of the renderer, so the
// scene can be drawn.
void Renderer::setRoot(SceneNode* n){
        root = n;
}
