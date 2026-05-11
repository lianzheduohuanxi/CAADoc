#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
GeometricObjectsUUID
#else
LINK_WITH_FOR_IID =
#endif
# 
# COPYRIGHT DASSAULT SYSTEMES  2000
#
BUILT_OBJECT_TYPE=SHARED LIBRARY
#
OS = COMMON

LINK_WITH= \
  $(LINK_WITH_FOR_IID) \
  JS0GROUP \
  CATMathematics \
  CATMathStream \
  CATCGMGeoMath \
  CATAdvancedMathematics \
  CATGeometricObjects \
  CAAAmtForeignFct
	


