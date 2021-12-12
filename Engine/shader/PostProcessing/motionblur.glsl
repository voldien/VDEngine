
layout(location = 0) out vec4 fragColor;

smooth in vec2 UV;
uniform sampler2D DiffuseTexture0;
uniform sampler2D DiffuseTexture1;
uniform sampler2D DiffuseTexture2;
uniform sampler2D DiffuseTexture3;
uniform sampler2D DiffuseTexture4;

void main(){
	fragcolor = texture(DiffuseTexture0,UV) + 
	texture(DiffuseTexture1,UV) + 
	texture(DiffuseTexture2,UV) + 
	texture(DiffuseTexture3,UV) + 
	texture(DiffuseTexture4,UV);
}
