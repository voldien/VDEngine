
layout(location = 0) out vec3 fragColor;
in vec3 VertexData;
in vec2 UV;
in vec3 normal;
in vec3 tangent;
in vec3 VertexPosition;

#include ForwardLightning
#include ForwardShadow
};
uniform int CameraFlag = 0x1000;
uniform float normalSize;
uniform float tangentSize;
uniform vec3 AmbientColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D SpecularTexture;
#define WireFrame 0x20
#define UVMode 0x40
#define NormalMode 0x80
#define TangentMode 0x100
#define MipModeMode 0x200
#define AmbientOcculsion 0x400
#define LightMode 0x800
#define UnlitTexture 0x1000
#define SpecularMode 0x2000

void main(){
	if((CameraFlag & UVMode) != 0){
		fragColor = vec3(UV,0.0f);
	}
	else if((CameraFlag & NormalMode) != 0){
		if(texture2D(NormalTexture,UV).z > 0.0f){
			fragColor = GetTBN(normal, tangent, NormalTexture, UV);
		}
		else{
			fragColor = normalize(normal);
		}
	}
	else if((CameraFlag & TangentMode) != 0){
			fragColor =  tangent;	
	}
	else if((CameraFlag & LightMode) != 0){
		fragColor = GetLight(normal).rgb;
	}
	else if((CameraFlag & UnlitTexture) != 0){
		fragColor = VertexData;
		//fragColor = texture2D(DiffuseTexture, UV).rgb;
	}
	else if((CameraFlag & SpecularMode) != 0){

	}
	else{
		fragColor = vec3(1.0f,0.0f, 0.0f);
	}
}


