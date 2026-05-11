// COPYRIGHT DASSAULT SYSTEMES 2003

#ifndef CAAVisTextModel_h
#define CAAVisTextModel_h

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//  This class is a main component which C++ and OM derives of the
//  CATModelForRep3D component. The CAAVisTextModel component 
//  implements:
//    - CATICreateInstance with the CAAEVisCreateInstanceForTextModel class
//    - CAAIVisTextModel   with the CAAVisTextModel class
//  This component deriving from CATModelForRep3D already implements 
//  CATI3DGeoVisu.
//
//===========================================================================

// Visualization Framework
#include "CATModelForRep3D.h"  // to derive from

// VisualizationBase Framework
class  CATRep ;

class CAAVisTextModel : public CATModelForRep3D
      
{
         // Used in conjunction with CATImplementClass in the .cpp file
         CATDeclareClass;

 public:
         CAAVisTextModel() ;
         virtual ~CAAVisTextModel();

         // CAAIVisTextModel interface
         virtual HRESULT SetGraphicRepresentation(CATRep *iRep) ;

 private:
 
         // Copy constructor, not implemented
         // Set as private to prevent from compiler automatic creation as public.
         CAAVisTextModel(const CAAVisTextModel &iObjectToCopy);
 
         // Assignment operator, not implemented
         // Set as private to prevent from compiler automatic creation as public.
         CAAVisTextModel & operator = (const CAAVisTextModel &iObjectToCopy);
      
};
#endif


