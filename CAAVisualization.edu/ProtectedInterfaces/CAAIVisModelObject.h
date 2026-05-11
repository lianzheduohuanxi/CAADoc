#ifndef CAAIVisModelObject_H
#define CAAIVisModelObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface to manage objects handled by the CAAVisManager sample.
//
//==========================================================================
//
// Usage 
// -----
// This interface is used to give ownership relations to objects that are handled
// in this sample. This interface defines a parent and child relationship. Thus using
// this interface allows you to define a ownership tree for any modeling structure.
//
// For example, objects that implement this interface are able to be made up of others objects
// or to be hold by other objects.
//     
// Every object that wants to be part of the ownership tree of the user model has 
// to implements the CAAIVisModelObject interface.
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

///Visualization FrameWork
#include "list.h"

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class


// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVisModelObject;

class ExportedByCAAVisManagerInt CAAIVisModelObject : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  virtual list<CATBaseUnknown> *GetChildren()=0;
  virtual list<CATBaseUnknown> *GetParents()=0;

  virtual HRESULT GetType(char ** oType)=0;
  virtual HRESULT SetType(const char * iType)=0;

  virtual HRESULT AddChild(CATBaseUnknown *iObject)=0;
  virtual HRESULT RemChild(CATBaseUnknown *iObject)=0;
  virtual HRESULT AddParent(CATBaseUnknown *iObject)=0;
  virtual HRESULT RemParent(CATBaseUnknown *iObject)=0;

};

#endif 
