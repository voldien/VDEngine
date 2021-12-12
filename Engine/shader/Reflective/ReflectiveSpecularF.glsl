
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;

#include ForwardLightning
#include ForwardShadow
};
uniform vec3 CameraPos;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec4 SpecularColor;
uniform vec4 ReflectionColor;
uniform sampler2D DiffuseTexture;
uniform samplerCube ReflectionTexture;
uniform float Shininess;


void main(){
	vec3 surfaceReflection = reflect(normalize(VertexPosition - CameraPos), normalize(normal)); 
	fragColor = texture2D(DiffuseTexture, UV).rgb * DiffuseColor.rgb * (AmbientColor + GetLight(normal).rgb) + GetSpecularFactor(normal, Shininess) * SpecularColor.rgb
	+ (texture(ReflectionTexture, surfaceReflection).rgb * ReflectionColor.rgb);
}
