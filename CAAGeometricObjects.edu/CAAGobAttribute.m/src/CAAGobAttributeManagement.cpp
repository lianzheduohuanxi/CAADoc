/**
* @quickReview CRE 03:10:17
*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// 
// Code implementing an attribute of CAAGobAttributeManagement type.
//
// To be done when implementing an attribute
//
// 1 - Declare the CATCGMImplAttribute macro in your implementation file
//     argument 1 - the class describing your attribute type (CAAGobAttributeManagement)
//     argument 2 - the class you derive from (CATCGMAttribute or CATCGMStreamAttribute
//                  for example - it can also be another already implemented attribute)
//     argument 3 - the application name (it must be declared in the dictionary)
//     argument 4 - the version number (1)
//
// 2 - Define the methods whereby you want to manipulate your attribute
//     (SetValue and GetValue for example)
//
// 3 - Declare the application name in the dictionary (CAAGeometricObjects.edu.dico)
//
//=============================================================================
#include "CAAGobAttributeManagement.h"    // the header which describes your attribute                      
#include "iostream.h"
#include "CATCGMStream.h"                 // to stream and unstream the persistent attribute

// Macro to declare that the code below implements a CATCGMStreamAttribute
// 
CATCGMImplAttribute(CAAGobAttributeManagement, CATCGMStreamAttribute, CAAGobAT, 1);

/**
* Stream the attribute.
*/
void CAAGobAttributeManagement::Stream(CATCGMStream & iStr) const 
{
	cout << "Streaming the attribute..." << endl;
	iStr.WriteLong(streamedvalue);
}

/**
* Unstream the attribute.
*/
void CAAGobAttributeManagement::UnStream(CATCGMStream & iStr) 
{
    cout << "Unstreaming the attribute..." << endl;
	iStr.ReadLong(streamedvalue) ;  
}

/**
* Set the attribute value.
*/
void CAAGobAttributeManagement::SetValue(CATLONG32 val)
{
	streamedvalue=val;
}

/**
* Get the attribute value.
*/
void CAAGobAttributeManagement::GetValue (CATLONG32 & oval)
{
	oval = streamedvalue;
	cout << "Attribute value " << oval << endl;
}
