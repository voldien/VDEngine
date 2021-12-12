
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
in vec3 VertexPosition;
in vec2 UV;
in vec3 normal;
in vec3 reflection;

#include ForwardLightning
#include ForwardShadow
};
uniform samplerCube ReflectionTexture;
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec4 ReflectionColor;
uniform vec3 CameraPos;


void main(){ 
	fragColor.rgb = (getAmbientColor().rgba +  getLight(normal,VertexPosition).rgba).rgb * DiffuseColor.rgb + texture(ReflectionTexture , reflection).rgb * ReflectionColor.rgb;
	fragColor.a =  1.0;
}
