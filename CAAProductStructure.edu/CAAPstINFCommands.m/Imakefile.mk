# COPYRIGHT DASSAULT SYSTEMES 2002
#======================================================================
# Imakefile for module CAAPstIntegrateNewFeaturesModel.m
#======================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY 
 
LINK_WITH=CATObjectModelerBase         \
          CATObjectSpecsModeler        \
		  CATProductStructure1         \
		  CATProductStructureInterfaces\
		  CAAPstINFInterfaces          \
		  CATVisualization             \
		  CATApplicationFrame          \
		  JS0FM JS0GROUP DI0PANV2      \
          
          



