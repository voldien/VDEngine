FRAGLOCATION(0) vec4 fragColor;

uniform sampler2D DiffuseTexture;

SMOOTH_IN vec2 vUV;

void main(){
	if(texture2D(DiffuseTexture, UV).a < 0.9)
		discard;

	gl_FragDepth = gl_FragCoord.z;
}
