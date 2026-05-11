// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// Imakefile for big module CAATPSInterfaces.m
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

BUILT_OBJECT_TYPE = SHARED LIBRARY

INCLUDED_MODULES = CAATpiAddin              \
                   CAATpiCreateText                   \
                   CAATpiRetrieveAnnotation         \
                   CAATpiAccessGeometry            \
                   CAATpiDumpTextContent           \
                   CAATpiAnnotationSetGlobalCopy  \
                   CAATpiAnnotationSetGlobalCopyTransfo  \

LINK_WITH = JS0GROUP                      \
            JS0FM                         \
            CATMathematics                \
            CATVisualization              \
            CATViz                        \
            CATApplicationFrame           \
            CATInteractiveInterfaces      \
            DI0PANV2                      \
            CATDialogEngine               \
            CATGeometricObjects           \
            CATNewTopologicalObjects      \
            CATObjectModelerBase          \
            CATProductStructure1          \
            CATTTRSItf                    \
            CATTTRSUUID                   \
            CATMecModInterfaces           \
            CATDraftingInterfaces         \
            CATTPSItf                     \
            CATTPSUUID                    \
            CATMathStream                 \
            CATCGMGeoMath                 \
