// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAESysUExitIO.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATLib.h"

//C++ standard library
#include "iostream.h"


//-----------------------------------------------------------------------------
// To create the TIE object
#include "TIE_CATIUExitIO.h"
TIE_CATIUExitIO(CAAESysUExitIO);

// To declare that the class is a data extension of CATUExitIO
//
CATImplementClass(CAAESysUExitIO, DataExtension, CATBaseUnknown, CATUExitIO);

// 
// To declare that CAAESysUExitIO implements CATIUExitIO, insert 
// the following line in the interface dictionary:
//
//    CATUExitIO CATIUExitIO  libCAASysUexitIO
//
//----------------------------------------------------------------------------

CAAESysUExitIO::CAAESysUExitIO()
{
  cout << "CAAESysUExitIO::CAAESysUExitIO" << endl;
}

CAAESysUExitIO::~CAAESysUExitIO()
{
  cout << "CAAESysUExitIO::~CAAESysUExitIO" << endl;
}
//----------------------------------------------------------------------------

HRESULT CAAESysUExitIO::OnOpen (const CATUnicodeString *iFileName,CATAccessRight iMode,
			  HRESULT *oGranted, CATFileSystemError *oError)
	

{
   cout << " CAAESysUExitIO::OnOpen"<< endl;

   // note: OnOpen is called only if iFileName exists 

   HRESULT rc = S_OK ;
   *oGranted = S_FALSE ;

   if ( NULL != iFileName )
   {
      cout << "The file to open is "<< iFileName->ConvertToChar() << endl;
      cout << "The access right of this file are" ;

      switch ( iMode )
      {
         case CATReadRight :
            cout << " Read right "<< endl ;
         break ;
         case CATWriteRight  :
            cout << " Write right "<< endl ;
         break ;
         case CATRWRight  :
            cout << " Read/Write right "<< endl ;
         break ;
         case CATExecuteRight  :
         cout << " Execute right "<< endl ;
         break ;
      }

      if ( CATReadRight == iMode )
      {
         // Everybody can read the file
         *oGranted = S_OK ;
      }else
      {
         if ( chmod(iFileName->ConvertToChar(),00777) )
         {
            // Pb in this system call
            rc = E_FAIL ;
         }else
         {
            *oGranted = S_OK ;
         }
      }
   } 
    
   *oError = 0 ; // Success case
   if ( E_FAIL == rc )
   {
      // if rc is not S_OK, oError must be valuated to CATERRNO
      *oError = CATERRNO ; // Error case
   }

   return rc ;
}

//----------------------------------------------------------------------------

HRESULT CAAESysUExitIO::CreationMask (const CATUnicodeString *iFileName, DWORD *oMode,
				CATFileSystemError *oError)
{
   cout << " CAAESysUExitIO::CreationMask"<< endl;

   // oMode is not valuated

   return E_NOTIMPL ;
}

//----------------------------------------------------------------------------

HRESULT CAAESysUExitIO::OnClose (const CATUnicodeString *iFileName,
			   CATFileSystemError *oError)
{
   cout << " CAAESysUExitIO::OnClose"<< endl;

   // note: OnClose is called only if iFileName exists 

   HRESULT rc = S_OK ;

   if ( NULL != iFileName) 
   {
      cout << "The file to open is "<< iFileName->ConvertToChar() << endl;

      // The right of the files are supposed to 00000
      //
      if ( chmod(iFileName->ConvertToChar(),00000) )
      {
         // Pb in this system call
         rc = E_FAIL ;
      }
   } 
    
   *oError = 0 ; // Success case
   if ( E_FAIL == rc )
   {
      // if rc is not S_OK, oError must be valuated to CATERRNO
      *oError = CATERRNO ; // Error case
   }

   return rc ;
}
//----------------------------------------------------------------------------
