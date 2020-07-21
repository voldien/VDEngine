
ATTRIBUTE_IN(0) vec3 vertex;	/*	*/
ATTRIBUTE_IN(1) vec2 uv;        /*	*/
ATTRIBUTE_IN(2) vec3 normal;    /*	*/
ATTRIBUTE_IN(3) vec3 tangent;	/*	*/

uniform mat4 ModelViewProjection;
uniform mat4 ModelViewMatrix;

OUT vec2 vUV;
OUT vec3 vNormal;

void main(void){
	vUV = uv;
	gl_Position = ModelViewProjection * vec4(vertex,1.0);
	vNormal = (ModelViewMatrix * vec4(normal,0.0) ).xyz;
}
