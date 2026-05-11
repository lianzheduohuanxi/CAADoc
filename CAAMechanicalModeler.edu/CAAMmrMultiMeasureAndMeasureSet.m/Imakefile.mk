# COPYRIGHT DASSAULT SYSTEMES 2006
#
BUILT_OBJECT_TYPE=SHARED LIBRARY
#
LINK_WITH=\
          JS0GROUP \
          \
          CATMechanicalModeler\
          CATObjectModelerBase\          
          \
          ObjectModeler\
          SpecsModeler \
          \
          CATTopologicalObjects BODYNOPE\
          KnowledgeItf\
          \
          CATVisualization\
          CATGraphicProperties\
          CATMathematics

