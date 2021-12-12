
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec3 VertexPosition;

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor;
uniform float Shininess;


void main(){
	vec3 newNormal = getTBN( normal, tangent, NormalTexture, UV );
	fragColor = (DiffuseColor.rgb * texture2D(DiffuseTexture, UV).rgb) * 
	(AmbientColor +  getLight(newNormal).rgb) + getSpecularFactor(newNormal,VertexPosition,Shininess) * SpecularColor * texture2D(SpecularTexture,UV).rgb;
	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
