---
title: "CAAEAfrCollection"
type: "LocalClass"
module: "CAAApplicationFrame"
base: "CATBaseUnknown"
method_count: 5
source_file: "CAAApplicationFrame.edu/CAAAfrGeoModel.m/LocalInterfaces/CAAEAfrCollection.h"
---

# CAAEAfrCollection

> Data extension implementing the CAAISysCollection interface which enables to manages the list of objects of the container in the CAAGeometry Document. So this extension extens the container. Inheritance: CATBaseUnknown (System Framework) Main Method: GetNumberOfObjects GetObject AddObject RemoveObject System framework

**基类**: CATBaseUnknown | **模块**: CAAApplicationFrame | **方法数**: 5

## 依赖

- `CATBaseUnknown.h`
- `CATCollec.h`

## 虚方法

### GetNumberOfObjects

```cpp
virtual HRESULT GetNumberOfObjects(int * oCount) ;
```

GetNumberOfObjects ------------------- Retrieves the number of object in the Collection. Return E_FAIL if the Collection is empty else S_OK

| 参数 | 类型 |
|------|------|
| oCount | `int *` |


### GetObject

```cpp
virtual HRESULT GetObject(int iRank, CATBaseUnknown ** oObject) ;
```

GetObject --------- Retrieves the iRank object in this Collection. Return E_FAIL if the Collection is iRank is bad else S_OK

| 参数 | 类型 |
|------|------|
| iRank | `int` |
| oObject | `CATBaseUnknown **` |


### AddObject

```cpp
virtual HRESULT AddObject(CATBaseUnknown * iObject) ;
```

AddObject --------- Adds iObject in the Collection, sets link for the display, sets link with the object which has created it (this) and send a notification to prevent that the model contains somethings

| 参数 | 类型 |
|------|------|
| iObject | `CATBaseUnknown *` |


### RemoveObject

```cpp
virtual HRESULT RemoveObject(CATBaseUnknown * iObject) ;
```

RemoveObject ------------ Removes iObject in the Collection, unsets link for the display, unsets link with the object which has created it (this) and send a notification to prevent that the model becomes empty

| 参数 | 类型 |
|------|------|
| iObject | `CATBaseUnknown *` |


### Empty

```cpp
virtual HRESULT Empty() ;
```

RemoveObject ------------ Empties the Collection, unsets link for the display, unsets link with the object which has created it (this)


---

**源文件**: `CAAApplicationFrame.edu/CAAAfrGeoModel.m/LocalInterfaces/CAAEAfrCollection.h`
