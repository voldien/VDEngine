
layout(location = 0) out vec3 fragColor;
in vec3 VertexPosition;
in vec2 UV;
in vec3 tangent;
in vec3 normal;
in vec3 eyeDirection;

#include ForwardLightning
#include ForwardShadow
};
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D DisplacementTexture;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform float Shininess;
uniform vec3 AmbientColor;
uniform vec3 CameraPos;
uniform vec2 DisplacementHeight;


void main(void){

}