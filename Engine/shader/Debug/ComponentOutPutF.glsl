
layout(location = 0) out vec4 fragColor;
in vec3 VertexData;

in vec3 VertexPosition;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec4 VertexWeight;

in vec4 Color; 
uniform mat4 ModelViewProjection;
uniform int componentFlag;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D IllusionTexture;
uniform sampler2D ReflectionTexture;
uniform sampler2D MipMapTexture;
uniform vec4 lineColor;
uniform vec4 boundingBoxColor;

#define worldPos 1
#define UVDefination 2
#define NormalDefination 4
#define TangentDefination 8
#define BiNormalDefination 0x1000
#define BitTangentDefination 0x1000
#define WireFrameDefination 16 
#define MipMapDefination 32
#define OrdinaryRendering 64



void main(){
	if((componentFlag & worldPos) != 0){
		fragColor = vec4(VertexPosition,1.0);		
	}
	else if((componentFlag & UVDefination) != 0){
		fragColor = vec4(UV,0,1);
	}
	else if((componentFlag & NormalDefination) != 0){
		if(length(texture2D(NormalTexture,UV).rgb) > 0.0)
			fragColor = vec4(GetTangentNormal(normal, tangent, NormalTexture,UV),1);
		else
			fragColor = vec4(normalize(normal),1.0f);
		fragColor += Color;
	}
	else if((componentFlag & TangentDefination) != 0){
		fragColor = vec4(normalize(tangent),1);
		fragColor += Color;
	}
	else if((componentFlag & WireFrameDefination) != 0){
		fragColor = lineColor;
	}
	else if((componentFlag & MipMapDefination) != 0){
		fragColor = texture2D(DiffuseTexture, UV);
	}
	else if((componentFlag & 0) != 0){
		fragColor += VertexWeight;
	}
	else if(componentFlag & 64){
		fragColor = Color;
	}
	else
		fragColor = vec4(1,0,0,1);

	fragColor += Color;
	fragColor += VertexWeight;
}
