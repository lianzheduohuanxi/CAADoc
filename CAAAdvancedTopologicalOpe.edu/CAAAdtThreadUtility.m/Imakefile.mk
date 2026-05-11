# COPYRIGHT DASSAULT SYSTEMES 2000
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 

LINK_WITH = 		JS0GROUP \
                        BasicTopology \
			CATMathematics \
			CATMathStream \
			CATCGMGeoMath \
			CATGeometricObjects \
			CATNewTopologicalObjects \
			CATBasicTopologicalOpe \
			CATTopologicalOperators \
			CATAdvancedTopologicalOpe


# System dependant variables
#
OS = AIX
#
OS = HP-UX
#
OS = IRIX
#
OS = SunOS
#
OS = Windows_NT
