
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec3 VertexPosition;
in vec2 UV;
in vec3 normal;
in vec3 refractionVector;

#include ForwardLightning
#include ForwardShadow
};
uniform samplerCube ReflectionTexture;
uniform vec3 AmbientColor;
uniform vec4 ReflectionColor;
uniform vec3 CameraPos;
uniform float refraction;


void main(void){
	fragColor = (GetLight(normal) + texture(ReflectionTexture ,refractionVector) * ReflectionColor).rgb;
}
