FRAGLOCATION(0, vec4, fragColor);
uniform vec4 DiffuseColor;

void main(void){
	fragColor = DiffuseColor;
	fragColor = internalFog(fragColor);
}
