
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;

vec3 grayColor(){
	float color = dot(texture2D(DiffuseTexture, getScreenUV() ).xyz, vec3(0.29f, 0.59f, 0.12f));
	return vec3(color);
}

void main(){
	fragColor = vec4(grayColor(), 1.0);
}