
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;
in int InstanceID;

uniform sampler2D DiffuseTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;
uniform float Shininess = 5.0f;


void main(void){
	fragColor = (texture2D(DiffuseTexture , UV) * getLightSpecular(normal) * DiffuseColor).rgb;
	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
