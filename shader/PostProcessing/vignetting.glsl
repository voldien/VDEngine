
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;

uniform float outRadius = 0.65;
uniform float inRadius = 0.42;
uniform float intensity = 0.6;


void main(void){
	vec2 UV = (gl_FragCoord / getScreen().xy );
	vec2 relativePos = UV - 0.5;
	float len = length(relativePos);
	float vignette = smoothstep(outRadius, inRadius, len);


	vec4 texcolor = texture2D(DiffuseTexture, UV).rgba;
	fragColor = vec4(mix(texColor.rgb, texColor.rgb * vignette, intensity) ,1.0);
}