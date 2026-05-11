#ifndef CAASysPoint2D_H
#define CAASysPoint2D_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract:
//  ---------
//
//	A simple 2D point class 
//    
//=============================================================================


class CAASysPoint2D	
{ 
	public:

       // Constructors.
       CAASysPoint2D();
       CAASysPoint2D(float iX, float iY);

        // Copy constructor used by list of value of this class
        //
        CAASysPoint2D( const CAASysPoint2D & iCopy);

        // Operators == and !=
        // --------------------
        // The class must override the operators == and != in order to
        // be used in list of values.
        //
        int operator==(const CAASysPoint2D & iRef) const;
        int operator!=(const CAASysPoint2D & iRef) const;

        // Coordinate access functions.
        // ----------------------------
        float GetX() const ;
        float GetY() const ;

        // Comparison function.
        // --------------------
        // The class must also provide a comparison function 
        // in order to be used in hashtables.
        // This method is called by the hash table if you try to range 
        // a new point with the same key as an another. For each point
        // in a "bucket", there is a comparison with the new point. 
        // if the new point is equal to an another, the nre point is 
        // not keep in the table.<< The Hash table has only one occurence 
        // of an element >> 
        // So this method must return:
        //   0    -> if the points are the same 
        //   != 0 -> points are not the same  
        // 
        static int Compare ( CAASysPoint2D* iPt1, CAASysPoint2D* iPt2 );

        // Hashing function.
        // -----------------
        // The class must also provide a hashing function 
        // in order to be used in hashtables.
        // This method return the key of the point in the table
        // 
        static unsigned int	Hash ( CAASysPoint2D*	iPt );

    private:
        float _x;
        float _y;
};

#endif
