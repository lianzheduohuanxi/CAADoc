#include "CATBaseUnknown.h"

class CATCmdContainer;

class CAAMfgToolPathEditorM3xAddin : public CATBaseUnknown
{
 
       CATDeclareClass;

  public :
     CAAMfgToolPathEditorM3xAddin();
     virtual ~CAAMfgToolPathEditorM3xAddin();

     void CreateCommands();
     CATCmdContainer * CreateToolbars();
};
 

