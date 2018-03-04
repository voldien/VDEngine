
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;
flat in int InstanceID;

uniform sampler2D DiffuseTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform vec3 CameraPos;
uniform float Shininess = 5.0f;


void main(void){
	fragColor = (DiffuseColor.rgb * texture2D(DiffuseTexture, UV).rgb).rgb * 
	(AmbientColor + getLight(normal).rgb) + getSpecularFactor(normal, Shininess) * SpecularColor;
	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
