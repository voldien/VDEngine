ATTRIBUTE_IN(0) vec3 vertex;		/*	*/
ATTRIBUTE_IN(7) vec4 vertexColor;	/*	*/

OUT vec4 vVertexColor;
uniform mat4 ModelViewProjection;

void main(void){
	gl_Position = ModelViewProjection * vec4(vertex, 1.0);
	vVertexColor = vertexColor;
}
