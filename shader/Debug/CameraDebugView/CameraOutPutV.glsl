ATTRIBUTE_IN(0) vec3 Vertex;
ATTRIBUTE_IN(1) vec2 TextureCoord;
ATTRIBUTE_IN(2) vec3 Normal;
ATTRIBUTE_IN(3) vec3 tangent;

SMOOTH_OUT vec2 UV;
SMOOTH_OUT vec3 normal;
SMOOTH_OUT vec3 VertexPosition;
SMOOTH_OUT vec3 VertexLitColor;

uniform vec4 DiffuseColor;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;


layout(location = 0) in vec3 Vertex;
layout(location = 1) in vec2 TextureCoord;
layout(location = 2) in vec3 Normal;
layout(location = 3) in vec3 tangent;

out vec3 VertexData;
out vec2 UV;
out vec3 normal;
out vec3 tangent;
out vec3 VertexPosition;

uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform int CameraFlag = 0x1000;

#define WireFrame 0x20
#define UVMode 0x40
#define NormalMode 0x80
#define TangentMode 0x100
#define MipModeMode 0x200
#define AmbientOcculsion 0x400
#define LightMode 0x800
#define UnlitTexture 0x1000
#define SpecularMode 

void main(void){
	gl_Position = ModelViewProjection * vec4(Vertex,1.0f);
	VertexData = Vertex;
	VertexPosition = (ModelMatrix * vec4(Vertex,1.0f)).xyz;
	UV = TextureCoord;
	normal = (ModelMatrix * vec4(Normal,0.0f)).xyz;
	tangent = (ModelMatrix * vec4(tangent,0.0f)).xyz;
}
