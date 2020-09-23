
layout(location = 0) in vec3 Vertex;
smooth out vec2 UV;

void main(void) {
	UV = vec2(Vertex.x, Vertex.y);
	gl_Position = vec4( Vertex.x , Vertex.y , 0, 1.0);
	
}
