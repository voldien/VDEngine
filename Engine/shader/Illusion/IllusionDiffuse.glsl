
layout(location = 0) out vec4 fragColor;
layout(location = 5) out vec4 emission;

smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;

uniform vec4 DiffuseColor;
uniform sampler2D DiffuseTexture;
uniform sampler2D IllusionTexture;

void main(){
	const vec2 constantList = vec2(1.0,0.0);
	fragColor = vec4((DiffuseColor.rgbw * texture2D(DiffuseTexture, UV).rgba * constantList.xxxy).rgb * (getAmbientColor().rgba +  getLight(normal,VertexPosition).rgba * constantList.xxxy ).rgb , 1.0) ;
	emission = texture2D(IllusionTexture, UV);
	fragColor = internalFog(fragColor);
}