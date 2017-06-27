#version 300 es
precision mediump float;

// Julia set renderer - Fragment Shader
// Graham Sellers
// OpenGL SuperBible

in vec2 vInitialZ;

layout (location = 0) out vec4 OutColor;

uniform sampler2D uTexGradient;
uniform vec2 C;
                                                                                       
void main(void)                                                                        
{
    vec2 Z = vInitialZ;
    const float threshold_squared = 16.0;
    int iterations = 0;
    const int max_iterations = 128; // size of texture width in Application.cpp
    while (iterations < max_iterations && dot(Z, Z) < threshold_squared)
    {
        vec2 Z_squared = vec2(Z.x * Z.x - Z.y * Z.y, 2.0 * Z.x * Z.y);
        Z = Z_squared + C;
        iterations += 1;
    }

    if (iterations == max_iterations)
        OutColor = vec4(0.0, 0.0, 0.0, 1.0);
    else
        OutColor = texture(uTexGradient, vec2(float(iterations) / float(max_iterations), 0.0));
}  
