# 
# COPYRIGHT DASSAULT SYSTEMES  2001
#
BUILT_OBJECT_TYPE=LOAD MODULE
#
OS = COMMON

# LINK_WITH = JS0GROUP FrFTopologicalOpe CATMathStream CATCGMGeoMath CATGeometricObjects CATTopologicalOperators CATTopologicalObjects CATAdvancedMathematics
	
CurrLINK_WITH = JS0GROUP FrFTopologicalOpe CATMathStream CATCGMGeoMath CATGeometricObjects CATTopologicalOperators CATTopologicalObjects CATAdvancedMathematics
#if defined (CATIAV5R17) || defined (CATIAR201)
LINK_WITH = \
  YN000MAT \
  $(CurrLINK_WITH)
#else
LINK_WITH = $(CurrLINK_WITH)
#endif

