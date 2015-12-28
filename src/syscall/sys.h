#ifndef SYS_H
#define SYS_H

/** @file sys.h
 * @brief System calls for user-mode applications to interface with kernel.
 * These are the 17 minimum required for newlib.  Additional ones will be added as needed.
 */

#define SYSCALL_INT		0x30

#define SYS_EXIT		0x1
#define SYS_FORK		0x2
#define SYS_KILL		0x3
#define SYS_GETPID		0x4
#define SYS_READ		0x5
#define SYS_WRITE		0x6
#define SYS_OPEN		0x7
#define SYS_CLOSE		0x8
#define SYS_EXECVE		0x9
#define SYS_FSTAT		0xA
#define SYS_STAT		0xB
#define SYS_LINK		0xC
#define SYS_UNLINK		0xD
#define SYS_LSEEK		0xE
#define SYS_SBRK		0xF
#define SYS_TIMES		0x10
#define SYS_WAIT		0x11

/** Simulate a syscall 
 */
void syscall_test( uint32 eax, uint32 ebx, uint32 ecx, uint32 edx );

/** Sets up the interrupt for system calls
 */
void syscall_init( );

/** Exits the current process without cleaning up files
 * @param nExit Exit code
 */
void sys_exit( int32 nExit );

/** Creates a new process
 * @return PID of new process
 */
int32 sys_fork( );

/** Kills a process
 * @param nPID Process ID to kill
 * @param nSignal Posix signal to send
 * @return -1 on fail, 0 on success
 */
int32 sys_kill( int32 nPID, int32 nSignal );

/** Returns the PID of the running process
 */
int32 sys_getpid( );

/** Reads from a file into a buffer
 * @param nFd File that has been previously opened
 * @param pBuffer Buffer into which file contents will be read to
 * @param nLength Maximum length to read into
 * @return -1 on fail, 0 on success
 */
int32 sys_read( int32 nFd, char* pBuffer, int32 nLength );

/** Writes into a file from a buffer
 * @param nFd File that has been previously opened
 * @param pBuffer Buffer to write into file from
 * @param nLength Length of buffer to write
 * @return -1 on fail, 0 on success
 */
int32 sys_write( int32 nFd, char* pBuffer, int32 nLength );

/** Opens a file for reading or writing
 * @param szFilename File to open
 * @param nFlags Opening file for read/write and various options
 * @param nMode Permissions in case a new file is created
 * @return -1 on fail, 0 on success
 */
int32 sys_open( const char* szFilename, int32 nFlags, int32 nMode );

/** Closes a file
 * @param nFd File to close
 * @return -1 on fail, 0 on success
 */
int32 sys_close( int32 nFd );

/** Transfer control to a new process
 * @param szName Filename of new process
 * @param szArrArgv Null terminated array of arguments to be passed
 * @param szArrEnv Null terminated array of environmental variables
 * @return -1 on fail, 0 on success
 */
int32 sys_execve( char* szName, char** szArrArgv, char** szArrEnv );

/** Get status of an opened file
 * @param nFd File
 * @param pStat Pointer to stat structure
 * @return -1 on fail, 0 on success
 */
int32 sys_fstat( int32 nFd, void* pStat );

/** Get status of an unopened file
 * @param szFilename Filename
 * @param pStat Pointer to stat structure
 * @return -1 on fail, 0 on success
 */
int32 sys_stat( char* szFilename, void* pStat );

/** Create a link between two files
 * @param szFileOld File to be linked from
 * @param szFileNew New file to be created
 * @return -1 on fail, 0 on success
 */
int32 sys_link( char* szFileOld, char* szFileNew );

/** Remove a link to a file
 * @param szFilename Filename of the file to be deleted
 * @return -1 on fail, 0 on success
 */
int32 sys_unlink( char* szFilename );

/** Seek to different part of file
 * @param nFd File
 * @param nOffset Offset in bytes
 * @param nDirection Starting point
 * @return -1 on fail, 0 on success
 */
int32 sys_lseek( int32 nFd, int32 nOffset, int32 nDirection );

/** Increase program data space
 * @param nIncr Amount in bytes to increase by
 * @return -1 on fail, 0 on success
 */
int32 sys_sbrk( int32 nIncr );

/** Gets time information
 * @return -1 on fail, 0 on success
 */
int32 sys_times( void* pBuffer );

/** Wait for any child process' status to change
 * @param pStatus Status of child
 * @return -1 on fail, 0 on success
 */ 
int32 sys_wait( int32* pStatus );

#endif
