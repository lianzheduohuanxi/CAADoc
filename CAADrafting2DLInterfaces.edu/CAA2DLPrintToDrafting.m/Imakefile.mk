// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Imakefile for code module CAA2DLPrintToDrafting.m
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH = JS0GROUP                      \
            JS0FM                         \
            CATApplicationFrame           \
            DI0PANV2                      \
            CATDialogEngine               \
            Drafting2DLItfCPP             \
            CATBatCliMonitor              \
            CATBatchUtils                 \
            CATObjectModelerBase
