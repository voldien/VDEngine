
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;

smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;
smooth in vec3 VertexLitColor;


	#include ForwardLightning
	#include ForwardShadow
};

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform float frontWeight;
uniform float backWeight;

void main(void){
	fragColor = ((getLightSubSurface(normal,VertexPosition) + getAmbientColor()) * DiffuseColor * texture2D(DiffuseTexture, UV)).rgb;	
}
