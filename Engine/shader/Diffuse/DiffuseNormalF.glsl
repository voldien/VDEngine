FRAGLOCATION(0, vec4, fragColor);
FRAGLOCATION(1, vec3, Worldfrag);
FRAGLOCATION(2, vec3, Normalfrag);

SMOOTH_IN vec3 vVertex;
SMOOTH_IN vec2 vUV;
SMOOTH_IN vec3 vNormal;
SMOOTH_IN vec3 vTangent;

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D NormalTexture;

void main (void){
	vec3 newNormal = getTBN( vNormal, vTangent, NormalTexture, vUV );

	fragColor = vec4( (DiffuseColor.rgb * texture2D(DiffuseTexture, vUV).rgb) *
	(getAmbientColor().rgb +  getLight(newNormal, vVertex).rgb) , 1.0f);

	Worldfrag = VertexPosition;
	Normalfrag = newNormal;
}
