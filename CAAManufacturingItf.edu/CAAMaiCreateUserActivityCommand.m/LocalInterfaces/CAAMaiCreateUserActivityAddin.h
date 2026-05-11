#include "CATBaseUnknown.h"  // Needed to derive from CATBaseUnknown

class CATCmdContainer;       // Needed by CreateToolbars

class CAAMaiCreateUserActivityAddin : public CATBaseUnknown
{
  CATDeclareClass;
  public:
     CAAMaiCreateUserActivityAddin();
     virtual ~CAAMaiCreateUserActivityAddin();

     void CreateCommands();
     CATCmdContainer * CreateToolbars();
};

