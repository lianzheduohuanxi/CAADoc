---
module: "CAAProductStructure.edu"
category: "产品结构管理"
tier: "4"
status: "已完成"
---

# CAAProductStructure.edu — 产品结构管理

## 模块定位

CAAProductStructure 是 CAA 示例中用于演示 **CATIA 产品结构管理** 的教学框架。它展示了如何：
- 创建和管理产品（Product）对象
- 处理产品层次结构（父子关系）
- 导航产品树（CATINavigateObject）
- 管理产品属性
- 实现组件服务

**依赖关系**：继承自 Tier 1 的 CAAObjectModelerBase，需要 CATIProduct 接口。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                    CATIA 产品结构 (CAAProductStructure)           │
├─────────────────────────────────────────────────────────────────┤
│  CATIProduct                                                    │
│  ├── 产品基本操作（名称、版本、状态）                              │
│  ├── 组件管理（添加、移除、替换）                                 │
│  └── 引用管理（Master/Instance 关系）                            │
├─────────────────────────────────────────────────────────────────┤
│  CAAIPstINFRoot                                                 │
│  ├── AddChild() — 添加子特征                                     │
│  └── GetChildren() — 获取子节点列表                               │
├─────────────────────────────────────────────────────────────────┤
│  CATINavigateObject (DataExtension)                             │
│  ├── GetIdentificators() — 获取节点标识                          │
│  └── GetChildren() — 获取子节点                                  │
├─────────────────────────────────────────────────────────────────┤
│  CAAPstComponentServices                                        │
│  ├── AddExternalComponent() — 导入已有文档                       │
│  └── AddNewExternalComponent() — 创建并添加新组件                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心接口详解

### 1. CATIProduct — 产品根接口

CATIProduct 是 CATIA 产品结构的核心接口，由系统框架提供：

```cpp
// 产品基本信息
virtual CATUnicodeString GetPartNumber() = 0;
virtual CATUnicodeString GetRevision() = 0;
virtual CATUnicodeString GetDefinition() = 0;

// 组件管理
virtual HRESULT AddChild(CATIProduct * iChild) = 0;
virtual HRESULT RemoveChild(CATIProduct * iChild) = 0;
virtual CATIProduct * GetParent() = 0;

// 产品引用
virtual CATIProduct * GetMasterProduct() = 0;
virtual CATIProduct * GetReferenceProduct() = 0;
```

**设计意图**：CATIProduct 是 CATIA 中所有产品对象的基接口。它定义了产品的基本属性和父子层次关系，是产品结构管理的核心抽象。

### 2. CAAIPstINFRoot — 特征根节点

```cpp
// CAAIPstINFRoot.h
class CAAIPstINFRoot: public CATBaseUnknown {
    virtual HRESULT AddChild(CATISpecObject * ipiFeature) = 0;
    virtual HRESULT GetChildren(CATListValCATBaseUnknown_var **opList) = 0;
};
```

**IID**: `{0x82ee9602, 0x34c5, 0x11d6, {0x85, 0x0c, 0x00, 0x03, 0x47, 0x6e, 0xe1, 0x75}}`

**设计意图**：为产品/容器提供特征聚合能力。类似于 CATISpecObject 的父子关系管理，但针对产品结构场景。

### 3. CAAIPstINFPoint / CAAIPstINFLine / CAAIPstINFWire — 特征接口族

```cpp
class CAAIPstINFPoint: public CATBaseUnknown {
    // 点特征相关方法
};

class CAAIPstINFWire: public CATBaseUnknown {
    // 线特征相关方法
};
```

这些接口用于产品结构中的几何特征（点、线等）建模。

### 4. CAAPstComponentServices — 组件服务函数

```cpp
// 添加外部组件
HRESULT AddExternalComponent(
    CATIProduct* iThisProd,      // 目标产品
    CATDocument *iDocument,       // 要导入的文档
    CATIProduct** oNewProduct     // 新创建的产品对象
);

// 添加新组件
HRESULT AddNewExternalComponent(
    CATIProduct* iThisProd,      // 目标产品
    const CATUnicodeString iDocumentType,  // 文档类型 ("Part"/"Product")
    const CATUnicodeString iPartNumber,     // 件号
    CATIProduct** oNewProduct
);
```

**设计意图**：这些全局服务函数封装了 CATIProduct 的组件添加功能，提供了更高级别的 API。

---

## 实现模式

### 1. DataExtension + TIE 模式

CAAProductStructure 使用 DataExtension 实现 CATINavigateObject：

```cpp
// CAAEPstNavigateObject.cpp

// 创建 TIE 对象
#include "TIE_CATINavigateObject.h"
TIE_CATINavigateObject(CAAEPstNavigateObject);

// 声明为 DataExtension
CATImplementClass(CAAEPstNavigateObject,
    DataExtension,           // ← 扩展类型
    CATBaseUnknown,
    CAAPstBook);             // ← 扩展目标组件
```

**字典声明**：
```
CAAPstBook  CATINavigateObject  libCAAPstEduNavigBook
```

### 2. 应用容器模式

```cpp
class CAAPstAppliContProvider : public CATBaseUnknown {
    HRESULT GetChildren(CATBaseUnknown * iObj, 
                       CATLISTP(CATBaseUnknown) ** oListChildren);
};
```

### 3. 导航扩展提供者

```cpp
class CAAPstBookExtProvider : public CATBaseUnknown {
    // 提供 Book 类型的导航扩展
};

class CAAPstINFNavigProviderRoot : public CATBaseUnknown {
    // 提供根节点的导航扩展
};
```

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| 产品层次 | CATIProduct 父子关系 | GetParent(), AddChild() |
| DataExtension | 扩展产品组件 | CAAEPstNavigateObject |
| 导航接口 | CATINavigateObject | GetIdentificators(), GetChildren() |
| 服务函数 | 全局函数封装 | AddExternalComponent() |
| 特征聚合 | CAAIPstINFRoot | AddChild(), GetChildren() |

---

## 对 AI agent 的要点

1. **CATIProduct 是产品结构的根接口**，所有产品都实现此接口

2. **产品有两种模式**：Reference Product（主引用）和 Instance（实例），通过 GetMasterProduct/GetReferenceProduct 区分

3. **添加组件的三种方式**：
   - AddExternalComponent() — 导入已有文档
   - AddNewExternalComponent() — 创建新 Part/Product
   - 直接调用 CATIProduct::AddChild()

4. **CATINavigateObject 用于将产品接入 CATIA 树**，实现 GetIdentificators() + GetChildren() 即可

5. **组件服务函数封装了底层 CATIProduct 操作**，使用更方便

6. **DataExtension 用于给产品添加导航能力**，不需要修改产品类本身

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIProduct.htm](../api-reference/interfaces/CATIProduct.htm)
- 完整方法签名: [api-reference/interfaces/CATINavigateObject.htm](../api-reference/interfaces/CATINavigateObject.htm)
- 完整方法签名: [api-reference/interfaces/CATISpecObject.htm](../api-reference/interfaces/CATISpecObject.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)
