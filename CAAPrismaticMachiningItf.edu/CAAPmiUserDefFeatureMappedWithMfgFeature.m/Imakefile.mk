// COPYRIGHT DASSAULT SYSTEMES 2002
#ifdef LOCAL_DEFINITION_FOR_IID
LINK_WITH_FOR_IID = \
ManufacturingInterfacesUUID
#else
LINK_WITH_FOR_IID =
#endif
##########################################################################
#
#       Manufacturing : Default mapping implementation
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
                CATPrismaticMachiningInterfaces CATManufacturingInterfaces\
                CATUdfInterfaces\
                CATPartInterfaces CATSketcherInterfaces CATCGMGeoMath CATMathStream

# -------------------------------------------------------------------------

OS = AIX

OS = IRIX

OS = HP-UX

OS = SunOS

OS = Windows_NT

