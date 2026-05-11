//===========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2004                                          
//===========================================================================
//                                                                           
//  Compound Files                                                     
//                                                                           
//  Usage Notes: Services functions
//===========================================================================
//  Creation aout 2004                                 adt              
//===========================================================================
#ifndef __CAASYSFILEFUNC
#define __CAASYSFILEFUNC

#include <string.h>
#include <errno.h>
#include <time.h>
#include "CATUnicodeString.h"
#include "CATIUExitCryptedILockBytes.h"



#ifdef _WINDOWS_SOURCE
#define ERRNO		GetLastError()
#define SEEKSET		FILE_BEGIN
#define SEEKCUR		FILE_CURRENT
#define SEEKEND		FILE_END
#else
#define ERRNO		errno
#define SEEKSET		SEEK_SET
#define SEEKCUR		SEEK_CUR
#define SEEKEND		SEEK_END
#endif


// some macros 
#ifdef _WINDOWS_SOURCE
#define FILEWRITE( fd, buf, length) 	   CAASysFileWrite ( fd, buf, length)
#define FILEREAD( fd, buf, length) 	   CAASysFileRead ( fd, buf, length)
#define FILESEEK( fd, Offset, Pos)	   CAASysFileSeek ( fd, Pos, Offset)
#define FILECLOSE( fd)			   CAASysFileClose(fd)
#else
#define FILEWRITE( fd, buf, length)	write(fd, buf, length)
#define FILEREAD( fd, buf, length)	read(fd, buf, length)
#define FILESEEK( fd, Offset, Pos)	lseek64 ( fd, Offset.QuadPart, Pos)
#define FILECLOSE( fd)			close (fd)
#endif


#ifdef _WINDOWS_SOURCE
long CAASysFileWrite (HANDLE  fd, const char* buf, ULONG ToWrite);
long CAASysFileRead (HANDLE  fd, char* buf, ULONG ToRead);
long CAASysFileSeek (HANDLE  fd, DWORD Pos, ULARGE_INTEGER Offset);
HRESULT CAASysFileFlush ( HANDLE fh);
HRESULT CAASysFileOpen( const CATUnicodeString *iPath,  
			CATSysOpenMode iOpenMode, 
			CATSysSharing iSharingMode, 
			CATSysCreateMode iOpenFlag, 
			CATSysCloseMode iCloseFlag,
			HANDLE &fh); 

HRESULT CAASysFileClose ( HANDLE fh);
HRESULT CAASysFileResize ( HANDLE  fd, ULARGE_INTEGER iOffset);

#else
HRESULT CAASysFileOpen ( const CATUnicodeString *iPath, 
			 CATSysOpenMode iOpenMode, 
			 CATSysSharing iSharingMode, 
			 CATSysCreateMode iOpenFlag, 
			 CATSysCloseMode iCloseFlag,
			 int &fd);

HRESULT CAASysFileResize ( int  fd, ULARGE_INTEGER iOffset);
HRESULT CAASysFileFlush ( int fd);

void CAASysConvertTime( time_t iS, FILETIME *otime);
#endif


#endif
