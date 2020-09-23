#include"Internal/glsl_compiler.h"
#include<string.h>
#include<stdio.h>

int glsl_version(const char* csource){
	return 0;
}

unsigned int GetShaderProgramSize(unsigned int getProgram()){
	unsigned int i,fsize;
	int size;
	int shad_num;
	unsigned int mshad[10];
	fsize = 0;
	glGetAttachedShaders(getProgram(),5,&shad_num,mshad);
	for(i=0;i<shad_num;i++){
		glGetShaderiv(mshad[i], GL_SHADER_SOURCE_LENGTH,&size);
		fsize+=size;
	}
	return fsize;
}


int LoadShader(struct shader_header* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename){
	char* v_source,*f_source,*g_source,*tc_source,*te_source;
	v_source = f_source = g_source = tc_source = te_source = NULL;


	shad->getProgram() = glCreateProgram();
	if(cvertexfilename){
		shad->ver = CompileShaderSource(cvertexfilename,&v_source,GL_VERTEX_SHADER);
		glAttachShader(shad->getProgram(),shad->ver);
		//InitShader(shad, v_source, GL_VERTEX_SHADER);
	}
	if(cfragmentfilename){
		shad->fra = CompileShaderSource(cfragmentfilename,&f_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->getProgram(),shad->fra);
	}
	if(cgeometryfilename){
		shad->geo = CompileShaderSource(cgeometryfilename,&g_source,GL_GEOMETRY_SHADER);
	}
	if(ctesscfilename){
		shad->tesc = CompileShaderSource(ctesscfilename,&tc_source,GL_TESS_CONTROL_SHADER);
	}
	if(ctessefilename){
		shad->tese = CompileShaderSource(ctessefilename,&te_source,GL_TESS_EVALUATION_SHADER);
	}

	glLinkProgram(shad->getProgram());
	ShaderCompileLog(shad->getProgram(),GL_PROGRAM);

	free(v_source);
	free(f_source);
	free(g_source);
	free(tc_source);
	free(te_source);
	return 1;
}
int LoadShaderv(struct shader_header* shad, const char* cvertex_source,const char* cfragment_source,const char* cgeometry_source,const char* ctess_c_source, const char* ctess_e_source){
	if(!shad)
		return 0;
	shad->program = glCreateProgram();
	if(cvertex_source){
		shad->ver = CompileShaderSourcev(&cvertex_source,GL_VERTEX_SHADER);
		glAttachShader(shad->getProgram(),shad->ver);
	}
	if(cfragment_source){
		shad->fra = CompileShaderSourcev(&cfragment_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->getProgram(),shad->fra);
	}
	if(cgeometry_source){
		shad->geo = CompileShaderSourcev(&cgeometry_source,GL_GEOMETRY_SHADER);
		glAttachShader(shad->getProgram(),shad->geo);
	}
	if(ctess_c_source){
		shad->tesc = CompileShaderSourcev(&ctess_c_source,GL_TESS_CONTROL_SHADER);
		glAttachShader(shad->getProgram(),shad->tesc);
	}
	if(ctess_e_source){
		shad->tese = CompileShaderSourcev(&ctess_e_source,GL_TESS_EVALUATION_SHADER);
		glAttachShader(shad->getProgram(),shad->tese);
	}

	glLinkProgram(shad->getProgram());
	ShaderCompileLog(shad->getProgram(),GL_PROGRAM);
	return 1;
}
int CompileShaderSource(const char* _Str_path,char** shader_source, unsigned int shader_flag){
	char* source;
	int shader, c_message;
	if(!strlen(_Str_path))return -1;
	if(LoadFile(_Str_path,(void**)&source) != -1){
	
		shader = glCreateShader(shader_flag);
		glShaderSource(shader, 1,(const char**)&source,0);
		glCompileShader(shader);
		// validate 
		glGetShaderiv(shader, GL_COMPILE_STATUS, &c_message);
		if(!c_message)
			Error("Error to compile %s", _Str_path);

		if(!shader_source)
			free(source);
		else
			*shader_source = source;
	}else{Error("Invalid Path %s",_Str_path); return -1;}
	return shader;
}
int CompileShaderSourcev(const char** shader_source, unsigned int shader_flag){
	int shader;
	if(!shader_source)
		return -1;
	if(!strlen(shader_source[0]))return -1;
	
	shader = glCreateShader(shader_flag);
	glShaderSource(shader,1,shader_source, 0);
	glCompileShader(shader);
	ShaderCompileLog(shader,shader_flag);
	return shader;
}

unsigned int getProgramShader(unsigned int getProgram(), unsigned int shader_flag){
	int shad_count,i;
	unsigned int shaders[5];
//	glGetProgramiv(getProgram(), GL_ATTACHED_SHADERS,&shad_count);
//	glGetAttachedShaders(getProgram(), shad_count,0,&shaders);
	for(i = 0; i < shad_count;i++){
	//	glGetShaderiv(shaders[i],GL_
	}
	return 1;
}
int ShaderCompileLog(unsigned int shader__program,unsigned int shader_flag){
	int status,validate;
	char message[256];
	switch(shader_flag){
	case GL_VERTEX_SHADER:
	case GL_FRAGMENT_SHADER:
	case GL_GEOMETRY_SHADER:
	case GL_TESS_CONTROL_SHADER:
	case GL_TESS_EVALUATION_SHADER:
		glGetShaderiv(shader__program, GL_COMPILE_STATUS, &status);
		break;
	case GL_LINK_STATUS:
	case GL_PROGRAM:
	glGetProgramiv(shader__program, GL_LINK_STATUS,&status);
	glGetProgramiv(shader__program, GL_VALIDATE_STATUS, &validate);
		break;
	default:return 0;
	}
	if(!status && shader_flag != GL_PROGRAM)
		glGetShaderInfoLog(shader__program,sizeof(message),NULL, message);
	else if(!status)
		glGetProgramInfoLog(shader__program,sizeof(message),NULL, message);
	if(!status){
		printf("Error message when compiling glsl Shader\n%s", message);
		return 0;
	}
	return 1;
}

int getShaderSource(unsigned int getProgram(), unsigned int shader_flag, char** source){
	int len;
	glGetShaderiv(getProgram(), GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source[0] = (char*)malloc(len);
	glGetShaderSource(getProgram(), len, NULL, source[0]);
	//glGetProgramiv(getProgram(),
	return 1;
}
char* GetShaderSourcefast(unsigned int getProgram(), unsigned int shader_flag){
	int len;
	char* source;
	glGetShaderiv(getProgram(), GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source = (char*)malloc(len);
	glGetShaderSource(getProgram(), len, NULL, source);
	return source;
}
