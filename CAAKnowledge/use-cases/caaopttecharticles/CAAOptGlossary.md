---
title: "KnowledgeOptimizer Glossary"
category: "use-case"
module: "CAAOptTechArticles"
tags: []
source_file: "Doc/online/CAAOptTechArticles/CAAOptGlossary.htm"
converted: "2026-05-11T17:33:46.040567"
---

3D PLM PPR Hub Open Gateway |  Knowledge Modeler |  Optimization Glossary _To understand what we are talking about_  
---|---|---  
Technical Article  
  
* * *

Abstract The purpose of this article is to give you the right definition for each term of the Knowledge vocabulary used in the context of the OptimizationInterfaces framework.

  * **General - Product Definition**
  * **Product Engineering Optimizer V5 Objects**
  * **Product Engineering Optimizer Additional Concepts**
  * **Relies on KnowledgeInterfaces Concepts**
  * **Relies on ObjectSpecsModeler Concepts**
  * **Where To Find Each Concept In The Code**

  
---  
  
* * *

General - Product Definiton **Product Engineering Optimizer:** Product required for using OptimizationInterfaces framework. **PEO:** Acronym for Product Engineering Optimizer product.  Product Engineering Optimizer V5 Objects (persistent features) **Optimization:** Defines an optimization problem (minimization, maximization or target value) with optimization constraints, the way to perform it (algorithms used, free parameters) and the results associated to it. There are several optimizations. **Optimization problem:** Describes the problem to solve, which is made of an optimization goal (eventually several) to reach and some optimization constraints to respect. **Optimization goal:** Describes optimization goal to reach which is made of  a goal parameter, an objective (minimum, maximum, target value), a target value eventually, and a priority. **Optimization free parameter:** Describes a parameter that can be changed during the optimization. It references an actual parameter and adds some information like ranges, etc. **Optimization algorithm:** Describes the strategy for solving a problem. It includes a set of settings that is depending on the algorithm (ending criteria, speed, etc). There are several algorithms. **Constraint satisfaction:** Describes a constraint satisfaction problem. It is a set of equations and inequations, with some selected input parameters and some output parameters. It can be solved and produces several solutions. Product Engineering Optimizer Additional Concepts **External Optimization Algorithm:** Customer can introduce their own algorithm, with a dedicated User Interface. **External sensors producing derivatives:** Customer can introduce their own sensors that will be used as optimization goals or constraints, and that can produce derivatives. Relies On KnowledgeInterfaces Concepts **Literal:** Optimizations are manipulating literal parameters (numerical ones in fact). Relies On ObjectSpecsModeler Concepts **Inputs and ouputs of the optimization problem:** Objects that knows how to be updated and that are the inputs and outputs of the optimization problems. Where To Find Each Concept In The Code ![](images/CAAOptGlossaryArray.jpg)

* * *

References [1] | [ KnowledgeAdvisor Glossary](../CAAKniTechArticles/CAAKniGlossary.md)  
---|---  
[Top]  
  
* * *

History Version: **1** [Nov 2004] | Document created  
---|---  
[Top]  
  
* * *

_Copyright 2004, Dassault Systmes. All rights reserved._
