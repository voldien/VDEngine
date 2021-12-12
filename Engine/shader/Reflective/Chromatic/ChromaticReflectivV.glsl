
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;

smooth out vec2 UV;
smooth out vec3 normal;
smooth out vec3 VertexPosition;
smooth out vec3 TRed,TBlue, TGreen, Reflect;
smooth out float refFactor;

uniform vec4 DiffuseColor;
uniform vec4 ReflactionColor;
uniform float fresnelBias = 0.05f;
uniform float fresnelScale = 0.25f;
uniform float fresnelPower = 0.3f;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main() {
	VertexPosition = vec4( ModelMatrix * vec4(Vertex, 1.0)).xyz;
	gl_Position = ModelViewProjection * vec4(Vertex, 1.0);
	
	normal = normalize((ModelMatrix * vec4(Normal, 0.0)).xyz);
	UV = TextureCoord;
	
	/*	*/
	Reflect = reflect(normalize(Vertex - info.cameraPos), normal);
	TRed = refract(normalize(Vertex - info.cameraPos), normal, Reflect.r);
	TGreen = refract(normalize(Vertex - info.cameraPos), normal, Reflect.g);
	TBlue = refract(normalize(Vertex - info.cameraPos), normal, Reflect.b);
	refFactor = fresnelBias+fresnelScale* pow(1.0 + dot(normalize(Vertex - info.cameraPos),normal),fresnelPower);

}
