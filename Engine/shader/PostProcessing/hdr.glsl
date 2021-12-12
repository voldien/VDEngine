
layout(location = 0) out vec4 fragColor;
in vec2 UV;
uniform sampler2D DiffuseTexture;
uniform vec2 Screen = vec2(1920.0f,1080.0f);
uniform float BlurAmount = 10.0f;
uniform float BlurScale = 1.0f;
uniform float radius = 1.0f;
uniform float exposure = 1.25f;
uniform float downSampleTexture = 4.0f;
uniform float bloomFactor = 1.0f;

#define Additive 0x1
#define ScreenBlend  0x2
#define HorizontalBlur 0x4
#define VerticalBlur 0x8

vec3 BlurColor(){
	vec3 color = vec3(0,0,0);
	float deviation = (float(BlurAmount) * 0.5f) * 0.35;
	deviation *= deviation;
	for(int x = 0; x < 10; x++){
		float offset = float(x) - float(BlurAmount) * 0.5f;
		vec3 _color = texture2D(DiffuseTexture, UV + vec2(offset * (5.0f / Screen.x) * BlurScale, 0.0f), 5.0f).xyz *  GaussianFilter( offset , deviation ) * 0.5;
		color += _color;
		continue;
	}
	for(int x = 0; x < 10; x++){
		float offset = float(x) - float(BlurAmount) * 0.5f;
		vec3 _color = texture2D(DiffuseTexture, UV + vec2(0, offset * (5.0f / Screen.y) * BlurScale), 5.0f).xyz *  GaussianFilter( offset , deviation ) * 0.5;
		color += _color;
		continue;
	}
	return clamp(color,0.0f, 1.0f);
}

void main(){
	vec4 color = texture2D(DiffuseTexture, UV);
	vec3 bloom = BlurColor();
	//color += vec4(bloom,1.0f) * bloomFactor;
	bloom *= ToneMapping(0.05, 12.8f);
	fragColor = color + vec4(bloom,1.0f);
	//fragColor = color;
	fragColor.a = 1.0f;
}
