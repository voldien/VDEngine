#include <Misc/VDGZFile.h>
#include <stdlib.h>
#include <zlib.h>
#include <cstring>


long int VDGZFile::load(const char* cfilename, char** racBuffer){
	long int nBytes = 0;
	char buf[1024];
	char len;

	gzFile gzf = gzopen(cfilename, "rb");
	while((len = gzread(gzf, buf, sizeof(buf))) > 0){
		nBytes += len;
		*racBuffer = (char*)realloc(*racBuffer, nBytes);
		memcpy(*racBuffer + (nBytes - len), buf, len);
	}
	gzclose(gzf);
	return nBytes;
}

long int VDGZFile::loadString(const char* cfilename, char** racBuffer){
	long int nbytes;

	nbytes = VDGZFile::load(cfilename, racBuffer);
	if(nbytes > 0){
		*racBuffer = (char*)realloc(*racBuffer, nbytes + 1);
		(*racBuffer)[nbytes] = '\0';
	}
	return nbytes;
}
