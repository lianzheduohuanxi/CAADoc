---
module: "CAAObjectModelerBase.edu"
category: "CAA 对象模型基础 — Session / Document / Navigate"
tier: "1"
status: "已完成"
---

# CAAObjectModelerBase.edu — 对象模型基础

## 模块定位

CAAObjectModelerBase 展示了 CAA 的**底层基础设施**——Session 管理、Document 生命周期、Root Container 访问，以及最重要的**规格树导航**（Specification Tree Navigation）模式。

这个模块规模虽小（5 个类），但揭示了 CAA 如何将自定义几何模型（CAASystem）**挂接到 CATIA 的文档管理和导航框架**中。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────┐
│                   CATSession                             │
│  Create_Session() ──→ 工作会话 ──→ Delete_Session()     │
│      │                                                   │
│      ├── CATDocument (New / Open / SaveAs / Remove)      │
│      │     │                                             │
│      │     └── CATInit::GetRootContainer("CATIPrtContainer")│
│      │           │                                        │
│      │           └── CATIContainer                        │
│      │                └── 自定义几何对象 (CAASysPoint...)  │
│      │                                                    │
│      └── 规格树 (Specification Tree)                       │
│            │                                              │
│            ├── CATINavigateObject 扩展                     │
│            │   ├── CAAOmbNavigateObjectRoot                │
│            │   │   (根节点：有子节点)                       │
│            │   └── CAAOmbNavigateObjectChildren            │
│            │       (叶子节点：无子节点)                     │
│            │                                              │
│            └── CATINavigModify 扩展                        │
│                ├── CAAOmbNavigModifyRoot                   │
│                │   (自定义节点外观：颜色、图标)              │
│                └── CAAOmbNavigModifyPoint                  │
│                    (自定义短帮助文本)                       │
└─────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. Session 生命周期（批处理模式）

```cpp
// 1. 创建 Session（批处理必须）
char *sessionName = "CAA2_Sample_Session";
CATSession *pSession = NULL;
HRESULT rc = ::Create_Session(sessionName, pSession);
// 批处理环境下必须手动创建 Session，交互模式下 CATIA 自动管理

// 2. 操作文档...

// 3. 删除 Session
rc = ::Delete_Session(sessionName);
```

**设计意图**：交互模式（CATIA 内部）会自动创建 Session。批处理模式（mkrun）必须手动管理 Session 生命周期。

### 2. Document 生命周期

```cpp
// 创建新文档
CATDocument *pDoc = NULL;
rc = CATDocumentServices::New("Part", pDoc);
// "Part" 是 File/New 对话框中显示的类型名
// 实际文件后缀为 .CATPart

// 打开已有文档
rc = CATDocumentServices::OpenDocument(filepath, pDoc);

// 保存
rc = CATDocumentServices::SaveAs(*pDoc, filepath);

// 从 Session 移除
rc = CATDocumentServices::Remove(*pDoc);
pDoc = NULL;  // 防止悬空指针
```

**关键约定**：操作完文档后必须 `Remove`——这是好习惯，防止同一文档在同一 Session 中重复加载时出现问题。

### 3. Root Container 访问

```cpp
CATInit *piInitOnDoc = NULL;
pDoc->QueryInterface(IID_CATInit, (void**)&piInitOnDoc);

CATIContainer *piRootContainer = (CATIContainer*)
    piInitOnDoc->GetRootContainer("CATIPrtContainer");

piInitOnDoc->Release();
piInitOnDoc = NULL;
```

**设计意图**：`CATInit` 是每个文档都实现的接口，`GetRootContainer` 通过字符串参数指定容器类型。不同的文档类型返回不同的容器接口（Part 文档返回 CATIPrtContainer）。

### 4. 规格树导航 — CATINavigateObject 接口

这是 CAA 中最重要的 UI 导航接口，控制**对象如何在规格树中显示**。

```cpp
// 必须实现两个方法：
virtual CATListValCATUnicodeString * GetIdentificators();
virtual CATListValCATBaseUnknown_var * GetChildren();
```

**GetIdentificators** — 返回节点显示的文字标识：
```cpp
// 根节点显示为 "Root" + 组件名称
CAAISysName *pISysName = NULL;
QueryInterface(IID_CAAISysName, (void**)&pISysName);
pISysName->GetName(Name);  // 从 CAASystem 获取名称
pIdent->Append(Name);
return pIdent;
```

**GetChildren** — 返回子节点列表：
```cpp
// 遍历 CAAISysCollection 获取所有几何对象
CAAISysAccess *piSysAccess = NULL;
QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
piSysAccess->GetContainer(&pContainer);
pContainer->QueryInterface(IID_CAAISysCollection, (void**)&piSysCollection);
piSysCollection->GetNumberOfObjects(&count);
for (int i=2; i<=count; i++) {  // 从 2 开始跳过根节点自身
    piSysCollection->GetObject(i, &pObject);
    pList->Append(pObject);
}
```

**有子节点 vs 无子节点**：
- `CAAOmbNavigateObjectRoot` — 根节点，GetChildren 返回所有子对象
- `CAAOmbNavigateObjectChildren` — 叶子节点，GetChildren 返回空列表

### 5. 规格树修改 — CATINavigModify 接口

控制节点外观和交互：

```cpp
class CAAOmbNavigModifyRoot : public CATNodeExtension {
    void UpdateElem(CATNavigInstance *iInstance);  // 自定义节点外观
};
```

**UpdateElem 中可以做的事**：
- `CATIGraphNode::SetColor(color)` — 设置节点颜色
- `CATIGraphNode::SetPixelImage(icon)` — 设置节点图标

```cpp
class CAAOmbNavigModifyPoint : public CATNodeExtension {
    HRESULT ModifyShortHelp(CATUnicodeString &ioText);  // 自定义悬停提示
};
```

### 6. 接口字典绑定

所有导航扩展通过 interface dictionary 绑定到组件：

```
# CAAObjectModelerBase.edu.dico
CAASysGeomRootObj      CATINavigateObject    libCAAOmbGeoNavigate
CAASysGeomRootObj_node CATINavigModify       libCAAOmbGeoNavigate
CAASysPoint            CATINavigateObject    libCAAOmbGeoNavigate
CAASysPoint_node       CATINavigModify       libCAAOmbGeoNavigate
CAASysLine             CATINavigateObject    libCAAOmbGeoNavigate
...
```

**命名约定**：`{ComponentName}_node` 是组件的"节点"扩展名，对应 CATINavigModify 扩展。

### 7. 数据导出 — CATIExportTypeManager

```cpp
class CAAEOmbExportTypeData : public CATBaseUnknown {
    virtual HRESULT ExportData(CATDocument *ipDoc, CATUnicodeString iPath);
    virtual HRESULT ExportData(CATUnicodeString iToExportPath,
                               CATUnicodeString iExportedPath);
};
```

字典中注释掉的条目表明它扩展的是 CATProduct：
```
#CAA# CATProduct_OmbExportType  CATIExportTypeManager  libCAAOmbExportType
```

---

## 与 Tier 1 其他模块的关系

```
CAAObjectModelerBase (本文档)
  ├─ Session/Document 管理 → 所有 CAA 应用的基础
  ├─ CATINavigateObject → 将 CAASystem 组件接入 CATIA 规格树
  │     │
  │     │  读取数据
  │     ▼
  │  CAASystem (数据模型)
  │     │
  │     │  渲染
  │     ▼
  │  CAAVisualization (可视化)
  │     │
  │     │  交互
  │     ▼
  │  CAAApplicationFrame (UI 框架)
```

**关键桥接**：`CAAOmbNavigateObjectRoot::GetChildren` 通过 CAAISysCollection 遍历几何对象，这是 CAA 中**数据模型 ↔ UI 框架**的桥接点。

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| Session 管理 | Create_Session / Delete_Session 全局函数 | 批处理必须手动管理 |
| Document 生命周期 | CATDocumentServices::New/Open/SaveAs/Remove | 工厂式创建，引用计数释放 |
| Container 访问 | CATInit::GetRootContainer(type) | 按类型字符串获取容器接口 |
| Navigate 扩展 | DataExtension + TIE_CATINavigateObject | 每个组件都有导航扩展 |
| NavigModify 扩展 | CATNodeExtension 子类 | 自定义节点外观和提示 |
| 字典绑定 | .dico 文件声明扩展关系 | 框架按组件名查找扩展 |

---

## 对 AI agent 的要点

1. **批处理程序必须**：Create_Session → 操作 → Delete_Session
2. **Document 操作模式**：New/Open → QueryInterface(CATInit) → GetRootContainer → 操作 → SaveAs → Remove
3. **CATINavigateObject 是规格树入口**：实现 GetIdentificators + GetChildren 即可将组件接入 CATIA 树
4. **CATINavigModify 自定义节点外观**：UpdateElem 设置颜色/图标，ModifyShortHelp 设置悬停提示
5. **字典声明格式**：`ComponentName  InterfaceName  LibraryName`
6. **_node 后缀**：表示组件的 NavigModify 扩展，如 `CAASysPoint_node CATINavigModify`
7. **容器类型字符串**：GetRootContainer("CATIPrtContainer") 中的字符串对应文档类型

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATInit.htm](../api-reference/interfaces/CATInit.htm)
- 完整方法签名: [api-reference/interfaces/CATIDocumentServices.htm](../api-reference/interfaces/CATIDocumentServices.htm)
- 完整方法签名: [api-reference/interfaces/CATINavigateObject.htm](../api-reference/interfaces/CATINavigateObject.htm)
- 完整方法签名: [api-reference/interfaces/CATINavigModify.htm](../api-reference/interfaces/CATINavigModify.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/caaombusecases/](../use-cases/caaombusecases/)