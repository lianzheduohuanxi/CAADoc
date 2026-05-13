---
title: "Untitled"
category: "use-case"
module: "CAASchUseCases"
tags: ["CATInit", "CAADocStyleSheets", "CAASchPlatformModeler", "CAASchAppSample2Main", "CAASchAppBaseEnv", "CAASchEduIn2", "CAASchApp", "CAASCHEDU_SamplePID", "CAADocUseCases", "CATISchCompGraphic", "CAASchAppUtilities", "CATISpecObject", "CATISchComponent", "CAASchEduOut2", "CATISchAppObjectFactory", "CAASchAppSample2", "CAASchAppBase", "CAASchAppSample1", "CATIView", "CATISchSession"]
source_file: "Doc/online/CAASchUseCases/CAASchSample2.htmmd"
converted: "2026-05-11T11:27:02.667683"
---

---

---

### What You Will Learn With This Use Case

This use case is intended to help you understand how to use the CAA Schematic
Platform Interfaces to manipulate Graphical Representations (GRRS) of Schematic
components.

[Top]

### The CAASchAppSample2 Use Case

CAASchAppSample2 is a use case of the CAASchPlatformModeler.edu framework
that illustrates CAASchPlatformModeler framework capabilities. The use case
demonstrates the creation of a component for a sample Schematics application, **CAASCHEDU_SamplePID**.

[Top]

#### What Does CAASchAppSample2 Do

The sample demonstrates the use of multiple Graphical Representations (GRRs)
of a component and the ability to swap these representations among the instances
of the component.

[Top]

#### How to Launch CAASchAppSample2

To launch CAASchAppSample2, you will need to set up the build time
environment, then compile CAASchAppSample2 along with its prerequisites, set up
the run time environment, and then execute the sample. This is fully described
in the referenced article [1]. When launching the use
case, you must pass the following arguments:

  
- **CAASchEduIn2.CATProduct** - the entire pathname, name and extension
    (.CATProduct) of the input drawing. Normally, it should be stored in the
    CNext/resources/graphic file directory.
  
- **CAASchEduOut2.CATProduct** - the entire pathname, name and extension
    (.CATProduct) under which the new document is to be stored

[Top]

#### Where to Find the CAASchAppSample2 Code

CAASchAppSample2 code is located in the CAASchAppSample2.m use case module of
the CAASchPlatformModeler.edu framework:

where `InstallRootDirectory` is the root directory of your CAA V5
installation. It is made of a two unique source files named
CAASchAppSample2Main.cpp and CAASchAppSample2.cpp.

Additional prerequisite code is located in the CAASchAppUtilities.m and
CAASchAppBase.m modules of the same framework.

[Top]

### Step-by-Step

These are the logical steps in CAASchAppSample2:

  
- Prolog
  
- Initializing the Environment
  
- Obtaining the List of GRRs for the Component
    Reference Object
  
- Adding additional GRRs to the Component
    Reference Object
  
- Placing another Instance of the
    Component on the Main Sheet
  
- Activating a Second Occurrence of the Instance using a
    Different GRR
  
- Swapping GRRs

[Top]

#### Prolog

In this use case, we open an input drawing containing one main sheet and one
detail sheet. The main sheet contains one component instantiated from a
reference object. The detail sheet contains three views. The use case will
create a new .CATProduct drawing for the sample application.

[Top]

#### Initializing the Environment

The CAASchAppSample2 code is derived from the CAASchAppBaseEnv base class.
The base class contains functionality common to the other CAASchApp samples.
Initializing the environment involves the following methods:

These methods perform the following functions:

  
- Creating a session, namely "Session DSA CAASchAppBaseEnv
    CATProduct".
  
- Obtaining the *CATISchSession* interface from the session.
  
- Obtaining the *CATISchBaseFactory* interface from the session
  
- Obtaining the applications *CATISchAppObjectFactory* interface
    pointer.
  
- Loading the input document.
  
- Initializing the document using the *CATInit* interface.
  
- Obtaining the pointer to the component reference.

[Top]

#### Obtaining the List of GRRs for the Component
Reference Object

In order to add to the list of GRRs for the component reference, we first
obtain the current list of GRRs. We dont want to add a duplicate GRR to our
component reference. To obtain the list of GRRs, the code uses the *CATISchCompGraphic*
interface method ListGraphicalRepresentations. From this method we obtain a list
of GRR, each of which we can query for the *CATIView* interface pointer.

Since the drawing was created by CAASchAppSample1, we know there is only one
GRR in the list.

[Top]

#### Adding Additional GRRs to the Component
Reference Object

To add a GRR to a component reference we use the the *CATISchCompGraphic*
interface method `AddGraphicalRepresentation`. This method has one
argument which is of type CATISchGRRComp*. The code loops through all the view
in the detail sheet. When it finds a view, it checks to see if it matches the
view of the original GRR. If not, it adds the GRR to the component. Since the *CATISchGRRComp*
interface is tied to the view object, we can obtain the CATISchGRRComp* for each
view.

[Top]

#### Placing Another Instance of the
Component on the Main Sheet

Placing an instance of the component reference is done using the PlaceInSpace
method of the CATISchComponent interface. The coding is similar to that of
CAASchAppSample1.

[Top]

#### Activating a Second Occurrenc of the Instance using a
Different GRR

A component may have more than one occurrence shown on the drawing. This is
not the same as instantiating the component reference another time. Rather, it
is useful for allowing the representation of a component to be shown in
different locations on a drawing with the same or a different GRR. Our component
reference object now has three GRRs. The code below shows the activating of
another occurrence of our component at a new location and using the second GRR.
This is done using the *CATISchCompGraphic* interface `Activate`
method from our placed component.

[Top]

#### Swap GRRs

The *CATISchCompGraphic* interface also has methods to allow switching
of the GRRs for a given occurrence or all occurrences of an object. The sample
shows using the `SwitchAll` method to change all the occurrences of
our new placed component to the second GRR.

[Top]

---

### In Short

This use case has demonstrated how to get a component reference object from a
drawing, manipulate it's GRRs, instantiate and activate more than one
occurrence. Specifically, it has illustrated:

  
- Obtaining the necessary Sch Interfaces
  
- Listing the Graphical Representations of a component reference
  
- Adding additional Graphical Representations to a component reference
  
- Activating additional occurrences of a component instance
  
- Swapping GRRs of a component instance

[Top]

---

### References

---

### History

---

*Copyright  2000, Dassault Systmes. All rights reserved.*

```vbscript
CAASchAppSample2::InitEnvironment
CAASchAppSample2::GetAppReference
CreateCATProductEnv::CreateCATProductEnv
```

```vbscript
//-------------------------------------------------------------------------
    //  Using the reference object, find CATISchCompGraphic interface.
    //-------------------------------------------------------------------------    
    HRESULT rc = _spAppRef-&gt;QueryInterface (IID_CATISchCompGraphic,(void **) &amp;piCompGraphic);
    if (!SUCCEEDED(rc))
    {
       cout &lt;&lt; &quot;cannot get CATISchCompGraphic interface &quot; &lt;&lt; endl;
       return 0;
    }
  
    //-------------------------------------------------------------------------
    //  Use the CATISchCompGraphic's method, ListGraphicalRepresentations, to
    //  find the current graphical representations for the object. 
    //
    //  Since this object was created in sample1, we know it will only have
    //  one GRR.  Use this to find the detail sheet and view of the GRR.
    //-------------------------------------------------------------------------
    int NbGRR = 0;
    if (SUCCEEDED (piCompGraphic-&gt;ListGraphicalRepresentations (&amp;pLIGRRs)))
    {
       unsigned int uSize = 0;
       if (SUCCEEDED (pLIGRRs-&gt;Count(&amp;uSize)))
       {
          cout &lt;&lt; &quot;Size of GRR List = &quot; &lt;&lt; uSize &lt;&lt; endl;
          NbGRR = uSize;
          if (uSize)
          {
             IUnknown *piUK = NULL;
             if (SUCCEEDED (pLIGRRs-&gt;Item(0,&amp;piUK)))
             {
                if ( SUCCEEDED (piUK-&gt;QueryInterface (IID_CATIView,(void **) &amp;piViewGRR1)))
                {
                   spDtlSheet = piViewGRR1-&gt;GetSheet(#);
                   if (!!spDtlSheet)
                   {
                      cout &lt;&lt; &quot;Got detail sheet containing the GRR detail &quot;
                           &lt;&lt; endl;
                   }
                }
                rc = piUK-&gt;QueryInterface (IID_CATISchGRRComp,(void **) &amp;piGRRComp1);
                CAASchAppDeleteBaseUnknown (piUK);
             }
          } 
       }
    }
```

```vbscript
for (int iView = 3; iView &lt;= SizeOfLView; iView++) 
        {
          if (LView[iView] != spSpecView)
          {
            if (SUCCEEDED ( (LView[iView])-&gt;QueryInterface (IID_CATISchGRRComp,(void **) &amp;piGRRComp)))
            {
              if (SUCCEEDED (piCompGraphic-&gt;AddGraphicalRepresentation (piGRRComp)))
              {
                cout &lt;&lt; &quot;successfully added GRR at position &quot; &lt;&lt; iView &lt;&lt; endl;
                NbGRR ++;
                if ( NbGRR == 2 ) piGRRComp2 = piGRRComp;
                if ( NbGRR == 3 ) piGRRComp3 = piGRRComp;
              }
            }
          }
	}
```

```vbscript
if ( SUCCEEDED(_spAppRef-&gt;QueryInterface (IID_CATISchComponent,(void **) &amp;piComponent)) )
    {
      double aDb6Axis[6] = {1.0,0.0, 0.0,1.0, 50.0,200.0};

      rc = piComponent-&gt;PlaceInSpace (NULL, aDb6Axis, &amp;piSchComp);
      if (SUCCEEDED (rc))
      {

        CATISpecObject *piSchCompInst = NULL;
        if (SUCCEEDED (piSchComp-&gt;QueryInterface (IID_CATISpecObject,(void **) &amp;piSchCompInst)))
        {
          piSchCompInst-&gt;SetName (SCHEDUPart_TestInst2);  // Name the instance
          CAASchAppDeleteBaseUnknown (piSchCompInst);
        }
```

```vbscript
double Db2Loc[2] = {220.0,200.0};
        char *pGRRName = NULL;
        if ( SUCCEEDED (piGRRComp2-&gt;QueryInterface(IID_CATISchGRR,(void**)&amp;piSchGRR) ) )
        {
          if ( SUCCEEDED (piSchGRR-&gt;GetGRRName(&amp;pGRRName)) )
          {
            rc = piSchComp-&gt;QueryInterface (IID_CATISchCompGraphic,(void **) &amp;piCompGraphic);
            if ( SUCCEEDED(rc) ) 
            {
              rc = piCompGraphic-&gt;Activate(pGRRName,Db2Loc,&amp;piNewGRRComp);
            }
```

```vbscript
if ( SUCCEEDED(piCompGraphic-&gt;SwitchAll(pGRRName)) )
   {
     cout &lt;&lt; &quot;Successfully switched all images&quot; &lt;&lt; endl;
   }
   else cout &lt;&lt; &quot;Failed to switch all images&quot; &lt;&lt; endl;
```