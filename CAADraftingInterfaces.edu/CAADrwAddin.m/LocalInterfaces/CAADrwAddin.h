#ifndef CAADrwAddin_H
#define CAADrwAddin_H

#include "CATBaseUnknown.h" 

class CATCmdContainer;      

class CAADrwAddin : public CATBaseUnknown
{
  CATDeclareClass;

  public:
     CAADrwAddin();
     virtual ~CAADrwAddin();

     void CreateCommands();
     CATCmdContainer * CreateToolbars();

  private:
  // The copy constructor and the equal operator must not be implemented
  // -------------------------------------------------------------------
	CAADrwAddin (CAADrwAddin &);
	CAADrwAddin& operator=(CAADrwAddin&); 

};
#endif
