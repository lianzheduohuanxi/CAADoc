 /*
 * @fullreview VEL 07:10:22
 */
// COPYRIGHT Dassault Systemes 2007
//===================================================================
//
// CAAPDMUEResId.cpp
// Implement the CATIPDMUEResId interface
//
//===================================================================
#include "CAAPDMUEResId.h"

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIPDMUEResId.h"
TIE_CATIPDMUEResId(CAAPDMUEResId);

CATImplementClass(CAAPDMUEResId,
		  CodeExtension,
		  CATBaseUnknown,
		  CATUEPDMResId);
 


//-----------------------------------------------------------------------------

 //-----------------------------------------------------------------------------
/* CDM                                                                 */
/*  VERSION 1 RELEASE 2.0                                              */
/*  COPYRIGHT DASSAULT SYSTEMES 1991                                   */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* IDENTIFICATION :                                                    */
/* --------------                                                      */
/*                                                                     */
/*    RESPONSIBLE :                                                    */
/*    FUNCTION    :                                                    */
/*    USAGE       :  CDM-API                                           */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* FUNCTION :                                                          */
/* --------                                                            */
/*                                                                     */
/*     :P.GENERATION OF A SYSTEM IDENTIFIER AS UNIQUE AS               */
/*        POSSIBLE.                                                    */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* COMMENTS :                                                          */
/* --------                                                            */
/*                                                                     */
/*     :P.GENERATION OF A SYSTEM IDENTIFIER AS UNIQUE AS               */
/*        POSSIBLE.                                                    */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/*                                                                     */
/* DECLARATION :                                                       */
/* ------------                                                        */
/*                                                                     */
/*    CALL DBSYSI ( CSYSID )                                           */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* ARGUMENTS :                                                         */
/* ----------                                                          */
/*                                                                     */
/* ARG*   0001 O C*8    CSYSID := SYSTEM IDENTIFIER                    */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* HISTORY :                                                           */
/* -------                                                             */
/*                                                                     */
/*    MODIF NUMBER :                                                   */
/*    DATE         :                                                   */
/*    TYPE         :                                                   */
/*    BUT          :                                                   */
/*    AUTEUR       :                                                   */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* KEYWORDS :                                                          */
/* --------                                                            */
/*                                                                     */
/* DATABASE - IDENTIFIER - GENERATION                                  */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* REFERENCES :                                                        */
/* ------------                                                        */
/*                                                                     */
/* CDM ADMINISTRATION GUIDE                                            */
/* CDM REFERENCE      MANUAL                                           */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* REFERENCED COMMONS :                                                */
/* -------------------                                                 */
/*                                                                     */
/* NONE                                                                */
/*                                                                     */
/*------------------------------------------------------------         */
/*                                                                     */
/* ERRORS :                                                            */
/* -------                                                             */
/*                                                                     */
/* NONE                                                                */
/*                                                                     */
/*-------------------------------------------------------------        */
/*                                                                     */
/* CALLED SYSTEM SUBROUTINES :                                         */
/* -------------------------                                           */
/*   time                                                              */
/*   sleep                                                             */
/*   srand                                                             */
/*   rand                                                              */
/*                                                                     */
/*-------------------------------------------------------------        */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAPDMUEResId::CAAPDMUEResId():
	CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAPDMUEResId::~CAAPDMUEResId()
{
}
#include <time.h>
#ifdef _WINDOWS_SOURCE

#else
#include <sys/utsname.h>
#include <sys/time.h>
#ifdef _SUNOS_SOURCE 
extern "C" int usleep (unsigned int);
#endif
#ifdef _IRIX_SOURCE  
extern "C" int usleep (unsigned int);
#endif
#endif

#ifdef  _WINDOWS_SOURCE  
#      define  sleep(x)  Sleep(1000*(x))  
#else  
#      include  <unistd.h>  
#endif  


#define AUGUST_16_90        650347849
#define MAX_TWO_BYTE_NUMBER 65536

#undef TRUE
#undef FALSE
#define TRUE                1
#define FALSE               0


//-----------------------------------------------------------------------------
CATDbBinary CAAPDMUEResId::CreateId ()
{
  // réservation d'uuid. Duplication du code V4 de VPM : dbsysi.c
  char coid [8];
  union {
    CATLONG32 ltime;
    char ctime[8];
    struct {
      int lo;
      int hi;
    } itime ;
  } t ;
  union {
    CATLONG32  number ;
    char character [4];
  } random ;
  short l ;
  
  /*-----------------------------------------------------------------------------------------------  */
  /* You should use the first two characters of the eight-			                     */
  /* character identifier to distinguish your CDM installation		                             */
  /* from a CDM installation on another site.							     */
  /*												     */
  /* These two characters are customized by the script shell		                             */
  /* dbuecl during the installation procedure.							     */
  /*------------------------------------------------------------------------------------------------ */
  static char site_id [] =   "==" ;
  
  static int first = TRUE ;
  static int last_time = 0 ;
  static int random_number = 0 ;
  static int last_random_number = 0 ;
  
  /*-----------------------------------------------------------------------------------------------*/
  /* srand subroutine initializes the random number generator      */
  /*-----------------------------------------------------------------------------------------------*/
  if ( first == TRUE )
    {
      first = FALSE ;
      t.ltime = time ((time_t*) 0) ;
#ifdef _WINDOWS_SOURCE
      l = t.ctime [0];
#else
      l = t.ctime [3];
#endif
      srand ( (unsigned) l ) ;
    }
  
  /*-----------------------------------------------------------------------------------------------*/
  /* these instructions return the time in seconds since                */
  /* august 16 1990.                                                                    */
  /*-----------------------------------------------------------------------------------------------*/
  t.ltime = time ((time_t *) 0) ;
  t.itime.lo = t.itime.lo - AUGUST_16_90 ;
  
  /*-----------------------------------------------------------------------------------------------*/
  /* last_time variable ensures that t.time.lo is always                   */
  /* greater than the previously generated identifiers.                   */
  /* This algorithm can generate up to 65536 identifiers per         */
  /* second.								 */
  /*-----------------------------------------------------------------------------------------------*/
  if ( t.itime.lo == last_time )
    {
      random_number ++ ;
      if ( random_number == MAX_TWO_BYTE_NUMBER ) random_number = 0 ;
      if ( random_number == last_random_number ) {
        /*-----------------------------------------------------------------------------------------------*/
	/* More than 65536 identifiers per second were						  */
	/* generated.																			  */
	/* Stop the program for one second before creating the			 */
	/*  next identifier.																	   */
        /*-----------------------------------------------------------------------------------------------*/
#ifdef _WINDOWS_SOURCE // on s'inspire de CATSleep  ( cf JS0LibServices.cpp de System )
	Sleep (1) ;
#elif defined(_AIX) || defined(_SUNOS_SOURCE) || defined(_IRIX_SOURCE)
	int status;
	status = usleep(1000); 
#elif defined(_HPUX_SOURCE)
	struct timespec hpt, hptret;
	hpt.tv_sec=1;
	hpt.tv_nsec=(1000%1000)*1000000;
	int status;
	status = nanosleep(&hpt, &hptret);
#endif
	t.ltime = time ((time_t*) 0) ;
	t.itime.lo = t.itime.lo - AUGUST_16_90 ;
	last_time = t.itime.lo ;
	random_number = rand () % MAX_TWO_BYTE_NUMBER ;
	last_random_number = random_number ;

      }
    }
  else {
    last_time = t.itime.lo ;
    random_number = rand () % MAX_TWO_BYTE_NUMBER ;
    last_random_number = random_number ;
  }
  
  // - RLB - 553645 - if random < 256 then problem cause CATUnicodeString will be
  //                  strip due to the 00 binary. so we forbid the 00 binary
  if (random_number <= 255) {
    random_number = 256;
    last_random_number = random_number ;
  }
  
  /*-----------------------------------------------------------------------------------------------*/
  /* First two characters are the CDM installation ID                    */
  /*-----------------------------------------------------------------------------------------------*/
  coid [0] = site_id [0] ;
  coid [1] = site_id [1] ;
  
  /*-----------------------------------------------------------------------------------------------*/
  /* Next four characters are the number of seconds since          */
  /* august 16 1990.																       */
  /* We add 128 to the first character to avoid regenerating	      */
  /* the identifiers created by the previous version of				    */
  /* this user exit (CDM 1.2.0).													    */
  /*-----------------------------------------------------------------------------------------------*/
#ifdef _WINDOWS_SOURCE
  coid [2] = t.ctime [3] + 128 ;
  coid [3] = t.ctime [2] ;
  coid [4] = t.ctime [1] ;
  coid [5] = t.ctime [0] ;
#else
  coid [2] = t.ctime [0] + 128 ;
  coid [3] = t.ctime [1] ;
  coid [4] = t.ctime [2] ;
  coid [5] = t.ctime [3] ;
#endif
  
  /*-----------------------------------------------------------------------------------------------*/
  /* The last two characters are randomly generated to reduce   */
  /* the risk of creating the same identifier as another user          */
  /* running CDM at the same time on the same site.                   */
  /*-----------------------------------------------------------------------------------------------*/
  random.number = random_number ;
#ifdef _WINDOWS_SOURCE
  coid [6] = random.character [1] ;
  coid [7] = random.character [0] ;
#else
  coid [6] = random.character [2] ;
  coid [7] = random.character [3] ;
#endif  
  CATDbBinary compid(8,coid,8);
  
  return compid;
}
