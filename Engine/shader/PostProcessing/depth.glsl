#version 410
layout(location = 0) out vec4 fragColor;
smooth in vec2 UV;
uniform sampler2D DepthTexture;
uniform vec2 Screen;
uniform vec2 Camera;


float unpack (vec4 colour) {
	const vec4 bitShifts = vec4(1.0, 1.0 / 255.0, 1.0 / (255.0 * 255.0), 1.0 / (255.0 * 255.0 * 255.0)); 
	return dot(colour, bitShifts);
}

vec3 DepthColor(){
	float f = Camera.x;
	float n = Camera.y;
	float z = ((2.0 * n) / (f + n - texture2D(DepthTexture,UV).x * (f - n)));
	return vec3(z,z,z);
}

void main(){
	fragColor = vec4(DepthColor(),1.0);
	return;
}