
layout(location = 0) out vec3 fragColor;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec3 VertexPosition;

#include ForwardLightning
#include ForwardShadow
};
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;
uniform float Shininess;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D IllusionTexture;


void main(){
	vec3 surfaceNormal = GetTBN(normal,tangent,NormalTexture,UV);
	fragColor = texture2D(DiffuseTexture, UV).xyz *DiffuseColor.xyz * (AmbientColor + GetLight(surfaceNormal).xyz) 
	+ texture2D(IllusionTexture, UV).xyz + GetSpecularFactor(surfaceNormal,Shininess) * SpecularColor;
}
