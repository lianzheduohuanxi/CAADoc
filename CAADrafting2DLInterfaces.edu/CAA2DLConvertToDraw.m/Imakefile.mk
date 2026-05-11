// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Imakefile for code module CAA2DLConvertToDraw.m
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Dec. 2007  Creation
//=============================================================================

BUILT_OBJECT_TYPE = SHARED LIBRARY
LINK_WITH = JS0GROUP \
            JS0CORBA \
            CATBatProtocol \
            CATBatchUtils \
            CATObjectModelerBase \
            CATObjectSpecsModeler \
            CATTPSUUID\
            CATMecModInterfaces \
			Drafting2DLItfCPP \
			DraftingItfCPP \
			CATPrt
