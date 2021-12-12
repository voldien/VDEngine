
layout(location = 0)out vec4 fragColor;
in vec2 UV;

uniform sampler2D DiffuseTexture;
uniform sampler2D DepthTexture;
uniform vec3 DiffuseColor;
uniform int FogMode;
uniform float startValue;
uniform float endValue;
uniform float density;

uniform vec2 Screen;
uniform vec2 Camera;


void main (){
	//float f = Camera.x;
	//float n = Camera.y;
	float z = ((2.0 * Camera.y) / (Camera.x + Camera.y - texture2D(DepthTexture,UV).x * (Camera.x - Camera.y)));
	vec3 ColorFog = vec3(1,1,1);
	vec3 Color = texture2D(DiffuseTexture, UV).xyz;
	if(z > startValue && z != 1.0){

		float Depth =  (z - startValue ) * (1.0 / (endValue - startValue));
		if(FogMode == 0){
			ColorFog = (DiffuseColor * Depth * (1.0 / density));
		}
		else if(FogMode == 1){
			ColorFog = (DiffuseColor * Depth * (1.0 / density));
			Depth = exp(z - Depth);			
		}
		else{
			ColorFog = (DiffuseColor * Depth * (1.0 / density));
			Depth = exp2(z - Depth);
		}
		fragColor = vec4(mix(ColorFog, Color, 1.0 - Depth ),1);
	}
	else
		fragColor = vec4(Color,1.0);
	return;
}