// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAOmbNavigModifyPoint.h"

// ObjectModelerBase Framework   
#include "CATNavigInstance.h"          // Argument type de UpdateElem:  not used
#include "CATINavigElement.h"          // To retrieve the element associated with this 
                                       // extension element_node

// CAASystem.edu Framework
#include "CAAISysPoint.h"              // To retrieve the coordinates of the element

// System Framework
#include "CATUnicodeString.h" 

// C++ Standard Library
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATINavigModify.h"
TIE_CATINavigModify(CAAOmbNavigModifyPoint);

// Declares that the class is a data extension of CAASysPoint_node
//
CATImplementClass(CAAOmbNavigModifyPoint,
				  DataExtension,
				  CATBaseUnknown,
				  CAASysPoint_node);
// 
// To declare that CAAOmbNavigModifyPoint implements the CATINavigModify 
// interface, insert these following lines in the interface dictionary:
//
//    CAASysPoint_node     CATINavigModify  libCAAOmbGeoNavigate
//
//
//---------------------------------------------------------------------------------------------

CAAOmbNavigModifyPoint::CAAOmbNavigModifyPoint()
{
  cout << "CAAOmbNavigModifyPoint::CAAOmbNavigModifyPoint" << endl;
}

//---------------------------------------------------------------------------------------------

CAAOmbNavigModifyPoint::~CAAOmbNavigModifyPoint()
{
  cout <<"CAAOmbNavigModifyPoint::~CAAOmbNavigModifyPoint" << endl;
}


//---------------------------------------------------------------------------------------------

HRESULT  CAAOmbNavigModifyPoint::ModifyShortHelp(CATUnicodeString& ioText)
{
    cout <<" CAAOmbNavigModifyPoint::ModifyShortHelp  " << ioText.CastToCharPtr() << endl;

    CATBaseUnknown_var Ref ;

    CATINavigElement *pINavigElement = NULL ;
    HRESULT rc = QueryInterface(IID_CATINavigElement, (void **) & pINavigElement);
    if ( SUCCEEDED(rc) )
    {
       // Do not release this pointer
       CATNavigInstance * pInst = pINavigElement->GetAssociatedInstance();
       if ( NULL != pInst)
       {
          // It is the component associated with this component's implementation
          // This current implementation is done for the CAASysPoint_node component
          // ref is a pointer on the CAASysPoint component
          //
          Ref = pInst->GetReference();

       }else 
          rc = E_FAIL ;

       pINavigElement->Release();
       pINavigElement = NULL ;
    }

    if (NULL_var != Ref)
    {
       CAAISysPoint *pISysPoint = NULL ;
       rc = Ref->QueryInterface(IID_CAAISysPoint, (void **) & pISysPoint);
       if ( SUCCEEDED(rc) )
       {
          float x,y,z ;
          pISysPoint->GetCoord(x,y,z);
       
          char PointPosistionBuffer[200];
          sprintf(PointPosistionBuffer,"X=%f Y=%f Z=%f",x,y,z);

          CATUnicodeString TextBuff (PointPosistionBuffer);
          ioText = TextBuff ;

          pISysPoint->Release();
          pISysPoint = NULL ;
       }
    }

    return rc ;
}

//---------------------------------------------------------------------------------------------
