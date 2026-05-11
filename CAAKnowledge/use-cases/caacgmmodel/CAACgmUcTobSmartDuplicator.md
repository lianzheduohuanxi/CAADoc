---
title: "Using the Smart Duplicator"
category: "use case"
module: "CAACgmModel"
tags: ["CATICGMContainer", "CAADoc", "CATICGMObject", "CATICGMSmartBodyDuplicator", "CAAGMModelInterfaces", "CAATopSmartDuplicator", "CAAGMModelSmartDuplicator"]
source_file: "Doc\online\CAACgmModel\CAACgmUcTobSmartDuplicator.htm"
converted: "2026-05-11T17:33:48.560636"
---

Using the Smart Duplicator  
---  
Use Case  
Abstract Right after its creation a topology is modifiable. But when the body which contains this topology is frozen, you can no longer modify this topology. With the smart duplicator, you can modify only a part of a body. The part to be modified has to be "touched". This results in a new body sharing the untouched topologies with the initial body. This use case illustrates the smart mechanism with a skin body which has a holed face. Touching the holed face allows you to remove the internal domain to fill in the hole. 
    * What You Will Learn With This Use Case
    * The CAAGMModelSmartDuplicator Use Case
      * What Does CAAGMModelSmartDuplicator Do?
      * How to Launch CAAGMModelSmartDuplicator 
      * Where to Find the CAAGMModelSmartDuplicator Code
    * Step-by-Step
    * References  
---  
What You Will Learn With This Use Case This use case is intended to help you use the CATICGMSmartBodyDuplicator operator. The CAAGMModelSmartDuplicator Use Case CAAGMModelSmartDuplicator is a use case of the CAAGMModelInterfaces.edu framework that illustrates the GMModelInterfaces framework capabilities. What Does CAAGMModelSmartDuplicator Do? The CAAGMModelSmartDuplicator use case:
    * Loads the container and retrieves the skin body to be duplicated.
    * Retrieves the holed face and the inner loop of that face.
    * Specifies the cell to be modified in the smart duplication operation.
    * Creates a smart duplicator in order to modify the holed face and retrieves the duplicated face associated with the holed face.
    * Removes the internal loop in the duplicated face.
How to Launch CAAGMModelSmartDuplicator  To launch CAAGMModelSmartDuplicator, you will need to set up the build time environment, then compile CAAGMModelSmartDuplicator.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. CAAGMModelSmartDuplicator `e:\partwithhole.NCGM` where `partwithhole.NCGM` is an input file delivered in the CAAGMModelInterfaces.edu/FunctionTests/InputData file. Where to Find the CAAGMModelSmartDuplicator Code The CAAGMModelSmartDuplicator use case is made of a main named CAATopSmartDuplicator.cpp located in the CAAGMModelSmartDuplicator.m module of the CAAGMModelInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelSmartDuplicator.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. Step-by-Step There are six main steps in CAATopSmartDuplicator.cpp:
    1. Loading the Container and Retrieving the Body to Be Checked
    2. Retrieving the Holed Face
    3. Touching the Topology to Be Modified
    4. Creating a Smart Duplicated Body
    5. Modifying the Touched Topology
    6. Writing the Model and Closing the Factory
Loading the Container and Retrieving the Body to Be Checked The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored, the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The body is retrieved by using the CATICGMContainer::FindObjectFromTag method. There is only one body in the container which is loaded. 10990 is the body tag.
    
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);
    ...
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag(10990 ); 

The initial body looks something like this: ![](images/CAACgmTobsmartDup1.gif) Retrieving the Holed Face To retrieve the holed face, all the faces of the body are scanned and for each cell, the number of internal domains is computed. For the cells which have internal domains, the domains are scanned. The internal loop is detected by using CATDomain::GetLocation.
    
    for (int k = 1; k < faceList.Size()+1; k++)
    {
      CATCell * pLocalCell = faceList[k];
      if (pLocalCell && pLocalCell-gt;GetNbInternalDomains() > 0)
      {       
        int NbDomains=pLocalCell->GetNbDomains();
        for(int j=1;j<=NbDomains;j++)
        {
          CATDomain *pDomain=pLocalCell->GetDomain(j);
          CATLocation Location=pDomain->GetLocation();
          if (Location==CATLocationInner)
          {
            pInnerLoop=pDomain;                    // the inner loop 
            holedFace = (CATFace *) faceList[k] ;  // the holed face
            break; 
          }
        }
      }
    }

Touching the Topology to Be Modified The CATTopology::Touch method is used to specify which topology is going to be modified.
    
    holedFace->Touch(piBody);

Creating a Smart Duplicated Body First, you must create an empty body from CATGeoFactory. The CATICGMSmartBodyDuplicator operator is created from this new body. It must be run.
    
    CATBody * copBody = piGeomFactory->CreateBody();
    CATICGMSmartBodyDuplicator * smartDuplicator = 
      copBody->CreateISmartDuplicator(piBody, topdata);
    if (smartDuplicator == NULL) return (1); 
    smartDuplicator->Run();
    CATFace * duplicatedFace = (CATFace *)smartDuplicator->GetDuplicatedCell(holedFace);

The cell which has been initially touched is retrieved by using the CATICGMSmartBodyDuplicator::GetDuplicatedCell method. Modifying the Touched Topology The face inner loop is retrieved by scanning its domains. A domain which is an internal domain is removed.
    
    int NbD=duplicatedFace->GetNbDomains();
    for(int j=1;j<=NbD;j++)
    {
      CATDomain *pDom=duplicatedFace->GetDomain(j);
      CATLocation Loc=pDom->GetLocation();
      if(Loc==CATLocationInner)
      {
        duplicatedFace->RemoveDomain(pDom);
      }
    }

Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
    if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
       ofstream filetowrite(pfileName, ios::binary ) ;
    #else
       ofstream filetowrite(pfileName,ios::out,filebuf::openprot) ;
    #endif
    
       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }	
    
     //
     // Closes the container
     //
     **::CATCloseCGMContainer**(piGeomFactory);

The resulting body looks something like this: ![](images/CAACgmTobsmartDup2.gif) References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.htm)  
---|---  
History Version: **1** [Jan 2009] | Document created  
---|---
