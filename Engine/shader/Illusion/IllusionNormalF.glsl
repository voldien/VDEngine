
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
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D IllusionTexture;


void main(void){
	fragColor = texture2D(DiffuseTexture, UV).rgb * Diffuse.rgb * (AmbientColor + GetLight(GetTBN(normal,tangent,NormalTexture,UV)).rgb)
	+ texture2D(IllusionTexture, UV).rgb);
}
