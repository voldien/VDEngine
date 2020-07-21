#version 430
layout(location = 0 ) out vec4 fragColor;

//uniform sampler2D DepthTexture;
uniform sampler2D DiffuseTexture;

uniform float FocusDistance;
uniform float FocusLenght;
uniform vec2 Screen;


smooth in vec2 UV;
const float blur[9] = {
	0.05,0.09, 0.11, 0.15,
	0.2,0.15,0.11,0.09, 0.05
};

vec3 BlurColor(void){

	float f = getCameraFar();
	float n = getCameraNear();
	/*	convert exp depth to linear.	*/
	float z = ((2.0 * n) / (f + n - texture2D(DepthTexture,UV).x * (f - n)));
	
	if(!(z < FocusDistance - FocusLenght / 2.0f  || z > FocusDistance + FocusLenght / 2.0f)){
		return texture2D(DiffuseTexture, UV).xyz;
	}
	else {
		vec2 blurPos  = vec2(UV.x - 0.0045, UV.y);
		vec3 color;
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
}

void main(void){
	fragColor = vec4(BlurColor(),1.0);
}