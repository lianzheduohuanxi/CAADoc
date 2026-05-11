# COPYRIGHT DASSAULT SYSTEMES 2000
#===================================================================
#
BUILT_OBJECT_TYPE=SHARED LIBRARY

OS = COMMON

LINK_WITH =  JS0CORBA JS0FM \
             CATApplicationFrame CATDialogEngine CATIAApplicationFrame \
			 CATObjectModelerBase CATObjectSpecsModeler  \
             CATVisualization CATViz \	 
			 CATAnalysisInterface CATSAM0Explicit CATSamVisuUUID CAAAniAutomationItf MSHUITools MSHModel DI0PANV2\



