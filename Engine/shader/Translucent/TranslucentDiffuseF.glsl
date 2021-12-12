
layout(location = 0) out vec3 fragColor;
smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;


	#include ForwardLightning
	#include ForwardShadow
};

uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform float weight = 0.5f;


void main(){
	fragColor = texture2D(DiffuseTexture, UV).rgb * DiffuseColor.rgb * (AmbientColor + GetLight(normal).rgb);
}
