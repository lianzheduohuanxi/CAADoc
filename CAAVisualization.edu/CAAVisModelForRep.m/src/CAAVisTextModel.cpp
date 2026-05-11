// COPYRIGHT DASSAULT SYSTEMES  2003

// Local framework
#include "CAAVisTextModel.h"

// The component implements CAAIVisTextModel
#include "TIE_CAAIVisTextModel.h"
TIE_CAAIVisTextModel(CAAVisTextModel);

//-----------------------------------------------------------------------------
// To declare that the class is a component main class which OM derives from
// the CATModelForRep3D component.
//
CATImplementClass(CAAVisTextModel,Implementation ,CATModelForRep3D , CATNull);

// 
// To declare that CAAVisTextModel implements CAAIVisTextModel, insert 
// the following line in the interface dictionary:
//
//    CAAVisTextModel CAAIVisTextModel  libCAAVisModelForRep
//
//-----------------------------------------------------------------------------

CAAVisTextModel::CAAVisTextModel():CATModelForRep3D()  {}

CAAVisTextModel::~CAAVisTextModel() {}

//-----------------------------------------------------------------------------

HRESULT CAAVisTextModel::SetGraphicRepresentation(CATRep *iRep)
{

    SetRep(iRep);

    return S_OK ;
}

//-----------------------------------------------------------------------------


