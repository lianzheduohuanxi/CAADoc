---
title: "CAA核心接口继承层次"
type: "quick-reference"
---

# CAA核心接口继承层次

## 基础接口

```
CATBaseUnknown
    │
    ├── CATIObject (对象)
    │    │
    │    └── CATIDocId (文档标识)
    │
    ├── CATIDocument (文档)
    │    ├── CATIPart (零件)
    │    ├── CATIProduct (产品)
    │    └── CATIAssembly (装配)
    │
    ├── CATIEditor (编辑器)
    │
    ├── CATIAlias (别名)
    │
    └── CATIAttribute (属性)
```

## 产品结构接口

```
CATBaseUnknown
    │
    └── CATIPLMNavReference (引用)
         │
         ├── CATIPLMNavOccurrence (实例)
         │
         └── CATIPLMNavProduct (产品)
              │
              ├── CATIPLMNavInstance (实例)
              │
              └── CATIPLMNavEntity (实体)
```

## 几何与拓扑接口

```
CATBaseUnknown
    │
    ├── CATIGeometricObject (几何对象)
    │    ├── CATICurve (曲线)
    │    │    ├── CATICircle
    │    │    ├── CATIEllipse
    │    │    ├── CATILine
    │    │    └── CATISpline
    │    │
    │    └── CATISurface (曲面)
    │         ├── CATICylinder
    │         ├── CATIPlane
    │         └── CATISphere
    │
    └── CATIBasicTopology (基础拓扑)
         ├── CATIFace (面)
         ├── CATIEdge (边)
         ├── CATIWire (线框)
         └── CATIBody (体)
```

## 工作台与命令接口

```
CATBaseUnknown
    │
    ├── CATIWorkbench (工作台)
    │
    ├── CATICommand (命令)
    │
    └── CATICommandHeader (命令头)
```

---
