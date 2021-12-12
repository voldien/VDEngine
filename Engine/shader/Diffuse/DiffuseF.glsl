FRAGLOCATION(0, vec4, fragColor);

SMOOTH_IN vec3 vVertex;
SMOOTH_IN vec2 vUV;
SMOOTH_IN vec3 vNormal;

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;

void main (){
	const vec2 constantList = vec2(1.0,0.0);
	fragColor = (DiffuseColor * texture2D(DiffuseTexture, vUV) * constantList.xxxy) * (getAmbient(vNormal) +  getLight(vNormal,vVertex) * constantList.xxxy ) ;
	fragColor = internalFog(fragColor);
}
