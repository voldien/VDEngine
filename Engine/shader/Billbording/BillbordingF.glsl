
layout(location = 0) out vec4 fragColor;
in vec2 FUV;
uniform sampler2D DiffuseTexture;
uniform vec4 DiffuseColor;

void main(){
	fragColor = texture2D(DiffuseTexture, FUV) * DiffuseColor;
	fragColor.a = 1.0f;
}
