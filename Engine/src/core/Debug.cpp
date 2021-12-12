#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <DataStructure/VDIterator.h>
#include <GL/glew.h>
#include <SDL2/SDL_stdinc.h>
#include <Tools/VDTweakBar.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

using namespace std;


VDDebug::VDDebug(){
	this->mode = 0;
	memset(this->query,0,sizeof(query));
}

VDDebug::~VDDebug(){

}

void VDDebug::init(){
	this->tools.push(new VDTweakBar());
}

void VDDebug::release(){

	/*	*/
	glDeleteQueries(sizeof(query) / sizeof(query[0]), (GLuint*)query);
	for(vector<VDToolBase*>::Iterator it = tools.begin(); it != tools.end(); it++){
		(*it)->release();
	}
}

void VDDebug::begin(){
	if(!VDDebug::isDebugEnabled()){
		return;
	}

	glBeginQuery(GL_SAMPLES_PASSED,query[0]);
	glBeginQuery(GL_ANY_SAMPLES_PASSED,query[1]);
	glBeginQuery(GL_PRIMITIVES_GENERATED,query[2]);
	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN,query[3]);
	glBeginQuery(GL_TIME_ELAPSED,query[4]);

	glBeginQuery(GL_ANY_SAMPLES_PASSED_CONSERVATIVE, query[5]);

}

void VDDebug::end(){
	if(!VDDebug::isDebugEnabled()){
		return;
	}


	int res[10];

	glGetQueryObjectuiv(query[0], GL_QUERY_RESULT, (GLuint*)&res[0]);
	glGetQueryObjectuiv(query[1], GL_QUERY_RESULT, (GLuint*)&res[1]);
	glGetQueryObjectuiv(query[2], GL_QUERY_RESULT, (GLuint*)&res[2]);
	glGetQueryObjectuiv(query[3], GL_QUERY_RESULT, (GLuint*)&res[3]);
	glGetQueryObjectuiv(query[4], GL_QUERY_RESULT, (GLuint*)&res[4]);


	glEndQuery(GL_SAMPLES_PASSED);
	glEndQuery(GL_ANY_SAMPLES_PASSED);
	glEndQuery(GL_PRIMITIVES_GENERATED);
	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glEndQuery(GL_TIME_ELAPSED);

	VDDebug::log("Sample passed : %d\n", res[0]);
	VDDebug::log("Any Sample passed : %d\n", res[1]);
	VDDebug::log("Primitives generated : %d\n", res[2]);
	VDDebug::log("Transform feedback primitives written: %d\n", res[3]);
	VDDebug::log("Time elapsed : %d\n", res[4]);

	for(vector<VDToolBase*>::Iterator it = tools.begin(); it != tools.end(); it++){
		(*it)->update();
	}
}


bool VDDebug::isDebugBuild(){
#ifdef VD_DEBUG
	return true;
#else
	return false;
#endif
}

bool VDDebug::isDebugEnabled(){
	return (VDEngine::getSubSystemFlag() & VDEngine::SubSystem::Debug) != SDL_FALSE;
}

void VDDebug::log(const char* format,...){
	va_list argptr;
	int status;

	va_start(argptr,format);

	/*	output to stdout	*/
	status = vfprintf(stdout, format, argptr);
	//VDDebug::fLogv(stdout, format, argptr);

	va_end(argptr);
}

void VDDebug::errorLog(const char* format,...){
	va_list argptr;
	int status;

	va_start(argptr, format);
	/**/
	status = vfprintf(stderr, format, argptr);

	va_end(argptr);
}

void VDDebug::warningLog(const char* format,...){
	char text[4096];
	va_list argptr;
	int status;

	va_start(argptr,format);

	/*	output to stdout	*/
	status = vfprintf(stderr, format, argptr);
	va_end(argptr);
}

void VDDebug::criticalLog(const char* format,...){
	char text[4096];
	va_list argptr;
	int status;

	va_start(argptr,format);
	status = vfprintf(stderr, format, argptr);
	va_end(argptr);
}


void VDDebug::debugLog(const char* format,...){
	if(!VDDebug::isDebugEnabled()){
		return;
	}

	char text[4096];
	va_list argptr;
	int status;

	va_start(argptr,format);
	status = vfprintf(stdout, format, argptr);
	va_end(argptr);
}

