---
```vbscript
title: "Extrema of a Solid"
category: "use case"
module: "CAACgmOperators"
tags: ["CAAGMOperatorsInterfaces", "CAAOpeA", "CAAOpeB", "CAAprogressBar", "CATIA", "CAAGMOperatorsProgressBar"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcProgressBar.htm"
converted: "2026-05-11T17:33:49.019696"
```

---
tags: ["CAAGMOperatorsInterfaces", "CAAOpeA", "CAAOpeB", "CAAprogressBar", "CATIA", "CAAGMOperatorsProgressBar"]
source_file: "Doc/online/CAACgmOperators/CAACgmUcProgressBar.htm"
converted: "2026-05-11T17:33:49.019696"
Progress Bar

---
converted: "2026-05-11T17:33:49.019696"
Progress Bar
Use Case
Abstract A progress bar is an object which indicates the progress of a task. CATIA provides several ways to manage progress bars in applications. The geometric modeler itself provides developers with a way to specify the progress rate of an algorithm. In your algorithm (the Run of an operator for example), you have to create a progress bar then mark out your code or put milestones reflecting the estimate progress of the global task when the current step is reached.
The progress bar can also be associated with an interrupt function which returns whether the task is to be interrupted. Another capability of the CGM progress bars consists of nested progress bars which apply to operators calling other operators having their own progress bars.

    * Classes to be Used
    * Use Case Description
    * References
---
Classes to be Used The CATCGMProgressBar class defines the geometric modeler progress bar.  Use Case Description The CAAGMOperatorsProgressBar.m module in CAAGMOperatorsInterfaces.edu illustrates how to implement a progress bar in two operators A and B, operator B being called by operator A.  Operator B iterates over the creation of topological points, an easy way to specify some progress rates. A function is associated with the progress bars so that each time a progress rate is specified in either operator, the progress rate is displayed on the standard output. In a true application, an interruption function would be usually written by the calling application. This interruption function would detect a user interaction to stop the current operation. No user interaction would allow the operator to proceed to the next step.  This use case is made up of several parts
    *  The main program (CAAprogressBar.cpp) creates and runs operator A.
    * CAAOpeA.cpp defines an operator with a progress bar. Two progress rates are specified for operator A. Operator B is called by operator A and a nested progress bar is created for operator B. A function is associated with operator B progress bar.
    * CAAOpeB.cpp defines an operator which creates points. The number of iterations within the loop to create points is used to specify progress rates.
    * the interruption function is defined in InterruptFc.cpp.
Classes to be Used The CATCGMProgressBar class defines the geometric modeler progress bar.  Use Case Description The CAAGMOperatorsProgressBar.m module in CAAGMOperatorsInterfaces.edu illustrates how to implement a progress bar in two operators A and B, operator B being called by operator A.  Operator B iterates over the creation of topological points, an easy way to specify some progress rates. A function is associated with the progress bars so that each time a progress rate is specified in either operator, the progress rate is displayed on the standard output. In a true application, an interruption function would be usually written by the calling application. This interruption function would detect a user interaction to stop the current operation. No user interaction would allow the operator to proceed to the next step.  This use case is made up of several parts
This use case creates its own input data. If you are not already familiar with geometric modeler use cases, go to [About Geometric Modeler Uses Cases](../CAACgmModel/CAACgmUcGMUseCases.md). Running this use case displays the progress rates of operator A as well as the "nested" progress rates of operator B. The progress bars of operators A and B is illustrated in figure below. Fig.1 Operator B nested progress bar ![Nested Progress Bars](images/CGM_progress_bar_0.png)

---
References [1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)
---|---
[2] |  [About Geometric Modeler Use Cases](../CAACgmModel/CAACgmUcGMUseCases.md)
[3] |  [How to Use Topological Operators](../CAACgmModel/CAACgmTaUseTopoOperators.md)
History Version: **1** [Oct 2011] | Document created
---|---
