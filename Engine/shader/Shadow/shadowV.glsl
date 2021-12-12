ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) vec2 uv;

SMOOTH_OUT vec2 vUV;

uniform mat4 ModelViewProjection;


void main (){
	gl_Position = ModelViewProjection * vec4(vertex, 1.0);
	vUV = uv;
}
