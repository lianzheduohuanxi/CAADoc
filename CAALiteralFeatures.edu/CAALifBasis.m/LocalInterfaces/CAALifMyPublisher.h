// COPYRIGHT DASSAULT SYSTEMES  1994 2000

#ifndef CAALifMyPublisher_H
#define CAALifMyPublisher_H

// LiteralFeatures adapter
#include "CATParmPublisherAdapter.h"

// LiteralFeatures interfaces
#include "CATICkeRelationForwards.h"
#include "CATICkeParm.h"
#include "CATICkeType.h"
#include "CATIVisitor.h"


// ================================================================
// 
// ABSTRACT
// --------
// 
// This class defines the CAAMyPublisher type which implements CATIParmPublisher
// It derives from CATCkeDescendants and redefine the GetDirectChildren and 
// CompAttrKey methods.
// Any object intended to be added parameters and relations and benefit from the f(x) 
// capabilities must implement the CATIParmPublisher interface.
// The LiteralFeatures framework provides you with the CATCkeDescendants adapter you can extend
// to redefine the GetDirectChildren and GetAllChildren methods.
//
// ===========================================================================
//  Usage:
//  ------
//  Type  CAALifPublishMain
//  
//===========================================================================
//  Inheritance:
//  ------------
//         CATParmPublisherAdapter
//
//===========================================================================
//  Main Method:
//  ------------
//
//  CAALifParametersVolatile
//
//===========================================================================
class  CAALifMyPublisher : public CATParmPublisherAdapter
{
	  CATDeclareClass;
	  
public:
	  // Constructors
	  CAALifMyPublisher();
	  
	  // Destructor
	  virtual ~CAALifMyPublisher();
	  
	  /**
	  * Used by KBWare to append user parameters and relations to this object.
	  * In this case, this object is the Applications Root Feature that implements this interface
	  * @param iKBwareObject : 
	  *    Kbware object to append to the root object.
	  */
	  virtual void Append         (const CATISpecObject_var & iKBwareObject )    ;
	  
	  /**
	  * Used by KBWare to remove user parameters and relations to this object.
	  * In this case, this object is the Applications Root Feature that implements this interface
	  * @param iKBwareObject : 
	  *    Kbware object to remove from the root object.
	  */
	  virtual void RemoveChild    (const CATISpecObject_var & iKBwareObject )   ;
	  
	  /**
	  * The GetDirectChildren is overrriden in this class
	  */
	  virtual void GetDirectChildren (CATClassId iIntfName,CATListValCATISpecObject_var &iList) ;
	  
	  /**
	  * Returns the objects implementing the given interface that are local to this feature
	  * or that belong to downstream features (recursive).<br> 
	  * Example of interfaces searched (CATICkeParm, CATICkeRelation, CATIDimCst)
	  * @param iIntfName name of the interface searched
	  * @param iListFound objects found are added to the list
	  */
	  virtual void GetAllChildren (CATClassId iIntfName,CATListValCATISpecObject_var &ListFound)     ;
	  
	  
	  boolean AllowUserAppend ( ) const;
	  
	  
	  /* Returns the container where the relations can be created
	  */
	  virtual CATIContainer_var GetContainer();
	  
      /**
      * This method is re-implemeted in order to allow a visitor to explore the feature
      * structure and eventually to launch its actions.
      * Generally there is one visitor per action that can be done on a data structure.
      * For instance, a visitor can retreive all instances of a CATICkeParm recursively from a feature.
      * (see CAALifMyVisitor.h .cpp).
      * You can also use visitors to play the same role as GetAllChildren and GetDirectChildren.
      */
	  void VisitChildren( CATIVisitor*, const int iRecursively = 0 );
	  
	  
private:
	  CAALifMyPublisher(const CAALifMyPublisher&);
	  
};

#endif
