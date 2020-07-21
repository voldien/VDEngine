
layout(location = 0) out vec4 fragColor;

smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 tangent;
smooth in vec3 VertexPosition;


uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform vec4 DiffuseColor;
uniform vec3 SpecularColor = vec3(0.7,0.7,0.7);
uniform float Shininess = 5.0f;

void main(void){
	vec3 newNormal = getTBN( normal, tangent, NormalTexture, UV );
	fragColor = (DiffuseColor * texture2D(DiffuseTexture, UV)) * 
	(getAmbient(normal) + getLightIsotropicSpecular(newNormal, VertexPosition, Shininess, SpecularColor));
	fragColor = internalFog(fragColor);
}
