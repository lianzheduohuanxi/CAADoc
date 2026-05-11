# COPYRIGHT DASSAULT SYSTEMES 1999
#======================================================================
# Imakefile for module CAAVisManagerImpl.m
#======================================================================
#
# SHARED LIBRARY
#
BUILT_OBJECT_TYPE = SHARED LIBRARY

LINK_WITH= CATVisualization CATViz CAAVisManagerInt\
            CATMathematics \
            JS0GROUP 
