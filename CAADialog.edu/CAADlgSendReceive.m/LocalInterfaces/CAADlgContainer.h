#ifndef CAADlgContainer_H
#define CAADlgContainer_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//==============================================================================
//  Abstract of the class:
//  ---------------------
// 
//  This class derives from CATCommand. It shows how a CATCommand can catch
//  some notifications and be transparent for others by redefining the
//  AnalyseNotification method.
//
//==============================================================================

// System Framework
#include "CATCommand.h"

// Local Framework
class CAADlgNotifAdd;
class CAADlgNotifRemove;


class CAADlgContainer: public CATCommand 
{
  public:

    CAADlgContainer(char *iName);
    virtual ~CAADlgContainer();

    // AnalyseNotification
    // --------------------
    // Redefined from CATCommand
    // Transparent for Add and Remove notifications, but catches Error
    // notifications. These three types of notifications are sent by the
    // model (CAADlgModel class). 
    CATNotifPropagationMode AnalyseNotification(CATCommand      *iSending,
                                                CATNotification *iReceive);

    // Returns the container name
    char * GetContainerName();

  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgContainer ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgContainer(const CAADlgContainer &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgContainer & operator = (const CAADlgContainer &iObjectToCopy);

  private:

    // The name of the container
    char * _pContainerName ;
};

#endif

