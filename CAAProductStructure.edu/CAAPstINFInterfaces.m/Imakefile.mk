# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAAPstINFInterfaces.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATObjectModelerBase         \
          CATObjectSpecsModeler        \
		  CATProductStructure1         \
		  CATVisualization             \
		  JS0GROUP
