
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;
uniform vec4 DiffuseColor;
smooth in vec2 UV;

void main(void){
	fragColor = texture2D(DiffuseTexture, UV) * DiffuseColor;
	
}