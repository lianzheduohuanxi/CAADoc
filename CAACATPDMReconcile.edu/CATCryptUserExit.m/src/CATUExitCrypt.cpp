//  COPYRIGHT  DASSAULT  SYSTEMES  2009-2010
// *****************************************************************
//
//   Description :
//   ------------
//
//   Provide a sample implementation to interface CATIUExitCrypt.
//
// *****************************************************************
//
//   Remarks :
//   ---------
//
//
// ****************************************************************
//
//   Story :
//   -------
//
//    Revision 1.0  September 2009   2004  Purpose: CAA sample.
//
// ****************************************************************

#include  "CATUExitCrypt.h"   

// --- List of referenced classes:
// --- * System header that need to be referenced.

#include <stdlib.h>  

// --- * Header that need to be referenced.

#include "CATError.h"  

CATImplementClass( CATRecUExitCrypt , CodeExtension , CATBaseUnknown , CATUExitCrypt ) ;  

//  Tie  the  implementation  to  its  interface  
//  ---------------------------------------  
#include  "TIE_CATIUExitCrypt.h"  
TIE_CATIUExitCrypt(CATRecUExitCrypt);  

//-----------------------------------------------------------------------------  
// Standard constructor
//-----------------------------------------------------------------------------  
CATRecUExitCrypt::CATRecUExitCrypt() : CATBaseUnknown()  
{  
}  

//-----------------------------------------------------------------------------  
// Standard destructor
//-----------------------------------------------------------------------------  
CATRecUExitCrypt::~CATRecUExitCrypt()  
{  
}  

//-----------------------------------------------------------------------------  
// Input password can be encrypted using this function.
//-----------------------------------------------------------------------------  
HRESULT  CATRecUExitCrypt::Code(const  void  *  iDecodedBuffer,  size_t  iDecodedLen,  void  **  oCodedBuffer,  size_t  *  oCodedLen)  
{  
   // --- Encoding & Decoding function are identical in this example.

   HRESULT HR = Decode( iDecodedBuffer , iDecodedLen , oCodedBuffer , oCodedLen ) ;  

   return HR ;  
}  

//-----------------------------------------------------------------------------  
// This function decodes the password in specific pattern.
// e.g  If input sting buffer is ABCDEF it will be changed to DECABF
// How this sample decode machnaisum works:     
// 1. ABCDEF  =  ABC | DEF  //---Half part  (in case ODD no  ABCDEFG == ABC | DEFG )
// 2. _ _ C | _ _ F         //--- Keep last chanractor of each half part (in case ODD no  _ _ _ | _ _ _ G )
// 3. D E C | A B F         //--- Exhange remaining part of each side with each other (in case ODD no  D E F | A B C G )
// 4. DECABF                //--- Final passowrd (in case ODD no  DEFABCG )
//-----------------------------------------------------------------------------  
HRESULT  CATRecUExitCrypt::Decode( const void * iCodedBuffer , size_t iCodedLen , void ** oDecodedBuffer , size_t * oDecodedLen )  
{  
   HRESULT HR = CATReturnFailure ;  

   *oDecodedLen = iCodedLen ;  
   char * pDecoded = strdup( (char*) iCodedBuffer ) ;
   if( pDecoded )
   {
      //--- get mid point of i/p string

      int  iMid    = (iCodedLen-1)/2    ;
      int  iStart1 = 0                  ;
      int  iStart2 = (iCodedLen-1)-iMid ; 
   
      strncpy( pDecoded+iStart1 , (char*) iCodedBuffer+iStart2 ,  iMid ) ;
      strncpy( pDecoded+iStart2 , (char*) iCodedBuffer+iStart1 ,  iMid ) ;

      *oDecodedBuffer = (void*) pDecoded ;
      HR              = CATReturnSuccess ;
   }
   else
   {
      *oDecodedBuffer = (void*) NULL ;
   }

   return HR ;
}  
