#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDTaskSchedule.h>
#include <semaphore.h>
#include<pthread.h>
#include<signal.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_video.h>
#include <VDSystemInfo.h>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>


VDTaskSchedule::VDTaskSchedule(void){
	this->num = 0;
	this->pool = NULL;
	this->flag = 0;
	this->dheap = NULL;
}

VDTaskSchedule::VDTaskSchedule(const VDTaskSchedule& task){
	*this = task;
}

VDTaskSchedule::~VDTaskSchedule(void){

}

void VDTaskSchedule::release(void){
	int x;

	terminateTaskSch();
	for(x = 0; x < getNumTaskPool(); x++){
		SDL_DestroyMutex((SDL_mutex*)this->pool[x].mutex);
		free(this->pool[x].package);
	}

	/**/
	free(this->pool);
	free(this->dheap);

	/**/
	this->dheap = NULL;
	this->pool = NULL;
}


void VDTaskSchedule::init(int cores, unsigned int flags, unsigned int maxPackagesPool){


	if(this->pool != NULL){
		this->wait();
		this->release();
	}

	/*	*/
	char buf[256] = {0};
	int offset = VDSystemInfo::getCPUCoreCount() / cores;
	unsigned int packageQueueSize = maxPackagesPool / cores;
	this->num = cores;
	this->pool = (VDTaskPool*)realloc(this->pool, this->num  * sizeof(VDTaskPool));
	this->dheap = (VDTaskPool**)realloc(this->dheap, sizeof(VDTaskPool*) * this->num);
	memset(this->pool, 0, sizeof(VDTaskPool) * num);


	/*	TODO resolve later, */
	/*	*/
	sigset_t* set = (sigset_t*)malloc(sizeof(*set));
	sigemptyset(set);
	sigaddset(set, eDone);
	pthread_sigmask(SIG_BLOCK, set, NULL);


	VDDebug::log("Creating %d thread for VDTaskSchedule.\n", cores);
	/*	iterator	*/
	for(int x = 0; x < this->num; x++){
		/*	dheap	*/
		this->dheap[x] = (VDTaskPool*)&this->pool[x];

		/*	Reference main schedule object.	*/
		pool[x].sch = this;
		pool[x].index = x;

		/*	Initialize pool queue.	*/
		pool[x].userdata = NULL;
		pool[x].package = (VDTaskPackage*)malloc(sizeof(VDTaskPackage) * packageQueueSize);
		pool[x].numqueue = 0;
		pool[x].back = pool[x].package;
		pool[x].front = pool[x].package;
		pool[x].size = packageQueueSize;
		pool[x].reserved = packageQueueSize;
		pool[x].maxpackageSize = 0;
		pool[x].totalPackages = 0;

		/*	*/
		pool[x].initcallback = NULL;
		pool[x].semaphore = malloc(sizeof(sem_t));
		sem_init((sem_t*)pool[x].semaphore, 0, 0);
		pool[x].mutex = SDL_CreateMutex();
		pool[x].schThread = pthread_self();
		pool[x].coreIndex = offset * x;


		/*	Set default userdata and callback functins.	*/
		pool[x].initcallback = (VDTaskInitCallback)VDTaskSchedule::initializefunc;
		pool[x].deinitcallback = (VDTaskdeinitCallback)VDTaskSchedule::deinitializefunc;
		pool[x].userdata = VDEngine::querySharedOpenGLContext();


		/*	*/
		pool[x].thread = SDL_CreateThread((SDL_ThreadFunction)VDTaskSchedule::poolexecutor, "",  (void*)&this->pool[x]);
		if(pool[x].thread != NULL){
			sprintf(buf, "task_schedule%d", x);
			buf[15] = '\0';
			//ExSetThreadName(pool[x].thread, buf);
			VDDebug::log("Created task thread : %d\n", x);
		}else{
			VDDebug::errorLog("Failed to create thread : %d\n", x);
		}
	}
}

void VDTaskSchedule::setPoolUserData(unsigned int index, void* userdata){
	if(index > (num - 1)){
		return;
	}
	pool[index].userdata = userdata;
}

void VDTaskSchedule::setInitPoolCallBack(int index, int (*initcallback)(struct task_pool*)){
	if(index > (num - 1)){
		return;
	}
	pool[index].initcallback = (VDTaskInitCallback)initcallback;
}

bool VDTaskSchedule::runTaskSch(void){
	if(this->num == 0 || this->pool == NULL)
		return false;

	for(int x = 0; x < this->getNumTaskPool(); x++){
		pthread_kill( SDL_GetThreadID( pool[x].thread ), eContinue);
	}
	return true;
}

int VDTaskSchedule::terminateTaskSch(void){

	unsigned int status = SDL_TRUE;

	if(this->num == 0 || this->pool == NULL){
		return false;
	}

	for(int x = 0; x < this->getNumTaskPool(); x++){
		if(pool[x].thread != NULL){
			this->clearQueue(x);
			pthread_kill(SDL_GetThreadID( pool[x].thread ), VDTaskSchedule::eQuit);
			//ExTerminateThread(pool[x].thread);
		}
	}

	/*	wait intill the thread has been killed.	*/
	for(int x = 0; x < this->getNumTaskPool(); x++){
		if(pool[x].thread != NULL){
			//SDL_WaitThread(this->pool[x].thread, NULL);
			this->pool[x].thread = NULL;
		}
	}

	return status;
}


static void dheap_pool(VDTaskSchedule* task){
	for(int x = 0; x < task->getNumTaskPool(); x++){

	}
}

void VDTaskSchedule::submitTask(VDTaskPackage* package){

	if(package == NULL || package->callback == NULL){
		throw std::invalid_argument("Invalid argument.\n");
	}

	dheap_pool(this);
	//poolIndex = dheap[0];
	int poolIndex = rand() % num;
	register VDTaskPool* submitpool = &this->pool[poolIndex];

	/*	debugging info.	*/
	if(VDDebug::isDebugBuild()){
		VDDebug::log("Submitting package : size %d, index : %d\n", package->size, poolIndex);
	}

	/*	*/
	memcpy(submitpool->back, package, sizeof(VDTaskPackage));
	submitpool->back->pool = submitpool;
	while(submitpool->numqueue >= submitpool->reserved){

	}

	/*	*/
	submitpool->back = submitpool->package + ((submitpool->back - submitpool->package) % (submitpool->size));
	submitpool->numqueue++;
	submitpool->back++;
	submitpool->totalPackages++;
	sem_post((sem_t*)submitpool->semaphore);


	/*	send signal for continue computing if thread is sleeping.	*/
	//pthread_kill( SDL_GetThreadID( submitpool->thread ), VDTaskSchedule::eContinue);
}

void VDTaskSchedule::clearQueue(int index){
	if(index > getNumTaskPool())
		VDDebug::warningLog("Out of range.\n");

	/*	*/
	pool[index].back = pool[index].front = pool[index].package;
	pool[index].numqueue = 0;
}


void VDTaskSchedule::wait(void){
	int signal;
	for(int x = 0; x < getNumTaskPool(); x++){
		sigwait((const sigset_t*)getTaskPool(x)->set, &signal);
	}
}

unsigned int VDTaskSchedule::getNumTaskPool(void)const{
	return this->num;
}


VDTaskSchedule::VDTaskPool* VDTaskSchedule::getTaskPool(void)const{
	return this->pool;
}

VDTaskSchedule::VDTaskPool* VDTaskSchedule::getTaskPool(int index)const{
	return &this->pool[index];
}

unsigned int VDTaskSchedule::getFlag(void)const{return this->flag;}




VDHANDLE VDTaskSchedule::poolexecutor(void* handle){

	/*	TODO resolve somehow.	*/
	sigset_t* set = (sigset_t*)malloc(sizeof(*set));
	assert(set);


	sigemptyset(set);
	sigaddset(set, eContinue);
	sigaddset(set, eDone);
	sigaddset(set, eQuit);
	pthread_sigmask(SIG_BLOCK, set, NULL);


	/*	*/
	int signal;
	const unsigned int SigQuit = VDTaskSchedule::eQuit;
	register VDTaskSchedule::VDTaskPool* pool = (VDTaskSchedule::VDTaskPool*)handle;
	pool->set = set;


	/*	*/
	if( pool == NULL ){
		VDDebug::errorLog("Thread parameter NULL.\n");
		VDDebug::errorLog("Terminating thread : %s.\n", SDL_GetThreadName(pool->thread));
		goto error;/**/
	}


	/**/
	//ExSetThreadSignal(pool->schThread, eDone);
	pthread_kill(pool->schThread, ThreadSignal::eDone);
	sigwait(set, &signal);

	/*	Initialize callback */
	if(pool->initcallback != NULL)
		pool->initcallback(pool);


	/*	main iterative loop.	*/
	do{
		if(pool->front != pool->back){
			pool->numqueue = pool->front >= pool->back ? (pool->front - pool->back) : (pool->back - pool->front);
			pool->front = pool->package + ((pool->front - pool->package) % pool->size );
			pool->front->callback((VDTaskSchedule::VDTaskPackage*)pool->front);	/*	TODO fix data type.*/
			pool->front++;
		}
		else{

			/*	send signal to main thread, that pool is finished.	*/
			//ExSetThreadSignal(pool->schThread, ThreadSignal::eDone);
			//pthread_kill(pool->schThread, ThreadSignal::eDone);
			/*	*/
			setPoolIdle(pool);
			do{
				/*	wait for signal from scheduler.	*/
				sem_trywait((sem_t*)pool->semaphore);
				sem_wait((sem_t*)pool->semaphore);
				//sigwait(set, &signal);
				if(signal == SigQuit){
					VDDebug::debugLog("Quitting task schedule thread of core %d\n", pool->index);
					goto error;
				}
			}while(signal != eContinue);

			/*	set pool as running.	*/
			setPoolRunning(pool);
		}
	/**/
	}while(SDL_TRUE);

	error:	/*	failure.	*/

	/*	clean up.	*/
	if(pool->deinitcallback != NULL){
		pool->deinitcallback(pool);
	}

	free(set);

	return NULL;
}

void VDTaskSchedule::setPoolRunning(VDTaskSchedule::VDTaskPool* pool){
	pool->flag |= eRunnig;
	pool->flag = pool->flag & ~eSleep;
}

void VDTaskSchedule::setPoolIdle(VDTaskSchedule::VDTaskPool* pool){
	pool->flag = pool->flag & ~eRunnig;
	pool->flag |= eSleep;
}



bool VDTaskSchedule::initializefunc(VDTaskPool* pool){
	if(pool != NULL && pool->userdata != NULL){
		VDEngine::bindOpenGLContext(*(VDOpenGLContext*)pool->userdata);
		return true;
	}
	return false;
}

bool VDTaskSchedule::deinitializefunc(VDTaskPool* pool){
	if(pool && pool->userdata){
		VDEngine::returnOpenGLContext((SDL_GLContext*)pool->userdata);
		return true;
	}
	return false;
}


void VDTaskSchedule::lock(VDTaskPool* pool){
	SDL_LockMutex((SDL_mutex*)pool->mutex);
}

void VDTaskSchedule::unLock(VDTaskPool* pool){
	SDL_TryLockMutex((SDL_mutex*)pool->mutex);
}
