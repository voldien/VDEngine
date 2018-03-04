#include <Core/VDDebug.h>
#include <errno.h>
#include <Misc/VDFile.h>
#include <stdlib.h>
#include <climits>
#include <cstdio>
#include <cstring>
#include <string>


static long int fileLenght(FILE* f){
	int pos, end;
	pos = ftell(f);
	fseek(f,0, SEEK_END);
	end = ftell(f);
	fseek(f,pos, SEEK_SET);
	return end;
}

long int VDFile::load(const char* cfilename, char** bufferptr){
	FILE*f;
	char* buffer;
	long int length;
	*bufferptr = NULL;

	if(!cfilename || strlen(cfilename) == 0){
		return -1;
	}

	f = VDFile::safeOpenRead(cfilename);
	if(!f){
		return -1;
	}
	length = fileLenght(f);
	buffer = (char*)malloc(length + 1);
	((char*)buffer)[length] = 0;
	VDFile::safeRead(f, buffer, length);
	fclose(f);
	*bufferptr = buffer;
	return length;
}

long int VDFile::load(const char* cfilename, char** bufferptr, long int& length){
	FILE*f;
	char* buffer;
	*bufferptr = NULL;

	if(!cfilename || strlen(cfilename) == 0){
		return -1;
	}

	f = VDFile::safeOpenRead(cfilename);
	if(!f){
		return -1;
	}
	length = fileLenght(f);
	buffer = (char*)malloc(length + 1);
	((char*)buffer)[length] = 0;
	VDFile::safeRead(f,buffer,length);
	fclose(f);
	*bufferptr = buffer;
	return length;
}

long int VDFile::loadString(const char* cfilename, char** racBuffer){

	long int nbytes;	/*	*/

	nbytes = VDFile::load(cfilename, racBuffer);
	if(nbytes > 0){
		*racBuffer = (char*)realloc(*racBuffer, nbytes + 1);
		(*racBuffer)[nbytes] = '\0';
	}
	return nbytes;
}

void VDFile::save(const char* cfilename, const char* racBuffer, long int riSize){

	FILE *f;	/*	*/

	f = VDFile::safeOpenWrite(cfilename);
	VDFile::safeWrite(f,racBuffer,riSize);

	fclose(f);
}

long int VDFile::append(const char* cfilename, char* acBuffer, int riSize){
	long int status;
	FILE* f;

	f = VDFile::safeOpenWrite(cfilename);
	if(!f){
		return -1;
	}

	fseek(f, 0, SEEK_END);
	VDFile::safeWrite(f, acBuffer, riSize);
	fwrite(acBuffer, riSize, 1, f);

	fclose(f);
	return status;
}

long int VDFile::size(const char* cfilename){
	long int len;
	FILE* file;
	file = VDFile::safeOpenRead(cfilename);
	if(!file)
		return -1;

	len = fileLenght(file);

	fclose(file);
	return len;
}

FILE* VDFile::safeOpenWrite(const char* cfilename){
	FILE* f;
	f = fopen(cfilename, "wb");
	if(!f){
		VDDebug::errorLog("Error opening file %s: %s\n", cfilename, strerror(errno));
	}
	return f;
}

FILE* VDFile::safeOpenWriteAppend(const char* cfilename){
	FILE* f;
	f = fopen(cfilename, "wb+");
	if(!f){
		VDDebug::errorLog("Error opening file %s: %s\n", cfilename, strerror(errno));
	}
	return f;
}

FILE* VDFile::safeOpenRead(const char* cfilename){
	FILE* f;
	f = fopen(cfilename,"rb");
	if(!f){
		VDDebug::errorLog ("Error opening file %s : %s\n",cfilename,strerror(errno));
	}
	return f;
}

void VDFile::safeWrite(FILE *f, const void* buffer, long int count){
	if((long int)fwrite(buffer,1, count, f) != count){
		VDDebug::errorLog("File write failure : %s \n",strerror(errno));
	}
}

void VDFile::safeRead(FILE* f, void* buffer, long int count){
	if((int)fread(buffer,1,count,f) != count){
		VDDebug::errorLog("File read failure : %s\n",strerror(errno));
	}
}

std::string VDFile::getDirectory(const char* cpath){
	return std::string(strstr(cpath, "/"));
}

bool VDFile::isRelativePath(const char* cfilename){
	return (cfilename[0] != '/');
}

bool VDFile::isAbsoultePath(const char* cfilename){
	return (cfilename[0] == '/');
}

bool VDFile::existFile(const char* cfilename){
	//return ExExistFile(cfilename) == SDL_TRUE;
}


bool VDFile::isDirectory(const char* cdirectory){
	//return ExIsDirectory(cdirectory) != SDL_FALSE;
}

int VDFile::directoryCount(const char* cdirectory){
	//return ExDirectoryCount(cdirectory);
}

const char* VDFile::getSubDirectory(const char* cdirectory, int index){
	//return ExGetSubDirectory(cdirectory, index);
}


bool VDFile::createDirectory(const char* directory){

	VDDebug::log("Create directory %s\n", directory);
	//ExBoolean status = ExCreateDirectory(directory);

	//if(status == SDL_FALSE){
	//	VDDebug::criticalLog("Failed to create directory %s : %d.\n", directory, errno);
	//}
	//return status != 0;
}

void VDFile::removeDirectory(const char* directory){
	//ExBoolean status = ExRemoveDirectory(directory);

	//if(!status){

	//}
}
