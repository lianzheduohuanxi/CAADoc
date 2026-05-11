// COPYRIGHT DASSAULT SYSTEMES 2004
#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
ManufacturingInterfacesUUID
#else
LINK_WITH_FOR_IID =
#endif
##########################################################################
#
#       Manufacturing : Generation of information in the machining process instantiation step
#
##########################################################################
#
# SHARED LIBRARY
#
# -------------------------------------------------------------------------

BUILT_OBJECT_TYPE=SHARED LIBRARY

LINK_WITH=$(LINK_WITH_FOR_IID)  	AD0XXBAS \
                AC0SPBAS \
                AC0XXLNK \
                SpecsModeler\
                CK0FEAT KnowledgeItf JS0CORBA \
                YP00IMPL YN000MAT\
                CATManufacturingInterfaces\
                CATPartInterfaces CATSketcherInterfaces CATCGMGeoMath CATMathStream

# -------------------------------------------------------------------------

OS = AIX

OS = IRIX

OS = HP-UX

OS = SunOS

OS = Windows_NT

