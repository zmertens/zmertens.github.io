#version 300 es
precision mediump float;

layout (location = 0) in vec4 aPosition;

uniform float uZoom;
uniform vec2 uOffset;

out vec2 vInitialZ;

void main(void)
{
    vInitialZ = (aPosition.xy * uZoom) + uOffset;

    gl_Position = aPosition;
}
