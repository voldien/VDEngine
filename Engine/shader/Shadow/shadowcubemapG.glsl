layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

SMOOTH_IN vec2 vUV;

uniform mat4 ViewProjection[6];
uniform mat4 ModelMatrix;

void main(){


	/*	first texture	*/
	gl_Layer = 0;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

	/*	Second texture.	*/
	gl_Layer = 1;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

	/*	Third texture.	*/
	gl_Layer = 2;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

	/*	Fourth texture.	*/
	gl_Layer = 3;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

	/*	Fifth texture.	*/
	gl_Layer = 4;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

	/*	Sixth texture.	*/
	gl_Layer = 5;
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = (ViewProjection[gl_Layer] * ModelMatrix) * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();

}

