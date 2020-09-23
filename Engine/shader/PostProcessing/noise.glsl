
layout(location = 0) out vec4 fragColor;

precision highp float;
precision lowp int;

uniform sampler2D DiffuseTexture;
uniform vec2 Screen;
smooth in vec2 UV;


float randomHash(uint seed, float b){
	uint i = (seed^12345391u) *2654435769u;
	i ^= (i<<6u)^(i>>26u);
	i *= 2654435769u;
	i += (i << 5u) ^ (i >> 12u);
	return float(b * i);
}


void main(void){
	//float colorTemp = randomHash();
	//vec3 color = vec3(colorTemp,colorTemp,colorTemp);
	fragColor = vec4(1,1,1,1) * max(1.0,fract(randomHash(232 * 2,texture2D(DiffuseTexture, UV).rbg * 24)) * 0.00001);
	return;
}