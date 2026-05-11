# COPYRIGHT DASSAULT SYSTEMES 2001
#======================================================================
# Imakefile for module CAAMaiDumpToolPath.m 
#======================================================================
#
# SHARED LIBRARY 
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 

LINK_WITH = JS0FM JS0GROUP AD0XXBAS \
	        DI0STATE AC0SPBAS \
	        DI0PANV2 CATApplicationFrame\
		    CATManufacturingInterfaces 

# -------------------------------------------------------------------------

OS = AIX

OS = IRIX

OS = HP-UX

OS = SunOS

OS = Windows_NT

