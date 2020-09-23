 core
layout(triangles) in;
layout(line_strip, max_vertices = 6) out;
//in vec3 vVertexData[];
//in vec2 vUV[];
//in vec3 vnormal[];
//in vec3 vtangent[];

//out vec3 VertexPosition;
//out vec2 UV;
//out vec3 normal; 
//out vec3 tangent;
uniform int CameraFlag = 0x1000;
uniform mat4 ModelViewProjection;
uniform mat4 ModelMatrix;
uniform float normalSize = 1.0f;
uniform float tangentSize = 1.0f;

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
	//normal = vnormal[0];
	//tangent = vtangent[0];
	//UV = vUV[0];
	for (int i = 0; i < gl_in.length(); ++i) {
		gl_Position = gl_in[i].gl_Position;

		EmitVertex();
	}
	EndPrimitive();
	return;
	// Normal
	//if((CameraFlag & NormalMode) != 0){
		gl_Position = ModelViewProjection * vec4(vVertexData[0],1.0f );
		//Color = vec4(vec3(0,1,0), 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(vVertexData[0] + vec3(1.0f) * normalSize,1.0);
		//Color = vec4(vec3(0,1,0), 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(vVertexData[0] - vec3(1.0f) * normalSize,1.0);
		//Color = vec4(vec3(0,1,0), 1.0);
		EmitVertex();
		EndPrimitive();
	//}
	// tangent
	if((CameraFlag & 8) != 0){
		gl_Position = ModelViewProjection * vec4(vVertexData[0],1.0);
		//Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(vVertexData[0] + vtangent[0] * tangentSize,1.0);
	//	Color = vec4(1,0,0, 1.0);
		EmitVertex();
		EndPrimitive();
	}
	if((CameraFlag & 2) != 0){	//biNormal
		gl_Position = ModelViewProjection * vec4(vVertexData[0],1.0);
		///Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(vVertexData[0] + cross(vnormal[0],vtangent[0]),1.0);
	//	Color = vec4(1,0,0, 1.0);
		EmitVertex();
		EndPrimitive();	
	}
	if((CameraFlag & 1) != 0){	//bitTangent
		gl_Position = ModelViewProjection * vec4(vVertexData[0],1.0);
		//Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(vVertexData[0] + cross(vtangent[0],vnormal[0]),1.0);
		//Color = vec4(1,0,0, 1.0);
		EmitVertex();

	}*/
	//	EndPrimitive();	
}
