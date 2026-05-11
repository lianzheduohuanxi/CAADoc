# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAACafUseToolsOptions.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH= DI0PANV2 \
            CATVisualization CATViz\
            CATApplicationFrame \
            CATMathematics \
            JS0GROUP JS0FM \
            CAASysGeoModelInf\
            CAACafCtrlToolsOptions
