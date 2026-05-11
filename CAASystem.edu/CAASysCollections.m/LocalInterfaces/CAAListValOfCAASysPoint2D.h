#ifndef	CAAListValOfCAASysPoint2D_h
#define	CAAListValOfCAASysPoint2D_h

// COPYRIGHT DASSAULT SYSTEMES 2000

// =====================================================================
// Abstract Class: 
//     
//     Defines a list of values of CAASysPoint2D
// 
// =====================================================================

// To undefine all possible methods of the list of values
#include  "CATLISTV_Clean.h" 

// Define the methods supported by the list of values
#define	CATLISTV_Append
#define	CATLISTV_Locate
#define	CATLISTV_RemoveValue

// For the macro CATLISTV_DECLARE
#include  "CATLISTV_Declare.h" 
#include  "CAASysPoint2D.h"

// Declare the type : list of values of class <CAASysPoint2D>
CATLISTV_DECLARE(CAASysPoint2D)

#endif
