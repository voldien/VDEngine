#version 410


struct BaseLight{
	vec3 Color;
	float intensity;
	int LightQuality;
};
struct DirectionLight{
	BaseLight base;
	vec3 Direction;
};
struct Omni{
	BaseLight base;
	vec3 Position;
	float Range;
};
struct SpotLight{
	BaseLight base;
	vec3 Position;
	vec3 Direction;
	float Angle;
	float Range;
};

varying vec2 UV;
varying vec3 normal;
varying vec3 VertexPosition;

uniform vec3 MaterialAmbientColor;
uniform vec4 BaseColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D IllusionTexture;

uniform DirectionLight _DirectionLight[2];
uniform Omni _OmniLight[50];
uniform SpotLight _SpotLight[20];

uniform int _DirectionCount;
uniform int _OmniCount;
uniform int _SpotLightCount;



void main(void){
	gl_FragColor = vec4(0,0,0,0);
}