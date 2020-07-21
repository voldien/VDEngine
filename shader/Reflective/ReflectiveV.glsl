
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
out vec3 VertexPosition;
out vec2 UV;
out vec3 normal;
out vec3 reflection;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform vec3 CameraPos;
void main(void){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix * vec4(Vertex,1.0)).xyz;
	UV = TextureCoord;
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	reflection = reflect(normalize(VertexPosition - CameraPos), normalize(normal));
}
