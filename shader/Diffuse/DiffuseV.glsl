ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) vec2 uv;
ATTRIBUTE_IN(2) vec3 normal;

SMOOTH_OUT vec2 vUV;
SMOOTH_OUT vec3 vNormal;
SMOOTH_OUT vec3 vVertex;

uniform vec4 DiffuseColor;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;

void main(void) {
	gl_Position = ModelViewProjection * vec4(vertex, 1.0);
	vVertex = (ModelMatrix * vec4(vertex, 1.0)).xyz;

	vNormal = (ModelMatrix * vec4(normal, 0.0)).xyz;
	vUV = uv;
}
