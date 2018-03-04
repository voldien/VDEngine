
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 tangent;
layout(location = 5) in ivec4 BoneID;
layout(location = 6) in vec4 BoneWeight;

out vec3 VertexPosition;
out vec2 UV;
out vec3 normal;
out vec3 tangent;
out vec3 VertexData;
out vec4 VertexWeight;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform mat4 DeformMatrix[100];
uniform int boneIndex = 1;


void main(void ){

	gl_Position = vec4(Vertex, 1.0);
	VertexWeight = BoneWeight * DeformMatrix[boneIndex];
	VertexData = Vertex;
	VertexPosition = (ModelMatrix * vec4(Vertex,1.0)).xyz;
	UV = TextureCoord;
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	tangent = (ModelMatrix * vec4(tangent,0.0)).xyz;
}
