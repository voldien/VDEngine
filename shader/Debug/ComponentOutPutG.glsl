

layout(triangles) in;
layout(line_strip, max_vertices = 20) out;

//in vec3 VertexData[];
in vec2 UV[];
in vec3 normal[];
in vec3 tangent[];

out vec4 Color; 
uniform int componentFlag;
uniform mat4 ModelViewProjection;
uniform float normalSize;
uniform float tangentSize;

#define worldPos 1
#define UVDefination 2
#define NormalDefination 4
#define TangentDefination 8
#define BiNormalDefination 0x1000
#define BitTangentDefination 0x1000
#define WireFrameDefination 16 
#define MipMapDefination 32
#define OrdinaryRendering 64

void main(void){


	for(int x = 0; x < gl_in.length();x++){
		gl_Position = ModelViewProjection * gl_in[x].gl_Position;
		Color = vec4(0,0,0, 1.0);
		EmitVertex();
		
	}
	EndPrimitive();

	// Normal
	if((componentFlag & 4) != 0){
		gl_Position = ModelViewProjection * gl_in[0].gl_Position;
		Color = vec4(vec3(0,1,0), 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(gl_in[0].gl_Position.xyz + normal[0] * normalSize,1.0);
		Color = vec4(vec3(0,1,0), 1.0);
		EmitVertex();
		EndPrimitive();
	}

	// tangent
	if((componentFlag & 8) != 0){
		gl_Position = ModelViewProjection * gl_in[0].gl_Position;
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(gl_in[0].gl_Position.xyz + tangent[0] * tangentSize,1.0);
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		EndPrimitive();
	}

	if((componentFlag & 2) != 0){	//biNormal
		gl_Position = ModelViewProjection * gl_in[0].gl_Position;
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(gl_in[0].gl_Position.xyz + cross(normal[0],tangent[0]),1.0);
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		EndPrimitive();	
	}

	if((componentFlag & 1) != 0){	//bitTangent
		gl_Position = ModelViewProjection * gl_in[0].gl_Position;
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		
		gl_Position = ModelViewProjection * vec4(gl_in[0].gl_Position.rgb + cross(tangent[0],normal[0]),1.0);
		Color = vec4(1,0,0, 1.0);
		EmitVertex();
		EndPrimitive();
	}
}
