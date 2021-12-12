
layout(location = 0)out vec3 fragColor;
in vec2 UV;
uniform sampler2D DiffuseTexture;
uniform float Brightness = 0.1f;
uniform float Contrast = 0.1f;
uniform float GammaCutoff = 0.5f;
uniform float InvGamma = 0.45f;


void main(){
	vec4 colour = texture2D(DiffuseTexture, UV);
	colour.xyz = colour.xyz + Brightness;
	
	colour.xyz = (colour.xyz - vec3(0.5f)) * Contrast + vec3(0.5);
	
	colour.xyz = clamp(colour.xyz, 0.0,1.0f);
	
	if(UV.x < GammaCutoff)
		colour.xyz  = pow(colour.xyz, vec3(InvGamma));
		
	fragColor.rgb = colour.rgb;
}