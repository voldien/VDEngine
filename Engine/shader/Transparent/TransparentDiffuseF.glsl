
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec4 Worldfrag;
layout(location = 2) out vec4 Normalfrag;
in vec2 UV;
in vec3 normal;
in vec3 VertexPosition;
in vec3 VertexLitColor;

#include ForwardLightning
#include Translucent 
#include ForwardShadow
};
uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;



void main (){
	fragColor = GetLight(normal) * DiffuseColor * texture2D(DiffuseTexture, UV);
	Worldfrag = vec4(VertexPosition,1.0f);
	Normalfrag = vec4(normal,1.0f);	
}
