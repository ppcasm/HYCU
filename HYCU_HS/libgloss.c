#include <sys/types.h>
#include <sys/stat.h>
/*
      * read  -- read bytes from the serial port. Ignore fd, since
      *          we only have stdin.
      */
int
_read_r (struct _reent *r, int fd, char *buf, int nbytes)
{
     return -1;

}

/*
      * write -- write bytes to the serial port. Ignore fd, since
      *          stdout and stderr are the same. Since we have no filesystem,
      *          open will only return an error.
      */
int
_write_r (struct _reent *r, int fd, char *buf, int nbytes)
{
     return -1;
}

/*
      * open -- open a file descriptor. We don't have a filesystem, so
      *         we return an error.
      */
int
_open_r (struct _reent *r, char *buf, int flags, int mode)
{
     return -1;
}

/*
      * close -- close a file descriptor. We don't need
      *          to do anything, but pretend we did.
      */
int
_close_r (struct _reent *ptr, int fd)
{
     return -1;
}

#if 1
/*
      * exit
      *          
      */
void
_exit ( extcode)
     
     int extcode;
{
}
#endif

/*
 * sbrk -- changes heap size size. Get nbytes more
 *         RAM. We just increment a pointer in what's
 *         left of memory on the board.
 */
char *
_sbrk_r (struct _reent *ptr, int nbytes)
{
     return NULL;
}


/*
      * lseek -- move read/write pointer. Since a serial port
      *          is non-seekable, we return an error.
      */
off_t
_lseek_r (struct _reent *ptr, int fd, off_t offset, int whence)
{
     return -1;
}

/*
      * fstat -- get status of a file. Assume it is a
      * terminal (character special file).
      */
int
_fstat_r (struct _reent *r, int fd, struct stat *buf)
{
     return -1;
}


int
isatty (int fd)

{
  
	 return fd == 0 || fd == 1 || fd == 2;

}

/*
      * getpid -- only one process, so just return 1.
      */

#define __MYPID 1

int
_getpid ()

{
  
	return __MYPID;

}

int
_getpid_r ()

{
  
	return __MYPID;

}


/*
      * kill -- go out via exit...
      */

int
_kill (int pid, int sig)

{
  
	 if (pid == __MYPID)
    //_exit(sig);
	 
    return 0;
	 return -1;
    

}

int
_kill_r (int pid, int sig)

{
  
	 if (pid == __MYPID)
    //_exit(sig);
	 
    return 0;
	 return -1;
    

}
