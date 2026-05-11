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
#ifndef  CATRecUExitCrypt_H  
#define  CATRecUExitCrypt_H  

// --- Header that need to be referenced

#include  "CATBaseUnknown.h"  

/**  
  *  Provide implementation for CATRecUExitCrypt.  
  *
  * <b>Role</b>:
  *  Provide implementation for CATRecUExitCrypt to enable to use -spwd option in Reconcilator & PVR utilities.  
  *  <sl>  
  *  <li>It  implements  the  interfaces:</li>  
  *  <li>@see  NavigatorInterfaces.CATIUExitCrypt </li>
  *  </sl>  
  */  
class  CATRecUExitCrypt :  public  CATBaseUnknown  
{  
   CATDeclareClass ;  

   public:  

      //  Standard  constructors  and  destructors  for  an  implementation  class. 
      //  -----------------------------------------------------------------  

    /**  
      *  Default constructor.
      */
      CATRecUExitCrypt() ;

    /**  
      *  Destructor.
      */
      virtual ~CATRecUExitCrypt() ;  

    /**  
      *  Encode function.
      *
      * <b>Role</b>:
      *  Implements encoding function for a given Buffer.
      *  @see  CATIUExitCrypt#Code  
      *
      * @param iBuffer
      *  Input Buffer to be coded 
      *
      * @param iLen
      *  Length of the input buffer 
      *
      * @param oCodedBuffer
      *  Output Buffer. It must be allocated by the method Code
      *
      * @param oCodedLen
      *  Length of the output buffer
      *
      * @return
      *  S_OK 
      *  E_FAIL if the coding is not succesfull
      */
      HRESULT Code( const void * iDecodedBuffer , size_t iDecodedLen , void ** oCodedBuffer , size_t * oCodedLen ) ;  

    /**
      *  Decode function.
      *
      * <b>Role</b>:
      *  Implements decoding function for a given Buffer.
      *  @see  CATIUExitCrypt#Decode  
      *
      * @param iCodedBuffer
      *  Input Buffer to be decoded.
      *
      * @param iCodedLen
      *  Length of the input buffer.
      *
      * @param oDecodedBuffer
      *  Output Buffer. It must be allocated by the method Decode.
      *
      * @param oDecodedLen
      *  Length of the output buffer.
      *
      * @return
      *  S_OK 
      *  E_FAIL if the decoding is not succesfull.
      */
      HRESULT Decode( const void * iCodedBuffer , size_t iCodedLen , void ** oDecodedBuffer , size_t * oDecodedLen ) ;  

   private:  
      //  The  copy  constructor  and  the  equal  operator  must  not  be  implemented  
      //  -------------------------------------------------------------------  
      CATRecUExitCrypt( CATRecUExitCrypt & ) ;

      CATRecUExitCrypt & operator=( CATRecUExitCrypt & ) ;
} ;
#endif  
