FRAGLOCATION(0, vec4, fragColor);

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
IN vec2 vUV;
IN vec3 vNormal;


void main(void){
	const vec4 color = DiffuseColor * texture2D(DiffuseTexture, vUV) * getAmbient(vNormal);
	fragColor = internalFog(color);
}
