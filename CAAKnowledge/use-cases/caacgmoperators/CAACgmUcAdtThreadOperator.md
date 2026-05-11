---
```vbscript
title: "Threading a Rod"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMOperatorsJournalThreadOpMain", "CAADoc", "CAAGMModelGemBrowser", "CAASweepProfile", "CAAGMOperatorsJournalThreadUtility", "CAASweepCreate", "CATICGMFrFTopologicalSweep", "CAAAdtJournalThread", "CAAAdtJournalCreateThread"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtThreadOperator.htm"
converted: "2026-05-11T17:33:48.868926"
```

---
tags: ["CAAGMCheckForPart", "CAAGMOperatorsInterfaces", "CAAGMOperatorsJournalThreadOpMain", "CAADoc", "CAAGMModelGemBrowser", "CAASweepProfile", "CAAGMOperatorsJournalThreadUtility", "CAASweepCreate", "CATICGMFrFTopologicalSweep", "CAAAdtJournalThread", "CAAAdtJournalCreateThread"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcAdtThreadOperator.htm"
converted: "2026-05-11T17:33:48.868926"
Threading a Rod

---
converted: "2026-05-11T17:33:48.868926"
Threading a Rod
Use Case
Abstract The CAAGMOperatorsJournalThreadOpMain use case provides you with a way to create an operator that threads a rod. To achieve the threading, an appropriate profile is swept along an helix, then after being closed, the resulting body is removed from the rod to be threaded.  This use case also illustrate how to check a journal by using the CAAGMCheckForPart.h operator.

    * What You Will Learn With This Use Case
    * The CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Use Cases
      * What Do CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility do?
      * How to Launch CAAGMOperatorsJournalThreadOpMain
      * Where to Find the CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility code
    * Step-by-Step
    * In Short
    * References
---
What You Will Learn With This Use Case In this use case, you learn how to create a sweep, close it and remove the resulting body from the rod to be threaded. You also learn the basics about how to create a user operator. The CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Use Cases CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility are use cases of the CAAGMOperatorsInterfaces.edu framework that illustrate the GMOperatorsInterfaces framework capabilities. What Do CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Do? ![Threaded Rod](images/CAACgmAdtresultthread.gif) | The CAAGMOperatorsJournalThreadUtility use case defines the CAAAdtJournalThread operator. Like any other operator, it must specify
    * A constructor as well as a destructor.
    * A Run method.
    * A GetResult method.
What You Will Learn With This Use Case In this use case, you learn how to create a sweep, close it and remove the resulting body from the rod to be threaded. You also learn the basics about how to create a user operator. The CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Use Cases CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility are use cases of the CAAGMOperatorsInterfaces.edu framework that illustrate the GMOperatorsInterfaces framework capabilities. What Do CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Do? ![Threaded Rod](images/CAACgmAdtresultthread.gif) | The CAAGMOperatorsJournalThreadUtility use case defines the CAAAdtJournalThread operator. Like any other operator, it must specify
In addition, two global functions which are discussed later on are defined in the CAAGMOperatorsJournalThreadUtility use case. The CAAGMOperatorsJournalThreadOpMain use case contains the main program that creates the cylinder to be threaded and call the CAAAdtJournalThread operator.  This is the solid you obtain when you execute the CAAGMOperatorsJournalThreadOpMain use case.

How to Launch CAAGMOperatorsJournalThreadOpMain You must compile CAAGMOperatorsJournalThreadUtility prior to launching CAAGMOperatorsJournalThreadOpMain. CAAGMOperatorsJournalThreadOpMain requires CAAGMOperatorsJournalThreadUtility as a module to be linked with in its Imakefile.mk file. To launch CAAGMOperatorsJournalThreadOpMain, you will need to set up the build time environment, then compile CAAGMOperatorsJournalThreadOpMain.m, set up the run time environment, and then execute the use case [1]. This use case creates its own input data. It must be executed with three arguments which are output files: `CAAGMOperatorsJournalThreadOpMain resultFile.NCGM verdictFile.md warningFile.htm`
    * The first argument is the resulting NCGM file.
    * The second argument is a "verdict" file in .md format. This file tells you whether the rules a journal has to comply with to be valid are fulfilled.
    * The third argument is a "warning" or detailed file also in .md format. This file tells you why the journal is not valid and which statements are to be investigated to fix the journal. It also reminds the input data which have be passed to the journal checker.
```vbscript
For information on journal checking, refer to:
```

    * [Topological Journal: Methodology](CAACgmTaTopJournalMethodology.md)
    * [Topological Journal: Writing a Validation Tool](CAACgmUcJournalChecking3.md)
    * [Topological Journal: Creation and Validation (1)](CAACgmUcJournalChecking1.md)
    * [Topological Journal: Creation and Validation (2)](CAACgmUcJournalChecking2.md)

This NCGM file can be displayed using the CAAGMModelGemBrowser use case. Where to Find the CAAGMOperatorsJournalThreadOpMain and CAAGMOperatorsJournalThreadUtility Code The CAAGMOperatorsJournalThreadOpMain use case is made of a main named CAAAdtJournalCreateThread.cpp located in the CAAGMOperatorsJournalThreadOpMain.m module of the CAAGMOperatorsInterfaces.edu framework: `InstallRootFolder\CAADoc\CAAGMOperatorsInterfaces.edu\CAAGMOperatorsJournalThreadOpMain.m\` where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed. This use case uses the CAAAdtJournalThread class which is defined in the CAAGMOperatorsJournalThreadUtility.m module. Step-by-Step The CAAGMOperatorsJournalThreadOpMain use case is divided into the following main steps:
    * Creation of the geometry factory (not discussed below - see for example [2]).
    * Creation of a CATSolidCylinder (see [2]).
    * Creation of the thread operator by using the CAAAdtJournalThread operator defined in the CAAGMOperatorsJournalThreadUtility.m module. This is the most interesting part of the use case. In this part, we must define:
      * The constructor and the destructor of the operator.
      * The Run() method whose operations are going to be reviewed below:
        1. Creation of a first sweep.
        2. Boolean remove from the initial rod.
        3. Creation of a second sweep.
        4. Boolean remove from the body resulting from the first remove.

      * The GetResult() method.
    * Running the CAAAdtJournalThread operator and retrieving the resulting body in the main program.
2. Boolean remove from the initial rod.
3. Creation of a second sweep.
4. Boolean remove from the body resulting from the first remove.
The Methodology At first sight, the methodology to thread this rod would consist in removing a single triangular sweep from the cylindrical rod as indicated below: Step 1: Creating a cylindrical rod | Step 2: Sweeping a triangular profile
along an helix | Step 3: Boolean remove

The Methodology At first sight, the methodology to thread this rod would consist in removing a single triangular sweep from the cylindrical rod as indicated below: Step 1: Creating a cylindrical rod | Step 2: Sweeping a triangular profile
along an helix | Step 3: Boolean remove
However, a usual source of problems when performing boolean operations is tangent or near-tangent surfaces. In the sequence of operations above, removing the sweep from the rod would result in a crash because the cylindrical surfaces of both operands are coincident. This problem can be worked around by creating extensions so that the sweep to be subtracted out has a diameter slightly larger that the rod diameter. Another source of problem is when one operand auto-intersects. If we make the sweep jut out from the rod, unless the sweep auto-intersects, parasite cylindrical faces will be generated in place of the outer edge of the thread. This is not what we want to obtain. To get over these two restrictions, we decided to proceed in two phases: **Phase 1** : a first sweep is created. The profile for this first sweep is a rectangular triangle as described below. This sweep is removed from the rod. Phase 1 (a): Initial rod | Phase 1 (b): First sweep | Phase 1 (c): First Boolean remove

**Phase 2** : a second sweep is created. A symmetrical profile is used for this second sweep. This second sweep is removed from the solid resulting from the first boolean remove. Phase 2 (a): Intermediary solid | Phase 2 (b): Second sweep | Phase 2 (c): Second Boolean remove
---|---|---

Creating the Sweeps The sweeps are created in the CAASweepCreate function. The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalSweep global function requires a guide and a profile as arguments.

    // a - Create the sweep operator
    //
Creating the Sweeps The sweeps are created in the CAASweepCreate function. The CATICGMFrFTopologicalSweep operator is created by the CATCGMCreateFrFTopologicalSweep global function requires a guide and a profile as arguments.
    CATICGMFrFTopologicalSweep * pSweepOperator = CATCGMCreateFrFTopologicalSweep(
            myFactory,
            myTopdata,
            iHelix,     //  guide
            iSection);  //  profile

Other parameters are tuned by using the Setxxx methods. Specifying the Guide The guide is an helix which is created by the CATCGMCreateTopHelix global function.

    // b - Helix creation
    //
Other parameters are tuned by using the Setxxx methods. Specifying the Guide The guide is an helix which is created by the CATCGMCreateTopHelix global function.
    CATBody* piHelix = CATCGMCreateTopHelix(
            _factory,
            _topData,
            piHelixAxis,                     // axis
            1,                               // orientation
            piBPOrigin,                      // origin
            CATAngle (0),                    // start angle
```vbscript
            CATAngle (helixAngleInt*CATPI),  // end angle
            CATLength (pitch),               // pitch
```

            1);                              // orientation of the rotation about the axis

The helix parameters are:

    * The axis is defined by the P1 and P2 CATMathPoint.
    * The origin which is not located on the rod cylindrical surface so that the sweep to be created later on protrude off the rod.

The helix parameters are:
          CATBody * piBPOrigin = CATCGMCreateTopPointXYZ (
            _factory,
            _topData,
            P1.GetX() + (cylRadius + **0.001**),
            P1.GetY(),
            P1.GetZ());

    * The start and end angle. The end angle (the number of helix turns) is roughly determined so that the portion of the rod to be threaded goes until an extremity of the rod. The distance where the thread starts is passed as the argument of the CAAAdtJournalThread constructor in the form of a length.
P1.GetX() + (cylRadius + **0.001**),
P1.GetY(),
P1.GetZ());
Specifying the Profile The profiles are defined in the CAASweepProfile function. They are originally created in the XOY plane but their positioning is moved to the beginning of the helix.

    CATMathAxis Ref; // the canonical math axis
    pSweepOperator->SetProfilePositionType(1);
    pSweepOperator->SetProfilePosition(&Ref); // set profile axis system

Specifying the reference element In order to avoid a twisted sweep, the XOY plane must be specified as the reference element. In Short When writing an operator such as CAAAdtJournalThread, the steps requiring attention are:

    * The definition of the sweep(s). An important parameter is the reference plane. If it is not properly specified, the resulting sweep can be twisted.
    * The boolean operations: a boolean remove operation cannot complete when there are tangent or near-tangent surfaces in both operands. You must design the operand to be extracted so that it protrudes off the operand it is to be extracted from.
pSweepOperator->SetProfilePosition(&Ref); // set profile axis system
Specifying the reference element In order to avoid a twisted sweep, the XOY plane must be specified as the reference element. In Short When writing an operator such as CAAAdtJournalThread, the steps requiring attention are:
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)

[2] | [Overview of the Topological Operators](CAACgmUcTopOverview.md)
History Version: **1** [Mar 2002] | Document created
---|---
