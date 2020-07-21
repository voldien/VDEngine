
layout(location = 0)out vec4 fragColor;
smooth in vec2 UV;

uniform sampler2D DiffuseTexture;	// Diffuse Color.
uniform sampler2D DepthTexture;		// Depth Color.
uniform vec3 lightPos;				// Light Position (xy ScreenCoordination, z = worldSpace Coordination)
uniform vec2 Screen;				// Screen Properties
uniform vec2 Camera;				// Camera Far & Near properties
uniform int RadianSampler;			// sample count;

const float blur[9] = {
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
};


/*	*/
void main(void){
	// Object Detph
	float detph = ((2.0 * Camera.y) / (Camera.x + Camera.y - texture2D(DepthTexture, UV).x * (Camera.x - Camera.y)));		// Exp Function to Linear Function.
	// Light Detph
	float lightDepth = (lightPos.z / Camera.x);
	
	// Delta Coordination
	vec2 deltaCoord = vec2(vec2(0.9,0.1) - UV);
	deltaCoord *= (1.0 / RadianSampler) * 0.1;
	vec2 _tempUV = UV;	
	vec3 color =  texture2D(DiffuseTexture,UV).rgb;
	float illuminationDecay = 1.0;
	if(detph < 0.1)
		illuminationDecay = 0;
	else{
		for(int x = 0;x < RadianSampler;x++){
			// get Color From Radial
			_tempUV -= deltaCoord;
			vec3 _tempColor = texture2D(DiffuseTexture,_tempUV).rgb;
	
			_tempColor *= illuminationDecay * 1.0;
	
			color += _tempColor * (1.0 / RadianSampler) * 0.25;
			
			illuminationDecay *= 0.98;
			continue;
		}
	//color /= RadianSampler;
	color *= 1.75;
	}
	//vec3 finalcolor = vec3(clamp(color.r,0.0, 1.0),clamp(color.g,0.0, 1.0),clamp(color.b,0, 1.0));
	fragColor = vec4(color * 1.1,1.0);
}