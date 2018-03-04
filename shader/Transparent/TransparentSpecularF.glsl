
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;
in int InstanceID;

#include ForwardLightning
#include Translucent 
#include ForwardShadow
};
uniform sampler2D DiffuseTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;
uniform float Shininess;


void main(void){
	fragColor = DiffuseColor * texture2D(DiffuseTexture, UV) * 
	vec4((AmbientColor +  GetLight(normal).rgb) + GetSpecularFactor(normal, Shininess) * SpecularColor,1.0f);
	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
