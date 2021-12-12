
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec3 Worldfrag;
layout(location = 2) out vec3 Normalfrag;
smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;
smooth in vec3 TRed,TBlue, TGreen, Reflect;
smooth in float refFactor;



	#include ForwardLightning
	#include ForwardShadow
};

uniform samplerCube ReflectionTexture;
uniform sampler2D DiffuseTexture;
uniform vec4 DiffuseColor;
uniform vec4 ReflectionColor;


void main(){
	vec4 cColor = getChromaticReflection( ReflectionTexture, normalize(VertexPosition - info.cameraPos),  Reflect, TRed, TGreen, TBlue, refFactor);
	fragColor = texture2D(DiffuseTexture, UV) * DiffuseColor * (getAmbientColor() + getLight(normal)) + (cColor * ReflectionColor);

	Worldfrag = VertexPosition;
	Normalfrag = normal;
}
