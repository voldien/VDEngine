#version 450
#extension GL_GOOGLE_include_directive : enable

#include"../common.glsl"

FRAGLOCATION(0, vec4, fragColor);
uniform vec4 DiffuseColor;

void main(){
	fragColor = DiffuseColor;
	fragColor = internalFog(fragColor);
}
