
layout(location = 0) out vec4 fragColor;
smooth in vec2 UV;
uniform sampler2D DiffuseTexture;


vec3 invertColor(void){
	vec3 color = texture2D(DiffuseTexture, getScreenUV()).xyz;
	return vec3(1.0 - color.x, 1.0 - color.y, 1.0 - color.z);
}

void main(void){
	fragColor = vec4(invertColor(),1.0);
}