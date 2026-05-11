# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAMmrDatumWindowCmd
#======================================================================
# 
# SHARED LIBRARY
# 
# 
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH = AD0XXBAS DI0PANV2 \
            CATVisualization CATViz \
            CATApplicationFrame CATDialogEngine \
            CATMathematics CATMathStream \
            JS0GROUP JS0FM SystemUUID \
            CATMecModInterfaces CATMmiUUID  
           
