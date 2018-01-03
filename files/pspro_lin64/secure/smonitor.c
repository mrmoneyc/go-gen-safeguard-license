#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>

#if defined(__WIN32) || defined(__WIN64)

#include <windows.h>


  #define MUTEX_VAR HANDLE
  #define MUTEX_INIT(m) (m=CreateMutex(0,FALSE,0))
  #define MUTEX_LOCK(m) WaitForSingleObject(m,INFINITE)
  #define MUTEX_UNLOCK(m) ReleaseMutex(m)
  #define MUTEX_DESTROY(m) CloseHandle(m)
  #define PTHREAD_T DWORD
  #define PTHREAD_ATTR_T DWORD
  #define PTHREAD_ATTR_INIT(a) //
  #define THREAD_CREATE(a,b,c,d) CreateThread(0,0,(LPTHREAD_START_ROUTINE)c,d,0,a)
  #define THREAD_EXIT() ExitThread(0)
  #define THREAD_JOIN(a) WaitForSingleObject((HANDLE)a,(DWORD)1000)
  #define THREAD_RETURN return(0)
  #define THREAD_FUNC(a) DWORD WINAPI _uu_gcc__ (LPVOID a)
  #define SLEEP(a) SleepEx(a * 1000,FALSE)
  #define TERMINATE ExitProcess(0)

  DWORD WINAPI _uu_gcc__ (LPVOID threadarg);

#pragma section(".CRT$XCU",read)
#define INITIALIZER(__UUID64) \
   static void __cdecl __UUID64(void); \
   __declspec(allocate(".CRT$XCU")) void (__cdecl*f##_)(void) = __UUID64; \
   static void __cdecl __UUID64(void)


void __UUID32x(void);
int _ccclip (int locale);
void __stat_system(char *uuid);

#else

#include <pthread.h>
#include <unistd.h>

  #define MUTEX_VAR pthread_mutex_t
  #define MUTEX_INIT(m) pthread_mutex_init(&m, NULL)
  #define MUTEX_LOCK(m) pthread_mutex_lock(&m)
  #define MUTEX_UNLOCK(m) pthread_mutex_unlock(&m)
  #define MUTEX_DESTROY(m) pthread_mutex_destroy(&m)
  #define PTHREAD_T pthread_t
  #define PTHREAD_ATTR_T pthread_attr_t
  #define PTHREAD_ATTR_INIT(a) pthread_attr_init(a)
  #define THREAD_CREATE(a,b,c,d) pthread_create(a,b,(void *)c,(void *)d)
  #define THREAD_EXIT() pthread_exit(NULL)
  #define THREAD_JOIN(a) pthread_join( a, NULL)
  #define THREAD_RETURN return(0)
  #define THREAD_FUNC(a) void *_uu_gcc__ (void *a)
  #define SLEEP(a) sleep(a)
  #define TERMINATE exit(0)

  void *_uu_gcc__ (void *threadarg);

// __UUID64() function call is made automatically by the GNU compiler
// and the Windows runtime.
// It will start a separate thread that will monitor a static location
// in memory to see whether it has been changed from the "hacked" state
// to the "not-hacked" state, where the "hacked" state is the default.
// In other words, when any one of the license check/checkout/activation
// functions are called, they will inform this thread that they performed
// their job correctly and therefore, there is no need to terminate the
// application.  Currently, the destructor does nothing, but you may want
// to implement something there.

#define INITIALIZER(__UUID64) \
   static void __UUID64(void) __attribute__((constructor)); \
   static void __UUID64(void)

void __UUID32(void);
int _ccclip (int locale);
void __stat_system(char *uuid);

#endif

MUTEX_VAR mutexlock_snap;

static char _snap_ptr[2];

struct thread_data
{
  int thread_id;
};



void __stat_system(char *uuid)
{
    static struct thread_data thread_data_array;
    PTHREAD_T threads;
    PTHREAD_ATTR_T attr;

    // this one is for when you don't want to wait 10 seconds.
    //printf("__stat_system\n");

    PTHREAD_ATTR_INIT(&attr);

    threads = 0;
    thread_data_array.thread_id = 0;
    THREAD_CREATE(&threads, &attr, _uu_gcc__, &thread_data_array);
    THREAD_JOIN(threads);   
    return;
}

int _ccclip (int locale)
{

  // if called with a non-zero locale, the monitor thread will
  // exit and let the application continue to run.  If it is
  // called with zero, it basically tells the monitor thread
  // to kill the application.

  MUTEX_LOCK(mutexlock_snap);
  if (locale) {
    _snap_ptr[0] = '-';
  } else {
    _snap_ptr[0] = '?';
    //printf("returning from cclip: %c\n",_snap_ptr[0]);
  }
  MUTEX_UNLOCK(mutexlock_snap);
  return (0);
}


void __UUID32(void)
{
  // destructor function called when a GNU application terminates
  //printf("destructor\n");
}


INITIALIZER(initialize)
{
    static struct thread_data thread_data_array;
    PTHREAD_T threads;
    PTHREAD_ATTR_T attr;

    MUTEX_INIT(mutexlock_snap);

    atexit(__UUID32);

  // constructor function called when a GNU application starts

    // set the default value of the special memory location to the
    // BAD state.  We wait for the *real* license functions to change
    // it to the GOOD state.  Otherwise, the app is terminated 

    MUTEX_LOCK(mutexlock_snap);
    _snap_ptr[0] = '?';
    MUTEX_UNLOCK(mutexlock_snap);

    // set the callbacks for the license check functions to call us
    // when a license check function is successfully called.
    // the first function will wait 10 seconds before doing the check,
    // the second function will not wait (your choice)

    // The developer can either just let us do the 10 second wait, or
    // he can make calls in his code after the license checks by himself.

    sg_getlocale(_ccclip,__stat_system);

    PTHREAD_ATTR_INIT(&attr);

    //printf("constructor\n");

    // create the thread that monitors the shared area for the update
    // from the real license functions.
    threads = 0;
    thread_data_array.thread_id = 1;
    THREAD_CREATE(&threads, &attr, _uu_gcc__, &thread_data_array);
    return;
}

/*******************************************************************
*
* this monitors license activity for any hacking attempts
*
*******************************************************************/

THREAD_FUNC(threadarg)
{

   char x[1];
   int i;
   struct thread_data *my_data;
  
   my_data = (struct thread_data *) threadarg;
   

   //printf("Monitor thread started.. %d\n",my_data->thread_id);

   // wait for 10 seconds and then see if we have been notified from sgAuthorized or sgCheckout,
   // sgTest, sgShowClient, sgShowServer, sgPaActivate, sgPaGetDemoActivationKeys, 
   // sgPaGetPaidActivationKeys, etc.. If we have and they are ok with everything, then there 
   // is no need to stick around. If after this period of time, other things have been called but 
   // not some things, then exit.


   if (my_data->thread_id != 0) { 
     SLEEP(10);  // You may want to adjust this time
   }

   // if '-', we are good to go.
   MUTEX_LOCK(mutexlock_snap);
   if (_snap_ptr[0] == '-') {
       MUTEX_UNLOCK(mutexlock_snap);
       goto done;
   }
   MUTEX_UNLOCK(mutexlock_snap);


   // exit nicely.  exit nasty if someone nop's
   // the following exit() call.

   //printf("License circumvention check BAD...\n");
   TERMINATE;

   // seg fault if someone nop's the previous exit() call
again:
   i =(2145*1000000)+342113;
   x[0+i]=x[0-i];
   goto again;
   exit(0);
   goto again;

done:
   //printf("License circumvention check OK...\n");
   THREAD_EXIT();
   THREAD_RETURN;

}
