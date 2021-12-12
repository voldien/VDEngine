ATTRIBUTE_IN(0) vec3 vertex;	/*	*/

uniform vec4 DiffuseColor;
uniform mat4 ModelViewProjection;

void main(){
	gl_Position = ModelViewProjection * vec4(vertex, 1.0);
}
