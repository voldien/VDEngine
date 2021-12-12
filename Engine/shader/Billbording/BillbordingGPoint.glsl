
layout(points)in;
layout(triangle_strip)out;
layout (max_vertices = 4) out;
uniform vec3 CameraPos;
uniform mat4 ModelViewProjection; 
uniform vec2 billBoardSize = vec2(1.0f, 1.0f);
in vec3 GVertex[];
out vec2 FUV;

void main(){
	vec3 CameraN = normalize(CameraPos - GVertex[0]);
	vec3 up = vec3(0.0,1.0f,0.0);
	vec3 right = cross(CameraN, up);
	up = cross(right,CameraN);
	
	vec3 pos = GVertex[0];
	pos -= (right * 0.5f);
	gl_Position = ModelViewProjection * vec4(pos,1.0);
	FUV = vec2(0.0f,0.0f);
	EmitVertex();
	
	pos.y += 1.0f;
	gl_Position = ModelViewProjection * vec4(pos,1.0);
	FUV = vec2(0.0f,1.0f);
	EmitVertex();

	pos.y -= 1.0f;
	pos += right;
	gl_Position = ModelViewProjection * vec4(pos,1.0);
	FUV = vec2(1.0f,0.0f);
	EmitVertex();

	pos.y += 1.0f;
	gl_Position = ModelViewProjection * vec4(pos,1.0);
	FUV = vec2(1.0f,1.0f);
	EmitVertex();	
	EndPrimitive();  
}
