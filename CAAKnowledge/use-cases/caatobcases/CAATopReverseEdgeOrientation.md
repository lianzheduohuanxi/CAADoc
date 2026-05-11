---
title: "Geometric Modeler"
category: "use case"
module: "CAATobUseCases"
tags: ["CAATobReverseEdgeOrientation", "CATICGMObject", "CAATopologicalObjects", "CATICGMContainer"]
source_file: "Doc/online/CAATobUseCases/CAATopReverseEdgeOrientation.md"
converted: "2026-05-11T17:33:45.870486"
---

Geometric Modeler |  Topology |  Reversing the Orientation of an Edge _How to Modify the Topology_  
---|---|---  
Use Case  
  
* * *

Abstract This use case illustrates how to use the smart duplicator to modify the orientation of an edge. **Note that it is not recommended to modify the orientation of an edge. As explained in this article, in order to modify the orientation of an edge, you must actually re-create an edge with a new orientation and re-adjust all the topology around this edge. It is not easy and requires a deep knowledge of the geometric modeler. The geometric modeler is not designed to be used that way. Topological operators create bodies with a consistent topology, it is far better to stick to topological operators when creating topology.**

  * **What You Will Learn With This Use Case**
  * **The CAATobReverseEdgeOrientation Use Case**
    * What Does CAATobReverseEdgeOrientation Do?
    * How to Launch CAATobReverseEdgeOrientation 
    * Where to Find the CAATobReverseEdgeOrientation Code
  * **Step-by-Step**
  * **References**

  
---  
  
* * *

What You Will Learn With This Use Case This use case is intended to make you understand how to modify a topology by using the CATSmartBodyDuplicator operator. It also illustrates how to manipulate topological objects to change parameters such as matter sides or orientations. [Top] The CAATobReverseEdgeOrientation Use Case CAATobReverseEdgeOrientation is a use case of the CAATopologicalObjects.edu framework that illustrates the NewTopologicalObjects framework capabilities. [Top] What Does CAATobReverseEdgeOrientation Do? The CAATobReverseEdgeOrientation use case:

  * loads the container and retrieves the edge to be reversed 
  * reverses the edge orientation
  * writes the model and closes the factory. Note that, in this use case the output model is the same as the input model.

[Top] How to Launch CAATobReverseEdgeOrientation To launch CAATobReverseEdgeOrientation , you will need to set up the build time environment, then compile CAATobReverseEdgeOrientation.m along with its prerequisites, set up the run time environment, and then execute the use case [1]. With Windows CAATobReverseEdgeOrientation `e:/tobereversed.NCGM" e/outputFile.NCGM` With UNIX CAATobReverseEdgeOrientation `/u/`tobereversed`.NCGM e/outputFile.NCGM` where tobereversed.NCGM is an input file delivered in the CAATopologicalObjects.edu/FunctionTests/InputData file and outputFile.NCGM the file where you want to store the created data. [Top] WWhere to Find the CAATobReverseEdgeOrientation Code The CAATobReverseEdgeOrientation use case is made of a main named ReverseEdgeOrientationOpe.cpp located in the CAATobReverseEdgeOrientation .m module of the CAATopologicalObjects.edu framework: Windows | `InstallRootDirectory\CAATopologicalObjects.edu\CAATobReverseEdgeOrientation .m\`  
---|---  
Unix | `InstallRootDirectory/CAATopologicalObjects.edu/CAATobReverseEdgeOrientation .m/`  
where `InstallRootDirectory` is the directory where the CAA CD-ROM is installed. [Top] Step-by-Step There are three main steps in ReverseEdgeOrientation.cpp: 

  1. Loading the container and retrieving the edge to be reversed 
  2. Reversing the edge orientation
  3. Writing the model and closing the factory

[Top] Loading the Container and Retrieving the Edge to Be Reversed  The geometry factory (CATGeoFactory) creates and manages all the CATICGMObject (and the curves and surfaces in particular). In this use case, the factory is defined by reading a NCGM file that was previously stored, the global function `::CATLoadCGMContainer` must be used to retrieve the factory. The edge is retrieved by using the CATICGMContainer::FindObjectFromTag method. 456 is the edge tag.
    
    
    CATGeoFactory* piGeomFactory = CATLoadCGMContainer(filetoread);...
    CATICGMObject * piCGMObj1 = piGeomFactory->FindObjectFromTag( 456  ); 
    CATEdge* piEdge = (CATEdge *) piCGMObj1;
      
  
---  
Here is the input model. The edge to be reversed is highlighted. ![](images/reverseEdge.gif) [Top] Reversing the edge orientation If the edge is modified, the loop which contents this edge as well as the face on which this edge relies on have to be modified. The consistency of the whole topology must be achieved. This is what you have to do:

  1. Touch the edge to be reversed, "smart duplicate" the initial body and retrieve the duplicated edge, face and loop. You can turn to [Using the Smart Duplicator](CAATobSmartDuplicator.md) for more information on how to use the CATSmartBodyDuplicator operator. 
         
         CATBody * copBody = piGeomFactory->CreateBody();
         CATSmartBodyDuplicator * smartDuplicator = 
         copBody->CreateSmartDuplicator(piBody, topdata);
         if (smartDuplicator == NULL) return (1); 
         smartDuplicator->SetFullDuplication(1);  // you duplicate the link
         smartDuplicator->Run();
         // Retrieve the duplicated edge
         CATEdge * duplicatedEdge= (CATEdge *)smartDuplicator->GetDuplicatedCell(piEdge);
         ...
         CATFace * duplicatedFace= (CATFace *)smartDuplicator->GetDuplicatedCell(piFace);
         ...
         CATLoop * duplicatedLoop= (CATLoop *)smartDuplicator->GetDuplicatedDomain(piLoop);
         ...
                
  
---  
  2. Create a new edge with an opposite direction (for more information on how to create edges and associate geometry with topology, refer to [Using the TopologicalObjects](CAATobTetra.md)). 
         
         // Create a new edge
         CATEdge * ReplEdg = copBody -> CreateEdge();
         // Associate the new edge with a geometry and reversed curve orientation
         ReplEdg -> SetCurve(ecrv, -EdgVsECrv); // Associate the new edge with a geometry and reversed orientation
         ...
         for ( k=0; k<2; k++) {
         	ReplEdg -> AddBoundingCell(EndVtx[1-k], NaturalSide[k], 0, OldEndPoec[1-k]);
         }
         EndVtx[0] -> SetGeometryOnEdge(ReplEdg, CATSideRight, OldEndPoec[0]);
         EndVtx[1] -> SetGeometryOnEdge(ReplEdg, CATSideLeft,  OldEndPoec[1]);
                
  
---  
  3. Replace the old edge with the new edge in the duplicated loop by adding a new edge and removing the old one.
         
         CATLONG32 Rank = duplicatedLoop -> GetCellRank(duplicatedEdge, &ori);
         // Insert the new edge at the same rank
         duplicatedLoop -> InsertEdge(ReplEdg, Rank, -ori);
         // Remove the old edge
         duplicatedLoop -> RemoveCell(duplicatedEdge); 
          

  4. Invert the matter side with respect to the face 
         
         CATSide curside = piEdge->GetSideOnFace(piFace) ;  // the previous side
         // Invert the side
         if(curside  ==  CATSideRight) 
         { newside = CATSideLeft;}
         else if (curside  ==  CATSideLeft) 
         { newside = CATSideRight;}
         ... 
         ReplEdg -> SetSideOnFace(duplicatedFace, newside);
          

  5. Reset the new edge orientation vs the underlying PCurve 
         
         CATEdgeCurveIterator EdgeCurveIterator(ecrv);
         CATCurve * CurCurve = NULL;
         CATPCurve  * CurPCurve = NULL;
         while ( ( CurCurve = EdgeCurveIterator.Next() )  )
         	{
         	...
         	ReplEdg -> SetGeometryOnFace(duplicatedFace,
         		newside,
         		CurPCurve); 
         		}

[Top]  Writing the Model and Closing the Factory To save the model in a file, the `::CATSaveCGMContainer` global function is used. Notice that in the use case, the save is conditioned by an input parameter representing the file inside which the model must be saved. The use case ends with the closure of the geometry factory, done by the ` ::CATCloseCGMContainer` global function.
    
    
     if(1==toStore)
     {
    #ifdef _WINDOWS_SOURCE
       ofstream filetowrite(pFileName1, ios::binary ) ;
    #else
       ofstream filetowrite(pFileName1,ios::out,filebuf::openprot) ;
    #endif
    
       **::CATSaveCGMContainer**(piGeomFactory,filetowrite);
       filetowrite.close();
     }	
    
     _//
     // Close the container
     //_
     **::CATCloseCGMContainer**(piGeomFactory);  
  
---  
[Top]

* * *

References [1] |  [ Building and Launching a CAA V5 Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[Top]  
  
* * *

History Version: **1** [Jan 200 9 ] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2009, Dassault Systmes. All rights reserved._
