
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D IntensityTexture;
uniform float radius;
in vec2 UV;


const float blur[9] = {
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
};

vec3 BlurColor(void){
	vec2 _uv = gl_FragCoord.xy * vec2(1.0 / 1920.0, 1.0 / 1080);
	if(texture2D(IntensityTexture,_uv).r == 0){
		return texture2D(DiffuseTexture, _uv).rgb;
	}
	else{
		vec3 color = vec3(0,0,0);

		vec2 blurPos  = vec2(_uv.x - 4.0 * (1.0 / 1920), _uv.y);
		for(int x = 0; x < 9; x++){
			color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
			blurPos.x += (1.0 / 1920);
		}
		blurPos = vec2(_uv.x, _uv.y-4.0*(1.0 / 1080.0));
		for(int x = 0; x < 9; x++){
			//color += texture2D(DiffuseTexture,blurPos).xyz * blur[x];
			color += texture2D(DiffuseTexture,blurPos).xyz * blur[x] * 0.5;
			blurPos.y += (1.0 / 1080);
		}
		return color;
	}
}

void main(void){
	fragColor = vec4(BlurColor(),1.0);
}