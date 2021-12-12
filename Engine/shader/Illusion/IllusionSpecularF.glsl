
layout(location = 0) out vec3 fragColor;
in vec2 UV;
in vec3 normal;
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
uniform sampler2D IllusionTexture;


void main(){
	fragColor = texture2D(DiffuseTexture, UV).xyz *DiffuseColor.xyz * (AmbientColor + GetLight(normal).xyz) 
	+ texture2D(IllusionTexture, UV).xyz + GetSpecularFactor(normal,Shininess) * SpecularColor;
}
