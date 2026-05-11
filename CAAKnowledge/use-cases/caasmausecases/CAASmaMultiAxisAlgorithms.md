---
title: "Untitled"
category: "use-case"
module: "CAASmaUseCases"
tags: ["CAASmaResultContourDriven", "CAASurfaceMachiningAlgoItf", "CATIDescendants_var", "CAADocStyleSheets", "CATIGSMPoint_var", "CATInstantiateComponent", "CATIPrtContainer_var", "CATIPartRequest", "CATIGSMFactory", "CAASmaResultSweeping", "CATIVisProperties_var", "CAAMultiAxisAlgorithms", "CATIMfgMachiningContainer", "CAADocUseCases", "CATISpecObject_var", "CAASmaMultiAxisAlgorithms", "CATIGeometricalElement", "CATIGeometricalElement_var", "CATIContainer_var", "CATIMfgMultiAxisAlgorithm"]
source_file: "Doc/online/CAASmaUseCases/CAASmaMultiAxisAlgorithms.htm"
converted: "2026-05-11T11:27:02.770050"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to help you run multi-axis machining algorithms. Its 
main intent is to explain how to set parameters, compute and read results of machining 
algorithms, which are:

	
- multi-axis sweeping: tool path is executed in vertical parallel planes 
	and is normal to the part surface
	
- multi-axis contour driven: tool path sweeps between two guide contours 
	or out an area by following contours parallel to a reference contour and is 
	normal to the part surface

[Top]

### The CAASmaMultiAxisAlgorithms Use Case

CAASmaMultiAxisAlgorithms is a use case of the CAASurfaceMachiningAlgoItf.edu 
framework that illustrates the SurfaceMachiningAlgoInterfaces framework capabilities.

[Top]

#### What Does CAASmaMultiAxisAlgorithms Do

CAASmaMultiAxisAlgorithms creates geometrical points, that follow tool paths 
computed by multi-axis sweeping and multi-axis contour driven algorithms.

[Top]

#### How to Launch CAASmaMultiAxisAlgorithms

To launch CAASmaMultiAxisAlgorithms, you will need to set up the build time environment, 
then compile CAASmaMultiAxisAlgorithms along with its prerequisites, set up the 
run time environment, and then execute the use case [1].

To launch the use case, execute the following command:

mkrun -c "CAASmaMultiAxisAlgorithms Filename"

where Filename is the path of a Part document. You can use the `CAAMultiAxisAlgorithms``.CATPart
`located:

[Top]

#### Where to Find the CAASmaMultiAxisAlgorithms Code

The use case code is located in the CAASmaMultiAxisAlgorithms.m module of the 
CAASurfaceMachiningAlgoItf.edu framework:

where `InstallRootDirectory` is the directory where the CAA CD-ROM 
is installed.

[Top]

### Step-by-Step

There are five logical steps in CAASmaMultiAxisAlgorithms:

	
- Opening a Part document and retrieving geometries
	
	
- Creating a Process document and initializing manufacturing 
	environment 
	
- Running the multi-axis sweeping algorithm 
	
- Running the multi-axis contour driven algorithm
	
	
- Creating sets of points from tool paths 

We will now comment each of those sections by looking at the code.

[Top]

#### Opening a Part document and retrieving geometries

First, we need to get geometries used by machining algorithms.

The `CATDocumentServices::OpenDocument` static method opens the part 
document from the location given as first argument of the main program. From the 
root container of the part, we get the *CATIPartRequest* interface and use 
it to access to the first geometrical set of the part.

We scan its children features thanks to `GetDirectChildren`, and get 
the topological result with `GetBodyResult`.

From features called PARTS1 and PARTS2, we get the faces and fill the according 
lists `ListOfParts1` and `ListOfParts2`.

From features called GUIDE1 and GUIDE2, we get the curves and fill the according 
lists `ListOfGuide1` and `ListOfGuide2`.

[Top] 

#### Creating a Process document and initializing manufacturing 
environment 

To store algorithms results, we need to get a machining tool path container.

The `CATDocumentServices::OpenDocument` static method creates a process 
document. From the root container of the process, we initialize the machining containers 
with `InitContainer` and we get the tool path container thanks to the
*CATIMfgManufacturingFactories* interface.

[Top]

#### Running the multi-axis sweeping algorithm

First we create an instance of the multi-axis sweeping algorithm with the
`CATInstantiateComponent` global function, the instance name is "`CATMfgAlgoMultiAxisSweeping`", 
we can also use `MultiAxisSweepingInstanceName` constant. Then we set parameters trough 
the *CATIMfgMultiAxisAlgorithm* interface. 

`SetValue` method is used to set the following numerical parameters:

	
- `MfgAlgMachiningTolerance`: Machining tolerance, it is the maximum 
	allowed distance between the theoretical and computed tool path
	
- `MfgAlgMaxDiscretizationStep`: Maximum discretization step, it 
	ensures linearity between points that are far apart
	
- `MfgAlgMaxDiscretizationAngle`: Maximum discretization angle, 
	it specifies the maximum angular change of tool axis between tool positions
	
- `MfgAlgMaxDistance`: Distance on part, it defines the maximum 
	distance between two consecutive tool paths
	
- `MfgAlgMachiningMode`: Tool path style, the cutting mode is one 
	way or zigzag
	
- `MfgAlgStepoverSide`: Stepover side, it determines the side of 
	the machining direction

`SetDirection` method sets a direction:

	
- `MfgAlgViewDirection`: View direction
	
- `MfgAlgStartDirection`: Start direction

`SetSurfacicGeometry` method sets the geometry of the parts. The call 
of this method is mandatory.

Macros motions are defined by one or several elementary motions with the following 
methods:

	
- `AddMacroAxialMotion`: along the tool axis
	
- `AddMacroTangentMotion`: tangent at its end to the tool path
	
	
- `AddMacroRampingMotion`: following a slope 
	
- `AddMacroCircularMotion`: in a arc
	
- `AddMacroToAPlaneMotion`: up to a plane 
	
- `AddMacroAlongALineMotion`: along a vector 
	
- `AddMacroSyntax`: insert a user syntax 

`SetTool` method sets a manufacturing tool. If we don't call it, then 
a default ball end tool will be used during computation.

At last, `ComputeToolPath` creates and returns a tool path. It is 
created in the container pointed by `spTPContainer`.

[Top]

#### Running the multi-axis contour driven algorithm

First we create an instance of the multi-axis contour driven algorithm with the
`CATInstantiateComponent` global function, the instance name is "`CATMfgAlgoMultiAxisContourDriven`", 
we can also use `MultiAxisContourDrivenInstanceName` constant. Then we set parameters trough 
the *CATIMfgMultiAxisAlgorithm* interface. 

`SetValue` method sets numerical parameters. All parameters of multi-axis 
sweeping are available for multi-axis contour driven. Additional parameters are:

	
- `MfgAlgOffsetOnGuide1`: Offset on guide 1
	
- `MfgAlgOffsetOnGuide2`: Offset on guide 2
	
- `MfgAlgPositionOnGuide1`: Position with respect to the guide 
	1
	
- `MfgAlgPositionOnGuide2`: Position with respect to the guide 
	2
	
- `MfgAlgContouringMode`: Guiding strategy, it is between contours 
	or parallel contour
	
- `MfgAlgFromToContour`: Direction in parallel contour mode, it 
	starts from the guide or it is done up to the guide

`SetSurfacicGeometry` method sets the geometry of the parts. The call 
of this method is mandatory.

`SetWireFrameGeometry` method sets one of the following geometry:

	
- `MfgAlgGuide1`: First guide, it is a mandatory geometry
	
- `MfgAlgGuide2`: Second guide, it is a mandatory geometry in between 
	contours mode
	
- `MfgAlgStop1`: First stop , it delimits the ends of paths
	
- `MfgAlgStop2`: Second stop, it delimits the ends of paths
	
- `MfgAlgLimitLine`: Limiting contour, it defines a limit to the 
	part surface and is also available for multi-axis sweeping algorithm

Direction, tool and macro motions are defined like in the multi-axis sweeping 
algorithm.

At last, `ComputeToolPath` creates and returns a tool path. It is 
created in the container pointed by `spTPContainer`.

[Top]

#### Creating sets of points from tool paths

Finally we scan information of tool paths and create points in the part document.

First we create a new geometrical set in the part container with `CreateGeometricalSet` 
method. Then we get a pointer on *CATIMfgTPMultipleMotion* and we scan the 
tool path. For each sub-trajects, we get the type with `GetSubTrajectType` 
and the position of tool path points with `GetTipPoint`.

Points are created in the new geometrical set thanks to the `CreatePoint` 
method of *CATIGSMFactory* interface. 

With the help of "`START`" and "`END`" user syntax defined in macros motions, we know which points 
are on the part surface and we colored them in green thanks to `SetPropertiesAtt` 
method of *CATIVisProperties* interface.

[Top]

---

### In Short

	
- Inputs of machining algorithms are several geometries and a tool path 
	container
	
- Numerical values, directions, geometry, tool and macros can be defined 
	with *CATIMfgMultiAxisAlgorithm *interface
	
- Output is a tool path, containing information that can be used outside 
	machining context

[Top]

---

### References

---

### History

---

*Copyright  2006, Dassault Systmes. All rights reserved.*

 



```vbscript
CATDocument *pPartDoc = NULL;
   rc = CATDocumentServices::OpenDocument(InputPathName, pPartDoc);
   ...
   CATIPartRequest_var spPartRequest(spPart); 
   if (NULL_var != spPartRequest)
   { 
      CATListValCATBaseUnknown_var ListOfSurfacicSets;
      spPartRequest-&gt;GetSurfBodies(CATUnicodeString (&quot;&quot;), ListOfSurfacicSets);
      ...
```

```vbscript
&nbsp;&nbsp;&nbsp;&nbsp;  CATIDescendants_var spDescOnSurfacicSet = ListOfSurfacicSets[1];
&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spDescOnSurfacicSet)
&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATListValCATISpecObject_var ListOfGeometricalElts;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spDescOnSurfacicSet-&gt;GetDirectChildren(CATIGeometricalElement::ClassName(), ListOfGeometricalElts);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  ...
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  for (int ig=1;ig&lt;=NbGeometricalElts;ig++)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATIGeometricalElement_var spGeomElement = ListOfGeometricalElts[ig];
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spGeomElement)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATBody_var spBody = spGeomElement-&gt;GetBodyResult();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  ...
```

```vbscript
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spBody-&gt;GetAllCells(ListOfCells,2);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  for (int i=1;i&lt;=NbCells;i++)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATFace_var spFace = ListOfCells[i];
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spFace)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (0 != IsParts1) ListOfParts1.Append(spFace);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  else ListOfParts2.Append(spFace);
			...
```

```vbscript
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spBody-&gt;GetAllCells(ListOfCells,1);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  for (int i=1;i&lt;=NbCells;i++)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATEdge_var spEdge = ListOfCells[i];
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spEdge)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATEdgeCurve * pEdgeCurve = spEdge-&gt;GetCurve();
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATCurve_var spCurve = pEdgeCurve;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spCurve)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (0 != IsGuide1) ListOfGuide1.Append(spCurve);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  else ListOfGuide2.Append(spCurve);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  ...
```

```vbscript
&nbsp;  CATDocument *pProcessDoc = NULL;
&nbsp;  rc = CATDocumentServices::New(&quot;Process&quot;, pProcessDoc );
&nbsp;  ...
&nbsp;  CATIMfgMachiningContainer * piMfgEnvt = NULL;
&nbsp;  piProcessContainer-&gt;QueryInterface(CATIMfgMachiningContainer::ClassId(), (void**)&amp;piMfgEnvt);
&nbsp;  if (piMfgEnvt)
&nbsp;  {
&nbsp;&nbsp;&nbsp;  piMfgEnvt-&gt;InitContainer(FALSE,0);
&nbsp;&nbsp;&nbsp;  ...
&nbsp;&nbsp; }
&nbsp;  CATIContainer_var spTPContainer;
&nbsp;  CATIMfgManufacturingFactories *piFact =NULL;
&nbsp;  CATString ClassName(&quot;CATMfgManufacturingFactories&quot;);
&nbsp;  ::CATInstantiateComponent (ClassName, CATIMfgManufacturingFactories::ClassId(), (void**)&amp; piFact);
&nbsp;  if (piFact)
&nbsp;  {
&nbsp;&nbsp;&nbsp;  piFact-&gt;GetManufacturingToolPathFactory(spTPContainer);
&nbsp;&nbsp;&nbsp;  ...
```

```vbscript
&nbsp;  CATIMfgMultiAxisAlgorithm *piMMSweepingAlgo =NULL;
&nbsp;  ::CATInstantiateComponent (&quot;CATMfgAlgoMultiAxisSweeping&quot;, CATIMfgMultiAxisAlgorithm::ClassId(), (void**)&amp; piMMSweepingAlgo);
&nbsp;  ...
&nbsp;  rc = piMMSweepingAlgo-&gt;SetValue(MfgAlgMachiningTolerance,0.1); // Machining tolerance
&nbsp;  rc = piMMSweepingAlgo-&gt;SetValue(MfgAlgMaxDiscretizationStep,100.); // Maximum discretization step
&nbsp;  rc = piMMSweepingAlgo-&gt;SetValue(MfgAlgMaxDistance,10.); // Distance on part

&nbsp;  rc = piMMSweepingAlgo-&gt;SetDirection(MfgAlgViewDirection,XVector); // View dir
&nbsp;  rc = piMMSweepingAlgo-&gt;SetDirection(MfgAlgStartDirection,YVector); // Start dir

&nbsp;  rc = piMMSweepingAlgo-&gt;SetSurfacicGeometry(MfgAlgParts,ListOfParts1); // Parts

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(1,&quot;START&quot;); // Approach macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroTangentMotion(1,10.,90.,0.);
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroToAPlaneMotion(1,MacroPlane);

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(2,&quot;END&quot;); // Retract macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroToAPlaneMotion(2,MacroPlane);

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(3,&quot;START&quot;); // Linking Approach macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroAxialMotion(3);

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(4,&quot;END&quot;); // Linking Retract macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroAxialMotion(4);

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(5,&quot;START&quot;); // Return in a level Approach macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroCircularMotion(5,90.,90.,10.);

&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroSyntax(6,&quot;END&quot;); // Return in a level Retract macro
&nbsp;  rc = piMMSweepingAlgo-&gt;AddMacroCircularMotion(6,90.,90.,10.);
&nbsp;  ... 
&nbsp;  CATBaseUnknown_var spSweepingTP;
&nbsp;  rc = piMMSweepingAlgo-&gt;ComputeToolPath(spTPContainer,spSweepingTP);
```

```vbscript
CATIMfgMultiAxisAlgorithm *piMMContourDriven =NULL;
&nbsp;  ::CATInstantiateComponent (&quot;CATMfgAlgoMultiAxisContourDriven&quot;, CATIMfgMultiAxisAlgorithm::ClassId(), (void**)&amp; piMMContourDriven);
&nbsp;  ...
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgMachiningTolerance,0.1); // Machining tolerance
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgMaxDistance,10.); // Distance on part
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgOffsetOnGuide1,-1.); // Offset on guide 1
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgOffsetOnGuide2,-1.); // Offset on guide 2
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgContouringMode,1); // Between Contour guiding strategy
&nbsp;  rc = piMMContourDriven-&gt;SetValue(MfgAlgMachiningMode,1); // One-way tool path style

&nbsp;  CATMathVector NormalView(2.,0.,1.);
&nbsp;  rc = piMMContourDriven-&gt;SetDirection(MfgAlgViewDirection,NormalView); // View dir
&nbsp;  rc = piMMContourDriven-&gt;SetDirection(MfgAlgStartDirection,YVector); // Start dir

&nbsp;  rc = piMMContourDriven-&gt;SetSurfacicGeometry(MfgAlgParts,ListOfParts2); // Parts
&nbsp;  rc = piMMContourDriven-&gt;SetWireFrameGeometry(MfgAlgGuide1,ListOfGuide1); // First guide
&nbsp;  rc = piMMContourDriven-&gt;SetWireFrameGeometry(MfgAlgGuide2,ListOfGuide2); // Second guide

&nbsp;  rc = piMMContourDriven-&gt;AddMacroSyntax(1,&quot;START&quot;); // Approach macro
&nbsp;  rc = piMMContourDriven-&gt;AddMacroTangentMotion(1,10.,90.,0.);
&nbsp;  rc = piMMContourDriven-&gt;AddMacroToAPlaneMotion(1,MacroPlane);

&nbsp;  rc = piMMContourDriven-&gt;AddMacroSyntax(2,&quot;END&quot;); // Retract macro
&nbsp;  rc = piMMContourDriven-&gt;AddMacroTangentMotion(2,10.,90.,0.);
&nbsp;  rc = piMMContourDriven-&gt;AddMacroToAPlaneMotion(2,MacroPlane);
&nbsp;  ...
&nbsp;  CATBaseUnknown_var spContourDrivenTP;
&nbsp;  rc = piMMContourDriven-&gt;ComputeToolPath(spTPContainer,spContourDrivenTP);
```

```vbscript
&nbsp;  ...
&nbsp;  CATIPrtContainer_var spPrtContainer = ispPartContainer;
&nbsp;  if (NULL_var != spPrtContainer)
&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;  CATISpecObject_var spRootPart = spPrtContainer-&gt;GetPart();
&nbsp;&nbsp;&nbsp;&nbsp;  spMechRootFactory-&gt;CreateGeometricalSet(&quot;&quot;,spRootPart,ospGeomSet);&nbsp;&nbsp;&nbsp;&nbsp; 
&nbsp;  }
&nbsp;  ...
&nbsp;  CATIMfgTPMultipleMotion_var spMultipleMotion ((*pListOfMultipleMotion)[1]);
&nbsp;  if (NULL_var != spMultipleMotion)
&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;  spMultipleMotion-&gt;GetNumberOfSubTrajects(NbSubTrajects);
&nbsp;&nbsp;&nbsp;&nbsp;  for (int ia=1;ia&lt;=NbSubTrajects;ia++)
&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATIMfgTPMultipleMotion::SubTrajectType SubTrajectType;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spMultipleMotion-&gt;GetSubTrajectType(ia,SubTrajectType);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (CATIMfgTPMultipleMotion::UserSyntax == SubTrajectType) // Syntax defined in macros
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATUnicodeString Syntax;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spMultipleMotion-&gt;GetUserSyntaxCharacteristics(ia,Syntax);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (0 != Syntax.Compare(&quot;START&quot;)) GreenColor = 1;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  else if (0 != Syntax.Compare(&quot;END&quot;)) GreenColor = 0;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  }
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  else // Traject
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  int StartNumber =0, EndNumber =0;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spMultipleMotion-&gt;GetStartAndEndNumber(ia,StartNumber,EndNumber);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  for (int ib=StartNumber;ib&lt;=EndNumber;ib++)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  double x=0.,y=0.,z=0.;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spMultipleMotion-&gt;GetTipPoint(ib,x,y,z);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  double Coord [3] = {x,y,z};
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATIGSMPoint_var spGSMPoint = spGSMFactory-&gt;CreatePoint(Coord);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  ...
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (1 == GreenColor) // Points lying on parts will be green
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATIVisProperties_var spGraphicsPoint = spGSMPoint;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  if (NULL_var != spGraphicsPoint)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  {
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  CATVisPropertiesValues VisProperties;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  VisProperties.SetColor(0, 255, 0); // Green color
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  spGraphicsPoint-&gt;SetPropertiesAtt(VisProperties, CATVPColor, CATVPPoint);
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  ...
```