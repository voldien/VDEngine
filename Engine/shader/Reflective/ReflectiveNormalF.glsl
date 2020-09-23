
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;
in vec3 tangent;

#include ForwardLightning
#include ForwardShadow
};
uniform vec3 CameraPos;
uniform vec3 AmbientColor;

uniform sampler2D DiffuseTexture;
uniform samplerCube ReflectionTexture;
uniform sampler2D NormalTexture;
uniform vec3 SpecularColor;
uniform vec4 DiffuseColor;
uniform vec4 ReflectionColor;
uniform float Shininess;


void main(void){
	vec3 surfaceNormal = GetTBN(normal,tangent, NormalTexture, UV);
	vec3 DiffuseReflection = reflect(normalize(VertexPosition - CameraPos), normalize(surfaceNormal)); 
	fragColor = texture2D(DiffuseTexture, UV) * (AmbientColor + GetLight(surfaceNormal).rgb)
	+ (texture(ReflectionTexture, DiffuseReflection) * ReflectionColor);
}
