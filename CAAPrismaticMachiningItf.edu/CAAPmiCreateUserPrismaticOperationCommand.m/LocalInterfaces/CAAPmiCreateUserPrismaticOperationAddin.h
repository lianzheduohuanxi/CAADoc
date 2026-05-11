//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
// Class CAAPmiCreateUserPrismaticOperationAddin
// Toolbar with commands to create User defined prismatic operation
//
//===================================================================
#ifndef CAAPmiCreateUserPrismaticOperationAddin_H
#define CAAPmiCreateUserPrismaticOperationAddin_H


#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

class CATCmdContainer;       // Needed by CreateToolbars


class CAAPmiCreateUserPrismaticOperationAddin : public CATBaseUnknown
{
   CATDeclareClass;

public:

   CAAPmiCreateUserPrismaticOperationAddin();
   virtual ~CAAPmiCreateUserPrismaticOperationAddin();
   
   void CreateCommands();
   CATCmdContainer * CreateToolbars();

};
#endif
