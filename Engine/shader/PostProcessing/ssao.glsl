
layout(location = 0) out vec4 fragColor;

smooth in vec2 UV;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;
uniform sampler2D WorldTexture;
uniform sampler2D DepthTexture;
uniform sampler2D NormalRandomize;
uniform int sampler; 

/// <summary>
/// Specifies the size of the sampling radius.
/// <summary>
uniform float SamplingRadius = 18.820513f;
/// <summary>
/// Occluder bias to minimize self-occlusion.
/// <summary>
uniform float OccluderBias = 0.045f;
uniform vec2 Attenuation = vec2(0.82999289,0.0020000297);
uniform vec2 Screen;
uniform vec2 Camera;

float SamplePixels (in vec3 srcPosition, in vec3 srcNormal, in vec2 uv){
	// Get the 3D position of the destination pixel
	//vec3 dstPosition = texture2D(WorldTexture, uv).xyz;

	// Calculate ambient occlusion amount between these two points
	// It is simular to diffuse lighting. Objects directly above the fragment cast
	// the hardest shadow and objects closer to the horizon have minimal effect.
	vec3 positionVec = texture2D(WorldTexture, uv).xyz - srcPosition;
	float intensity = max(dot(normalize(positionVec), srcNormal) - OccluderBias, 0.0);

	// Attenuate the occlusion, similar to how you attenuate a light source.
	// The further the distance between points, the less effect AO has on the fragment.
	float dist = length(positionVec);
	float attenuation = 1.0 / (Attenuation.x + (Attenuation.y * dist));
	
	return intensity * attenuation;
}

void main(void){
	vec3 srcPosition = texture2D(WorldTexture,UV).rgb;
	vec3 srcNormal = normalize(texture2D(NormalTexture,UV).rgb);
	vec2 randVec = normalize(texture2D(NormalRandomize,UV).xy * 2.0f - 1.0f);
	float srcDepth = texture2D(DepthTexture, UV).r;
	srcDepth = GetExpToLinear(Camera.y,Camera.x,srcDepth);
	float kernelRadius = SamplingRadius * (1.0 - srcDepth);	

	vec2 kernel[4];
	kernel[0] = vec2(0.0, 1.0);		/* top		*/
	kernel[1] = vec2(1.0, 0.0);		/* right	*/
	kernel[2] = vec2(0.0, -1.0);	/* bottom	*/
	kernel[3] = vec2(-1.0, 0.0);	/* left		*/
	
	const float Sin45 = 0.707107;	/* 45 degrees = sin(PI / 4)	*/

	float occlusion = 0.0;
	for (int i = 0; i < 4; ++i){
		vec2 k1 = reflect(kernel[i], randVec);
		vec2 k2 = vec2(k1.x * Sin45 - k1.y * Sin45,
				k1.x * Sin45 + k1.y * Sin45);
		k1 *= (1.0f /Screen);
		k2 *=  (1.0f /Screen);
		
		occlusion += SamplePixels(srcPosition, srcNormal, UV + k1 * kernelRadius);
		occlusion += SamplePixels(srcPosition, srcNormal, UV + k2 * kernelRadius * 0.75);
		occlusion += SamplePixels(srcPosition, srcNormal, UV + k1 * kernelRadius * 0.5);
		occlusion += SamplePixels(srcPosition, srcNormal, UV + k2 * kernelRadius * 0.25);
	}
	
	/* Average and clamp ambient occlusion	*/
	occlusion /= 16.0;
	occlusion = (1.0f - clamp(occlusion, 0.0f, 1.0f));
	fragColor = occlusion * texture2D(DiffuseTexture, UV);
}



