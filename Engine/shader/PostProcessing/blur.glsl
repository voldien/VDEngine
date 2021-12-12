
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;
uniform int BlurAmount;
uniform float BlurScale;
uniform float BlurStrength;
smooth in vec2 UV;

uniform float blurs[];
uniform int blurSample;

const float blur[9] = float[9](
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
);

vec3 BlurColor(){
	vec2 blurPos  = vec2(UV.x - 0.0045, UV.y);
	vec3 color = vec3(0,0,0);
	for(int x = 0; x < 9; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.x += 0.001;
	}


	blurPos = vec2(UV.x, UV.y -  0.0045);
	for(int x = 0; x < 9; x++){
		color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
		blurPos.y += 0.001;
	}
	return color;
}


void main(){
	fragColor = vec4(BlurColor(),1.0);

}