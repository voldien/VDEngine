ATTRIBUTE_IN(0) vec3 vertex;
ATTRIBUTE_IN(1) vec2 uv;

SMOOTH_OUT vec2 vUV;

void main(){
	gl_Position = vec4(vertex,1.0);
	vUV = uv;
}
