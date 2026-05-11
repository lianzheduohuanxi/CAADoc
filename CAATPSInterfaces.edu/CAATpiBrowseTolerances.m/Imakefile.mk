// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// Imakefile for code module CAATpiBrowseTolerances.m
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Jan. 2000  Creation
//=============================================================================

BUILT_OBJECT_TYPE = LOAD MODULE

LINK_WITH = JS0GROUP                      \
            CATMathematics                \
            CATObjectModelerBase          \
            CATApplicationFrame           \
            CATProductStructure1          \
            CATProductStructureInterfaces \
            CATTTRSItf                    \
            CATTPSItf                     \
            CATTPSUUID                    \
            CATMathStream                 \
            $(LINK_WITH_DEBUG)

#if os SunOS
LINK_WITH_DEBUG = CATObjectSpecsModeler

#else
LINK_WITH_DEBUG = 
#endif
