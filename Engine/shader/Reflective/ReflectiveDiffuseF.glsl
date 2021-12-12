
layout(location = 0) out vec4 fragColor;
smooth in vec2 UV;
smooth in vec3 normal;
smooth in vec3 VertexPosition;

uniform vec4 DiffuseColor;
uniform vec4 ReflectionColor;
uniform sampler2D DiffuseTexture;
uniform samplerCube ReflectionTexture;

void main(){
	vec3 SurfaceReflection = reflect(normalize(VertexPosition - getCameraPosition()), normalize(normal)); 
	
	fragColor.rgb = texture2D(DiffuseTexture, UV).rgb * (getAmbientColor().rgb + getLight(normal,VertexPosition).rgb)
	+ (texture(ReflectionTexture, SurfaceReflection).rgb * ReflectionColor.rgb).rgb;
	fragColor.a = 1.0;
}
