
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;

in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;
in vec3 tangent;
in vec3 VertexLitColor;

#include ForwardLightning
#include ForwardShadow
};
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform float frontWeight;
uniform float backWeight;
uniform vec3 CameraPos;


void main(){
	fragColor = ((GetLightSurfaceScattering(GetTBNnormal(normal,tangent, NormalTexture,UV)) + vec4(VertexLitColor,0.0f)) * DiffuseColor * texture2D(DiffuseTexture, UV)).rgb;	
}
