

layout(location = 0)out vec4 fragColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D DepthTexture;
uniform vec3 Direction;
in vec2 UV;

vec3 BlurMotion(){
	int samplerCount = length(Direction.xy);
	int samplerDepth = direction.z;
	vec3 blurColor;
	vec2 blurPos = UV - vec2((1.0f / Screen.x) * sampelerCount * 0.5,(1.0f / Screen.y) * sampelerCount * 0.5);

	for(int x = 0; x < samplerCount; x++){
		blurColor += texture2D(DiffuseTexture, blurPos) * (1.0f / samplerCount);
		vec2 pos += vec2((1.0 / Screen.x), (1.0 / Screen.y));
		continue;
	}

	for(int x = 0; x < samplerDepth; x++){
		vec2 direction;
		direction.x = cos(dot(UV, vec2(0.5, 0.5)));
		direction.y = sin(dot(UV, vec2(0.5, 0.5)));
		continue;
	}

	return blurColor;
}

void main (){
	fragColor = blurColor;
	return;
}