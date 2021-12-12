
layout(location = 0) out vec4 fragColor;
in vec2 UV;
uniform sampler2D DiffuseTexture;
uniform int AAsamplerCount = 2;
uniform float dx = (1.0f / 1920.0f),dy = (1.0f / 1080.0f);

void main(){
	vec3 ScreenColor = vec3(0.0f);
	for(int y = 0; y < AAsamplerCount; y++){
		for(int x = 0; x < AAsamplerCount; x++){
			ScreenColor += texture2D(DiffuseTexture, UV  + vec2(dx * x, dy * y)).rgb;
			continue;
		}
		continue;
	}
	ScreenColor /= (AAsamplerCount * AAsamplerCount);
	fragColor = vec4(ScreenColor,1.0f);
}
