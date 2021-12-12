
layout(location = 0) out vec3 fragColor;
layout(location = 5) out vec4 emission;
smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;


#include ForwardLightning
#include ForwardShadow
};

uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D IllusionTexture;


void main(){
	fragColor = texture2D(DiffuseTexture, UV).rgb * Diffuse.rgb * (AmbientColor + GetLight(normal).rgb)
	+ texture2D(IllusionTexture, UV).rgb);
	illusionColor = texture2D(IllusionTexture, UV).rgba;
}
