
layout(location = 0) out vec3 fragColor;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec3 VertexPosition;


	#include ForwardLightning
	#include ForwardShadow
};

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform float weight;


void main(void){
	fragColor = texture2D(DiffuseTexture, UV) * getLightTranslucent(normal);
}
