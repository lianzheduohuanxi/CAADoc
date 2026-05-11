// COPYRIGHT DASSAULT SYSTEMES 1999
 
#include "CAASysPoint2D.h"

//-------------------------------------------------------------------------
CAASysPoint2D::CAASysPoint2D() {
   _x = 0.0f;
   _y = 0.0f;
}

//-------------------------------------------------------------------------

CAASysPoint2D::CAASysPoint2D(float iX, float iY) {
   _x = iX;
   _y = iY;
}

//-------------------------------------------------------------------------
 
CAASysPoint2D::CAASysPoint2D(const CAASysPoint2D &iPointToCopied) 
{
   _x = iPointToCopied.GetX();
   _y = iPointToCopied.GetY();
}
 
//-------------------------------------------------------------------------

int CAASysPoint2D::operator ==(const CAASysPoint2D & iRef) const 
{
  return ((iRef.GetX() == _x) && (iRef.GetY() == _y));
}

//-------------------------------------------------------------------------

int CAASysPoint2D::operator!=(const CAASysPoint2D &iRef) const
{
  return ((iRef.GetX() != _x) || (iRef.GetY() != _y));
}

//-------------------------------------------------------------------------

int CAASysPoint2D::Compare ( CAASysPoint2D* iPt1, CAASysPoint2D* iPt2) 
{
   if ( (0 != iPt1 ) && ( 0 != iPt2 ) ) 
   {
      if ((iPt1->_x == iPt2->_x) && (iPt1->_y == iPt2->_y)) 
      {
           // 2 points are the same
      	return 0;
      }
      // 2 points are not the same, try to be more precise 
      // But for the hash table code is not nesserary to be more precise.
      if (iPt1->_x < iPt2->_x)
      {
        
      	return 1;
      }

      return -1;

   }else
   {
      // Invalid data
      return -2 ;
   } 
}

//-------------------------------------------------------------------------

unsigned int   CAASysPoint2D::Hash( CAASysPoint2D* iPt) 
{
   // The key of the table is the exclusif or 
   if ( 0 != iPt )
   {
      return ((unsigned int)iPt->_x) ^ ((unsigned int)iPt->_y);
   }else
   {
      // Invalid data
      return -1 ;
   }
}

//-------------------------------------------------------------------------

float CAASysPoint2D::GetX() const
{
   return _x ;
}

//-------------------------------------------------------------------------

float CAASysPoint2D::GetY() const
{
   return _y ;
}
//-------------------------------------------------------------------------
