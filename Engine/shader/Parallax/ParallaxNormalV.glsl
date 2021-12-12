
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 tangent;
smooth out vec3 VertexPosition;
smooth out vec2 UV;
smooth out vec3 tangent;
smooth out vec3 normal;
smooth out vec3 CameraEye;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main(){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix * vec4(Vertex, 1.0)).xyz;
	
	UV = TextureCoord;
	tangent = (ModelMatrix * vec4(tangent,0.0)).xyz;
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	Mat3 TBNMatrix = Mat3(tangent, cross(normal, tangent),normal);
	CameraEye = (CameraPos - Vertex) * TBNMatrix;
}
