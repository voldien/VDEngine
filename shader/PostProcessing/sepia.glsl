
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;
smooth in vec2 UV;

void main(void){
	fragColor = texture2D(DiffuseTexture, getScreenUV() ) * vec3(112.0 / 255.0, 66.0 / 255.0, 20.0 / 255.0, 1.0);
	fragColor.a = 1.0f;
}
