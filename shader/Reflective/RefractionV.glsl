
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
out vec3 VertexPosition;
out vec2 UV;
out vec3 normal;
out vec3 refractionVector;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform float refraction;
uniform vec3 CameraPos;

void main(void){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix * vec4(Vertex,1.0)).xyz;
	UV = TextureCoord;
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	refractionVector = refract((VertexPosition - CameraPos), normalize(normal),1.0/refraction);
}
