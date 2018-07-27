#include "Object.h"
#include "Geometry.h"
#include <cmath>

class Cylinder : public Object {

public:

Cylinder();

void init();

};

Cylinder::Cylinder(){
        std::cout << "(Cylinder.cpp) Cylinder constructor called";
        init();
}

void Cylinder::init(){
        unsigned int latitudeBands = 30;
        unsigned int longitudeBands = 30;
        float radius = 1.0f;
        double PI = 3.14159265359;
        double length = 1.0f;


        for(unsigned int latNumber = 0; latNumber <= latitudeBands; latNumber++) {
                float z = length/latitudeBands * latNumber;

                for(unsigned int longNumber = 0; longNumber <= longitudeBands; longNumber++) {

                        float angle = longNumber * PI / longitudeBands;
                        float sinAngle = sin(angle);
                        float cosAngle = cos(angle);

                        float x = radius * cosAngle;
                        float y = radius * sinAngle;
                        // Why is this "1-" Think about the range of texture coordinates ??
                        float u = 1 - ((float)longNumber / (float)longitudeBands);
                        float v = 1 - ((float)latNumber / (float)latitudeBands);

                        // Setup geometry
                        geometry.addVertex(x,y,z); // Position
                        geometry.addTexture(u,v); // Texture
                }
        }

        // Now that we have all of our vertices
        // generated, we need to generate our indices for our
        // index element buffer.
        // This diagram shows it nicely visually
        // http://learningwebgl.com/lessons/lesson11/sphere-triangles.png
        for (unsigned int latNumber1 = 0; latNumber1 < latitudeBands; latNumber1++) {
                for (unsigned int longNumber1 = 0; longNumber1 < longitudeBands; longNumber1++) {
                        unsigned int first = (latNumber1 * (longitudeBands + 1)) + longNumber1;
                        unsigned int second = first + longitudeBands + 1;
                        geometry.addIndex(first);
                        geometry.addIndex(second);
                        geometry.addIndex(first+1);

                        geometry.addIndex(second);
                        geometry.addIndex(second+1);
                        geometry.addIndex(first+1);
                }
        }

        // Finally generate a simple 'array of bytes' that contains
        // everything for our buffer to work with.
        geometry.gen();

        // std::cout << "#vertices:" << geometry.getSize() << "\n";
        // std::cout << "#indicies:" << geometry.getIndicesSize() << "\n";

        // Create a buffer and set the stride of information
        myBuffer.CreateBufferNormalMapLayout(14,
                                             geometry.getSize(),
                                             geometry.getIndicesSize(),
                                             geometry.getData(),
                                             geometry.getIndicesData());
}
