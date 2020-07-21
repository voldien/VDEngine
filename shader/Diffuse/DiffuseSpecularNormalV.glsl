
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec4 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 Tangent;

smooth out vec2 UV;
smooth out vec3 normal;
smooth out vec3 tangent;
smooth out vec3 VertexPosition;

uniform mat4 ModelMatrix[32];
uniform mat4 ModelViewProjection[32];

void main(void){
	
	gl_Position = ModelViewProjection[gl_InstanceID] * vec4(Vertex,1.0);
	VertexPosition = (ModelMatrix[gl_InstanceID] * vec4(Vertex,1.0) ).xyz;
	UV = TextureCoord.xy;
	normal = (ModelMatrix[gl_InstanceID] * vec4(Normal,0.0)).xyz;
	tangent = (ModelMatrix[gl_InstanceID] * vec4(Tangent, 0.0)).xyz;
}
