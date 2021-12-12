
layout(location = 0) out vec4 fragColor;
smooth in vec3 VertexPosition;
smooth in vec2 UV;
smooth in vec3 tangent;
smooth in vec3 normal;
smooth in vec3 CameraEye;


#include ForwardLightning
#include ForwardShadow
};

uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D DisplacementTexture;
uniform vec4 DiffuseColor;

void main(){

	vec2 ParallaxCoord = GetParallax(DisplacementTexture,UV ,normalize(CameraEye), DisplacementHeight);
	vec2 newNormal = getTBN(normal, tangent, NormalTexture, ParallaxCoord);
	
	fragColor = texture2D(DiffuseTexture, ParallaxCoord) * DiffuseColor * (getAmbientColor() + hetLight(normal,VertexPosition ) ) ;
	fragColor = internalFog(fragColor);
}