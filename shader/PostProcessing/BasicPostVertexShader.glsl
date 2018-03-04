
layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
uniform Mat4 ModelViewProjection;
out vec2 UV;

void main(void) {
	gl_Position =  ModelViewProjection * vec4(Vertex,1.0);
	UV = TextureCoord;
	return;
}