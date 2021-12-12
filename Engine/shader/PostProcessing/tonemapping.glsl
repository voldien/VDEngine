
layout(location = 0) out vec4 fragColor;
uniform sampler2D DiffuseTexture;

void main(){
	vec2 UV = gl_FragCoord.xy / getScreen().xy;
	vec4 color = texture2D(DiffuseTexture, UV);
	
	//toneMapping(
	color = color / ( color + vec4(1.0) );
	fragColor = fragColor;
}