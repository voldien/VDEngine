ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) vec2 uv;
ATTRIBUTE_IN(2) vec3 normal;
ATTRIBUTE_IN(3) vec3 tangent;

SMOOTH_OUT vec2 vUV;
SMOOTH_OUT vec3 vNormal;
SMOOTH_OUT vec3 vVertex;
smooth out vec3 vTangent;

uniform vec4 DiffuseColor;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;


void main(void) {
	gl_Position = ModelViewProjection * vec4(Vertex,1.0);
	VertexPosition = vec3(ModelMatrix * vec4(Vertex,1.0));
	normal = (ModelMatrix  * vec4(Normal,0.0)).xyz;
	tangent = (ModelMatrix * vec4(Tangent,0.0)).xyz;
	UV = TextureCoord;
}
