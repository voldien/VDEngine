
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
smooth out vec2 UV;
smooth out vec3 normal;
smooth out vec3 VertexPosition;
smooth out vec3 VertexLitColor;

uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main() {
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = ( ModelMatrix * vec4(Vertex,1.0)).xyz;
	
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	UV = TextureCoord;
}
