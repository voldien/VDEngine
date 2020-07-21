/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_TASK_SCHEDULE_H_
#define _VD_TASK_SCHEDULE_H_ 1
#include"../VDDef.h"
#include"../VDSimpleType.h"
#include <pthread.h>
#include <signal.h>

struct SDL_Thread;

/**
 *	Task schedular responsible for
 *	distributing task on all CPU
 *	core evenly.
 */
class VDDECLSPEC VDTaskSchedule{
public:

	enum ThreadSignal{
		eStop = SIGQUIT,		/*	*/
		eQuit,					/*	*/
		eStart,					/*	*/
		eContinue = SIGUSR1,	/*	*/
		eDone = SIGUSR2,		/*	*/
	};

	enum PoolFlag{
		eSleep 	= 0x1,	/*	*/
		eRunnig = 0x2,	/*	*/
	};

	/**
	 *
	 */
	struct vd_task_pool;
	struct vd_task_package;
	typedef int (*VDTaskCallback)(struct vd_task_package* package);
	typedef int (*VDTaskInitCallback)(struct vd_task_pool*);
	typedef int (*VDTaskdeinitCallback)(struct vd_task_pool*);

	/**
	 *
	 */
	typedef struct vd_task_package{

		unsigned int size;	/*	size in bytes of the package.	*/
		unsigned int offset;	/*	*/
		unsigned int flag;	/*	Attribute flag.	*/
		VDTaskCallback callback;	/*	callback function.	*/
		union{
			void* begin;
			char* cbegin;	/*	begin iterator.	*/
		};
		union{
			void* end;	/*	end iterator.	*/
			void* cend;
		};
		void* pool;		/*	*/

	}VDTaskPackage;

	/**
	 *
	 */
	typedef struct vd_task_pool{

		SDL_Thread* thread;		/*	*/
		unsigned int coreIndex;	/*	core index.	*/
		pthread_t schThread;	/*	Thread schedular binded too. */
		unsigned int flag;

		/*
		 *	package queue.
		 */
		//struct{
			unsigned int size;
			unsigned int numqueue;
			VDTaskSchedule::VDTaskPackage* front;		/*	*/
			VDTaskSchedule::VDTaskPackage* back;		/*	TODO make atomic data type. */
			unsigned int reserved;
			VDTaskSchedule::VDTaskPackage* package;
			unsigned long int totalPackages;
			unsigned long int maxpackageSize;
		//};

		void* mutex;				/*	mutex.	*/
		void* atomiccounter;		/*	*/
		void* semaphore;			/*	*/
		void* set;					/*	*/
		void* userdata;				/*	user data.	*/
		VDTaskInitCallback initcallback;
		VDTaskdeinitCallback deinitcallback;
		VDTaskSchedule* sch;		/*	Pointer to task schedule object.	*/
		unsigned int index;			/*	CPU index, 0,n.*/

	}VDTaskPool;

public:
	VDTaskSchedule(void);
	VDTaskSchedule(const VDTaskSchedule& task);
	~VDTaskSchedule(void);

	/**
	 *	Release resources assiociated with object.
	 */
	void VDAPIENTRY release(void);

	/**
	 *	Initialize task schedule.
	 */
	void VDAPIENTRY init(int cores, unsigned int flags = 0, unsigned int maxPackagesPool = 16384);

	/**
	 *	Set userdata assoicated with the CPU
	 *	index.
	 */
	void VDAPIENTRY setPoolUserData(unsigned int index, void* user);

	/**
	 *	Set callback that will be executed prior to
	 *	the scheduler main routine.
	 */
	void VDAPIENTRY setInitPoolCallBack(int index, int (*initcallback)(struct task_pool*));

	/**
	 * 	Starts task scheduler.
	 *
	 *	@Return true if schedule is running.
	 */
	bool VDAPIENTRY runTaskSch(void);

	/**
	 *	@Return termination status.
	 */
	int VDAPIENTRY terminateTaskSch(void);

	/**
	 *	Submit task to be executed.
	 */
	void VDAPIENTRY submitTask(VDTaskPackage* package);

	/**
	 *	Submit task to be executed on a specified task pool.
	 */
	void VDAPIENTRY submitTask(VDTaskPackage* package, VDTaskPool* pool);

	/**
	 *	Clear queue on the pool.
	 *
	 *	\index index of the pool to be cleared.
	 */
	void VDAPIENTRY clearQueue(int index);

	/**
	 *	Set current thread in sleep till all
	 *	of the pool schedule has finished.
	 */
	void VDAPIENTRY wait(void);

	/**
	 *	@Return number of task pool.
	 */
	unsigned int VDAPIENTRY getNumTaskPool(void)const;

	/**
	 *	Get task pool.
	 */
	VDTaskPool* VDAPIENTRY getTaskPool(void)const;

	/**
	 *	Get task pool by the index.
	 */
	VDTaskPool* VDAPIENTRY getTaskPool(int index)const;

	/**
	 *	@Return flag of task scehdule.
	 */
	unsigned int VDAPIENTRY getFlag(void)const;

private:	/*	Attributes.	*/

	unsigned int num;		/*	Number of task pools.	*/
	struct vd_task_pool* pool;	/*	Task pool pointer.	*/
	VDTaskPool** dheap;		/*	DHeap.	*/
	unsigned int flag;		/*	task schedule flag.	*/


public:	/*	static methods.	*/


	/**
	 *	Main shedular function.
	 */
	static VDHANDLE VDAPIENTRY poolexecutor(void* handle);

	/**
	 *
	 */
	static void VDAPIFASTENTRY setPoolRunning(VDTaskPool* pool);

	/**
	 *
	 */
	static void VDAPIFASTENTRY setPoolIdle(VDTaskPool* pool);

	/**/
	static bool VDAPIENTRY initializefunc(VDTaskPool* pool);
	static bool VDAPIENTRY deinitializefunc(VDTaskPool* pool);

	/**
	 *	Lock task pool.
	 */
	static void VDAPIFASTENTRY lock(VDTaskPool* pool);

	/**
	 *	Unlock task pool.
	 */
	static void VDAPIFASTENTRY unLock(VDTaskPool* pool);

};

#endif
