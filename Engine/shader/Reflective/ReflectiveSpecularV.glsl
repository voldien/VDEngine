
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
out vec2 UV;
out vec3 normal;
out vec3 VertexPosition;

uniform vec3 AmbientColor;
uniform vec4 DiffuseColor;
uniform vec4 SpecularColor;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform vec3 CameraPos;


void main() {
	VertexPosition = vec4( ModelMatrix * vec4(Vertex,1.0)).xyz;
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	UV = TextureCoord;
}
