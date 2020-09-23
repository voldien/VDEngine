
layout(location = 0)out vec4 fragColor;

uniform sampler2D DiffuseTexture;
uniform float radius;
in vec2 UV;
uniform int BlurAmount;

const float blur[9] = {
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
};

vec3 BlurColor(void){
	vec3 color = vec3(0,0,0);
	vec2 blurPos  = vec2(UV.x - 0.0045, UV.y);

	for(int x = 0; x < BlurAmount; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.y += 0.001;
	}


	blurPos = vec2(UV.x, UV.y - 0.0045);
	for(int x = 0; x < BlurAmount; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.y += 0.0005;
	}
	return color;
}




void main(void){
	vec3 texColor = texture2D(DiffuseTexture, UV).rgb;
	vec3 glowColor = BlurColor();
	const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
	float intes = dot(texColor, LumCoeff);
	//fragColor = vec4(texColor + (glowColor  * 10 * intes - glowColor), 1.0);
	fragColor = vec4((texColor + glowColor) - (texColor * glowColor),1.0);
	//fragColor = vec4(4 * texColor * intes - texColor, 1);
	//fragColor = vec4(_uvs,0,1);
	return;
}