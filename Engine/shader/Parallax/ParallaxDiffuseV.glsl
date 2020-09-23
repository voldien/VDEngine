
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Tangent;

smooth out vec3 VertexPosition;
smooth out vec2 UV;
smooth out vec3 tangent;
smooth out vec3 normal;
smooth out vec3 CameraEye;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main(void){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix * vec4(Vertex, 1.0)).xyz;
	
	UV = TextureCoord;
	tangent = (ModelMatrix * vec4(Tangent, 0.0)).xyz;
	normal = (ModelMatrix * vec4(Normal, 0.0)).xyz;

	mat3 TBNMatrix = mat3(tangent, cross(normal, tangent),normal);
	CameraEye = (getCameraPosition().xyz - Vertex) * TBNMatrix;
}
