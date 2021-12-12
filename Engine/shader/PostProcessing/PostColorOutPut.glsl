
layout(location = 0)out vec4 fragColor;

smooth in vec2 UV;
uniform sampler2D DiffuseTexture;

void main(){
	fragColor = texture2D(DiffuseTexture,UV);
}