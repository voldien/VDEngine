
FRAGLOCATION(0, vec4, fragColor);

SMOOTH_IN vec3 vVertex;
SMOOTH_IN vec2 vUV;
SMOOTH_IN vec3 vNormal;
smooth in vec3 vTangent;
smooth in vec3 vCameraEye;

uniform sampler2D DiffuseTexture;
uniform sampler2D DisplacementTexture;
uniform vec4 DiffuseColor;
uniform vec2 DisplacementHeight;

void main(void){
	fragColor = texture2D(DiffuseTexture, getParallax(DisplacementTexture, UV, normalize(CameraEye), DisplacementHeight) ) * DiffuseColor.rgb *
	(getAmbientColor() + getLight(normal));
	fragColor = internalFog(fragColor);
}
