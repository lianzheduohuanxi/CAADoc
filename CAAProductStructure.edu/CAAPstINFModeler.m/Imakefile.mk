# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAAPstINFModeler.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATObjectModelerBase         \
          CATObjectSpecsModeler        \
		  CATProductStructure1         \
		  CAAPstINFInterfaces          \
		  CATVisualization             \
		  CATMathematics               \
		  CATApplicationFrame          \
		  JS0FM JS0GROUP DI0PANV2  ToolsVisu 
          



