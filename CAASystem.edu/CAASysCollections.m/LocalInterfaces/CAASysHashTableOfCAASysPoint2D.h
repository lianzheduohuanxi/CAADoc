#ifndef CAASysHashTableOfCAASysPoint2D_h
#define CAASysHashTableOfCAASysPoint2D_h

// COPYRIGHT DASSAULT SYSTEMES 2000

// =====================================================================
// Abstract Class: 
//     
//     Defines a Hash Table of CAASysPoint2D
// 
// =====================================================================

// Undefine all previous member function definitions on hashtables.
#include "CATHTAB_Clean.h"

// Define the methods supported by the hashtable
// Since CATHTAB_AllFunct.h is included, the hashtables
// defined thereafter will support all the existing
// hashtable member function.
#include "CATHTAB_AllFunct.h"

// Include the hashtable class declaration macros.
#include "CATHTAB_Declare.h"

// Use the macros to declare a hashtable of CAASysPoint2D class.
#include <CAASysPoint2D.h>
CATHTAB_DECLARE(CAASysPoint2D)


#endif
