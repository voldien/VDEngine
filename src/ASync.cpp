#include <Core/VDAsync.h>
#include <Core/VDEngine.h>
#include <Core/VDTaskSchedule.h>
#include <malloc.h>
#include <Misc/VDFile.h>
#include <cstdio>
#include <cstring>


static int private_async_read_pack_schedule(VDTaskSchedule::VDTaskPackage* pack){
	fseek((FILE*)pack->end, pack->offset, SEEK_SET);
	fread( (void*)(pack->begin + pack->offset) , 1, pack->size, (FILE*)pack->end);
	return 1;
}

static int private_async_write_pack_schedule(VDTaskSchedule::VDTaskPackage* pack){
	fseek((FILE*)pack->end, pack->offset, SEEK_SET);
	fwrite((const char*)(pack->begin + pack->offset),  1, pack->size, (FILE*)pack->end);
	return 1;
}


VDASync::VDASync(void){
	this->file = NULL;
}

VDASync::VDASync(const VDASync& sync){
	*this = sync;
}

VDASync::~VDASync(void){

}

VDAsyncRequestHandle VDASync::open(const char* cfilename){
	VDAsyncRequestHandle handle;
	handle.path = (char*)malloc(strlen(cfilename) + 1);
	memcpy(handle.path, cfilename, strlen(cfilename) + 1);
	handle.file = NULL;
	return handle;
}

void VDASync::close(VDAsyncRequestHandle* handle){
	free(handle->path);
	fclose(handle->file);
	handle->file = NULL;
	handle->path = NULL;
}


void VDASync::readFile(VDAsyncRequestHandle* handle, void* buffer, int buflem, AsyncMode mode){
	VDTaskSchedule::VDTaskPackage pack;
	const int packsize = 4096;
	int numPack = buflem / packsize;
	int rem = buflem % packsize;
	int x;

	handle->file = VDFile::safeOpenRead(handle->path);
	for(x = 0; x < numPack; x++){
		pack.offset = x * packsize;
		pack.size = packsize;
		pack.callback = (VDTaskSchedule::VDTaskCallback)private_async_read_pack_schedule;
		pack.begin = buffer;
		pack.end = handle->file;
		pack.flag = mode;
		VDEngine::getTaskSchedule().submitTask(&pack);
	}

	pack.offset = numPack * packsize;
	pack.size = rem;
	pack.callback = (VDTaskSchedule::VDTaskCallback)private_async_read_pack_schedule;
	pack.begin = buffer;
	pack.end = handle->file;
	pack.flag = mode;
	VDEngine::getTaskSchedule().submitTask(&pack);

}

void VDASync::writeFile(VDAsyncRequestHandle* handle, void* buffer, int buflem, AsyncMode mode){
	VDTaskSchedule::VDTaskPackage pack;
	const int packsize = 4096;
	int numPack = buflem / packsize;
	int rem = buflem % packsize;
	int x;

	/*	generate aligned packets	*/
	handle->file = VDFile::safeOpenWrite(handle->path);
	for(x = 0; x < numPack; x++){
		pack.offset = x * packsize;
		pack.size = packsize;
		pack.callback = (VDTaskSchedule::VDTaskCallback)private_async_write_pack_schedule;
		pack.begin = buffer;
		pack.end = handle->file;
		pack.flag = mode;
		VDEngine::getTaskSchedule().submitTask(&pack);
	}

	/*	generate non aligned packets.	*/
	pack.offset = numPack * packsize;
	pack.size = rem;
	pack.callback = (VDTaskSchedule::VDTaskCallback)private_async_write_pack_schedule;
	pack.begin = buffer;
	pack.end = handle->file;
	pack.flag = mode;
	VDEngine::getTaskSchedule().submitTask(&pack);

}


void VDASync::readFile(VDAsyncRequestHandle* handle, void* buffer, int buflem,  void (*VDAFileSyncCallBack)(void* buffer, unsigned int buflen, AsyncMode mode), AsyncMode mode){

}

void VDASync::writeFile(VDAsyncRequestHandle* handle, void* buffer, int buflem, void (*VDAFileSyncCallBack)(void* buffer, unsigned int buflen, AsyncMode mode),  AsyncMode mode){

}

int VDASync::wait(VDAsyncRequestHandle* handle){

	return 0;
}
