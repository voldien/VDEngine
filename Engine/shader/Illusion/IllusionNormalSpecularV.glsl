
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 tangent;

	ForwardShadow 
};
out vec2 UV;
out vec3 normal;
out vec3 tangent;
out vec3 VertexPosition;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main(){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix * vec4(Vertex,1.0)).xyz;
	normal = (ModelMatrix * vec4(Normal,0.0)).xyz;
	tangent = (ModelMatrix * vec4(tangent,0.0)).xyz;
	UV = TextureCoord;
}
