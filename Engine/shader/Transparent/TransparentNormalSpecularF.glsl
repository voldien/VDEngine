
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec3 VertexPosition;

#include ForwardLightning
#include Translucent 
#include ForwardShadow
};
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;
uniform float Shininess;


void main(){
	vec3 surfaceNormal = GetTBN(normal, tangent, NormalTexture, UV);
	fragColor = (texture2D(DiffuseTexture , UV)  * DiffuseColor) * (vec4(AmbientColor,0.0f) + GetLight(surfaceNormal).rgba) + vec4(GetSpecularFactor(surfaceNormal,Shininess) * vec4(SpecularColor, 1.0f)) ;
	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
