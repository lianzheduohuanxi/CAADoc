#ifndef CAADlgModel_H
#define CAADlgModel_H

// COPYRIGHT DASSAULT SYSTEMES 2000

//==============================================================================
//  Abstract of the class:
//  ---------------------
// 
//  This class derives from CATCommand. It shows how to send notifications by
//  using the SendNotification method, and how to answer to a sending object
//  request by redefining the SendCommandSpecificObject method.
//
//==============================================================================

// System Framework
#include "CATCommand.h"  // To derive from CATCommand

class CAADlgElement;

class CAADlgModel: public CATCommand
{
  public:

    CAADlgModel(CATCommand * iParent, char *iName);
    virtual ~CAADlgModel();

    // Add
    // ---
    // Adds an element to the model
    //
    void Add(CAADlgElement *iNewElement);

    // Remove
    // ------
    // Removes an element from the model
    //
    void Remove(CAADlgElement *iElemenToRemove);

    // SendCommandSpecificObject
    // --------------------------
    // Redefined from CATCommand
    // Sends the last element added or removed to the command that caught
    // the Add or Remove notification (the screen or the plot)
    void *SendCommandSpecificObject(const char      *iObjectClassNeeded,
                                    CATNotification *iReceived);

    // Returns the name of the model
    char * GetModelName();

   private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgModel ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgModel(const CAADlgModel &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAADlgModel & operator = (const CAADlgModel &iObjectToCopy);

   private:

    // List of elements contained in the model
    //
    CAADlgElement     * _ElementList[100];
    int                 _PositionToAdd   ;

    // It can be the last element added or removed 
    CAADlgElement     * _pTheLastElementManipulated;

    // The name of the model
    char * _pModelName;
};

#endif
