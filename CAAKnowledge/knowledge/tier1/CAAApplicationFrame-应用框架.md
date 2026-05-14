---
module: "CAAApplicationFrame.edu"
category: "CAA 应用框架 — Workbench / Addin / Command 完整模式"
tier: "1"
status: "已完成"
---

# CAAApplicationFrame.edu — 应用框架

## 模块定位

CAAApplicationFrame 展示了 CAA 中**最核心的 UI 架构模式**：Workshop（工作台）→ Workbench（工作间）→ Addin（插件）三级层次，以及 Command（命令）的注册和布局系统。

这不是 CATIA 的真实框架，而是**教学用的最小化完整示例**，演示了如何为一个自定义文档（CAAGeometry）构建完整的交互界面。

**与 CAASystem 的关系**：CAASystem 定义了数据模型（几何元素 + 集合），CAAApplicationFrame 在其上构建了用户交互层。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────┐
│                   CATIA 应用窗口                          │
│  ┌───────────────────────────────────────────────────┐  │
│  │           Workshop: CAAAfrGeometryWks              │  │
│  │  实现 CATIWorkshop (via TIE)                        │  │
│  │  ├─ GetWorkbenchInterface() → CATI*Configuration   │  │
│  │  ├─ GetAddinInterface()     → CAAI*WksAddin        │  │
│  │  ├─ CreateCommands()   — 注册命令 Header            │  │
│  │  └─ CreateWorkshop()   — 布局菜单和工具栏            │  │
│  │                                                     │  │
│  │  ┌─────────────────────────────────────────────┐   │  │
│  │  │   Workbench: CAAAfrGeoCreationWkb            │   │  │
│  │  │   实现 CATI*Configuration (via TIE)           │   │  │
│  │  │   ├─ GetAddinInterface() → CAAI*WkbAddin     │   │  │
│  │  │   ├─ CreateCommands()  — 注册实体/曲面命令     │   │  │
│  │  │   └─ CreateWorkbench() — 布局 Solid/Surface 工具栏│  │
│  │  │                                               │   │  │
│  │  │  ┌───────────────────────────────────────┐   │   │  │
│  │  │  │  Addin: CAAAfrGeoOperationAdn          │   │   │  │
│  │  │  │  实现 CAAI*WkbAddin (via TIE)           │   │   │  │
│  │  │  │  DataExtension of CAAAfrGeoOperationAddin│  │   │  │
│  │  │  │  ├─ CreateCommands() — Union/Subtract/Fillet│  │   │  │
│  │  │  │  └─ CreateToolbars() — 工具栏 + 菜单项    │   │   │  │
│  │  │  └───────────────────────────────────────┘   │   │  │
│  │  └─────────────────────────────────────────────┘   │  │
│  └───────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

**三级层次的关键区别**：

| 层级 | 实现接口 | 注册宏 | 创建什么 |
|------|------|------|------|
| Workshop | CATIWorkshop | CATDeclareWorkshopFactory | 菜单栏 + 工具栏 + 切换 Workbench 的标签 |
| Workbench | CATI*Configuration | CATDeclareConfigurationFactory | 工具栏 + 菜单项 |
| Addin | CATIWorkbenchAddin 子接口 | CATImplementClass(DataExtension) | 额外的工具栏 + 菜单项 |

---

## 核心接口详解

### 1. Workshop 接口体系

Workshop 定义了两个「接口标识」——它们本身是空接口，作用是**类型标记**：

```cpp
// 空接口：Workshop 的 Workbench 必须实现这个接口
class CATICAAAfrGeometryWksConfiguration : public CATIWorkbench {
    CATDeclareInterface;
};

// 空接口：Workshop 的 Addin 必须实现这个接口
class CAAIAfrGeometryWksAddin : public CATIWorkbenchAddin {
    CATDeclareInterface;
};
```

**设计意图**：Workshop 不关心 Workbench 的具体方法，只关心「你是我的 Workbench 类型」。通过 QueryInterface 查询这个标记接口来识别。这是 CAA 的**类型标记模式**。

### 2. Workshop 实现 — CAAAfrGeometryWks

```cpp
class CAAAfrGeometryWks : public CATBaseUnknown {
    CATDeclareClass;
public:
    void             CreateCommands();        // 注册命令 Header
    CATCmdWorkshop * CreateWorkshop();        // 布局 UI
    CATClassId       GetWorkbenchInterface(); // 返回 "CATICAAAfrGeometryWksConfiguration"
    CATClassId       GetAddinInterface();     // 返回 "CAAIAfrGeometryWksAddin"
};

// .cpp 中通过 TIE 绑定 CATIWorkshop 接口
TIE_CATIWorkshop(CAAAfrGeometryWks);
CATImplementClass(CAAAfrGeometryWks, Implementation, CATBaseUnknown, CATNull);
```

**CreateCommands 注册了约 15 个命令**，例如：
```cpp
new CAAAfrGeometryWksHeader("CAAAfrPointHdr",
    "CAADegGeoCommands",           // 命令所在的共享库
    "CAADegCreatePointCmd",        // 命令类名
    (void *)NULL);                 // 可选参数
```

每个命令有三个要素：Header 名称（唯一标识）、库名、类名。

### 3. Workbench 实现 — CAAAfrGeoCreationWkb

```cpp
// .cpp 中通过 TIE 绑定 Configuration 接口
TIE_CATICAAAfrGeometryWksConfiguration(CAAAfrGeoCreationWkb);
CATImplementClass(CAAAfrGeoCreationWkb, Implementation, CATBaseUnknown, CATNull);
```

**GetAddinInterface 返回 "CAAIAfrGeoCreationWkbAddin"**，告诉框架：只有实现了 CAAIAfrGeoCreationWkbAddin 接口的 Addin 才能附加到这个 Workbench。

### 4. Addin 实现 — CAAAfrGeoOperationAdn

```cpp
// .cpp
TIE_CAAIAfrGeoCreationWkbAddin(CAAAfrGeoOperationAdn);
CATImplementClass(CAAAfrGeoOperationAdn,
    DataExtension,                    // ← 关键：不是 Implementation！
    CATBaseUnknown,
    CAAAfrGeoOperationAddin);         // ← 扩展目标：late type
```

**Addin 是 DataExtension，不是 Implementation**。这意味着 Addin 附加到一个已存在的 late type 组件上，而不是独立存在。需要在 interface dictionary 中声明绑定关系。

### 5. 菜单/工具栏布局宏

CAA 使用一套宏来构建 UI 层次：

```
NewAccess(类型, 变量名, 标识符)          — 创建 UI 节点
SetAccessChild(父, 子)                  — 设为第一个子节点
SetAccessNext(前一个, 下一个)            — 设为兄弟节点
SetAccessCommand(Starter, "Header名")   — 绑定命令
SetAccessAnchorName(节点, "锚点名")      — 插入到指定位置
SetWorkshopMenu(Workshop, MenuBar)      — 合并 Workshop 菜单栏
SetWorkbenchMenu(Workbench, MenuBar)    — 合并 Workbench 菜单栏
SetAddinMenu(Toolbar, MenuBar)          — 合并 Addin 菜单
AddToolbarView(Toolbar, 可见性, 位置)    — 添加工具栏视图
```

**节点类型**：
- `CATCmdWorkshop` — Workshop 根节点
- `CATCmdWorkbench` — Workbench 根节点
- `CATCmdContainer` — 容器（Toolbar、Menu、SubMenu）
- `CATCmdStarter` — 命令启动器（按钮/菜单项）
- `CATCmdSeparator` — 分隔线

**命令参数传递**：
```cpp
// 同一个命令，不同参数 → 三个不同的 Header
new CAAAfrGeometryWksHeader("CAAAfrNormalXHdr",
    "CAAAfrGeoCommands", "CAAAfrChangeViewNormalCmd",
    (void *)CATINT32ToPtr(1));   // X 轴 → 参数 1

new CAAAfrGeometryWksHeader("CAAAfrNormalYHdr",
    "CAAAfrGeoCommands", "CAAAfrChangeViewNormalCmd",
    (void *)CATINT32ToPtr(2));   // Y 轴 → 参数 2
```

### 6. MRU 系统

```cpp
// 接口
class CAAIAfrMRUManagement : public CATBaseUnknown {
    virtual HRESULT AddElement(CATUnicodeString &) = 0;
    virtual HRESULT GetElementList(CATListOfCATUnicodeString &) const = 0;
    virtual HRESULT SelectElement(int iPosition) = 0;
};

// 获取函数（非工厂，而是查找已存在的 Manager）
HRESULT CAAAfrGetMRUManager(const IID &, void **);
```

MRU 不是通过工厂创建，而是通过全局函数查找已存在的 Manager 实例。

### 7. Command 模式 — CATCommand

```cpp
class CAAAfrDumpCmd : public CATCommand {
    // 激活命令时调用
    virtual CATStatusChangeRC Activate(
        CATCommand *iFromClient,
        CATNotification *iNotification);

    // 回调：对话框关闭时
    void CloseBox(CATCommand *, CATNotification *, CATCommandClientData);
};
```

Command 的生命周期由 CATCommand 框架管理：创建 → Activate → 用户操作 → 回调 → 销毁。

---

## 实现模式总结

### 模式 1: MacDeclareHeader — 命令注册

```cpp
// .cpp 顶部
MacDeclareHeader(CAAAfrGeometryWksHeader);

// CreateCommands 中
new CAAAfrGeometryWksHeader("标识名", "库名", "类名", 参数);
```

`MacDeclareHeader` 自动生成一个 CATCommandHeader 子类，构造函数接收四个参数。

### 模式 2: 命令头部自定义

```cpp
// 自定义 Header 类（非 MacDeclareHeader）
class CAAAfrDumpCommandHeader : public CATCommandHeader {
    // 覆盖 GetAvailability 控制命令何时可用
    // 覆盖 GetRep 自定义命令的视觉表现
};
```

### 模式 3: 工厂宏

```cpp
// Workshop 工厂
CATDeclareWorkshopFactory(CAAAfrGeometryWks);

// Workbench 工厂
CATDeclareConfigurationFactory(CAAAfrGeoCreationWkb);
```

工厂宏生成框架所需的样板代码，使框架能在适当时机创建 Workshop/Workbench 实例。

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| 类型标记 | 空接口作为类型标识 | CAAIAfrGeometryWksAddin（无方法，仅作标记） |
| 三级层次 | Workshop → Workbench → Addin | 命令和工具栏按层级聚合 |
| DataExtension | Addin 作为 late type 的扩展 | CAAAfrGeoOperationAdn extends CAAAfrGeoOperationAddin |
| TIE 委托 | 接口实现委托给组件类 | TIE_CATIWorkshop(CAAAfrGeometryWks) |
| 宏驱动的 UI 布局 | NewAccess/SetAccessChild 链式构建 | 菜单栏和工具栏的声明式布局 |
| 命令-Header 分离 | Header 定义何时可见，Command 定义做什么 | CAAAfrDumpCommandHeader + CAAAfrDumpCmd |
| 全局查找 | 非工厂创建，查找已存在实例 | CAAAfrGetMRUManager |

---

## 对 AI agent 的要点

1. **创建 Workshop 的三步**：定义 Configuration/Addin 空接口 → 实现类 + TIE → 工厂宏
2. **创建 Workbench 的三步**：实现 Configuration 接口 → 定义自己的 Addin 接口 → 工厂宏
3. **创建 Addin 的关键**：DataExtension（非 Implementation）+ TIE 绑定标记接口 + interface dictionary 声明
4. **命令注册**：MacDeclareHeader 在 .cpp 顶部 → new Header 在 CreateCommands 中
5. **菜单布局**：NewAccess 创建节点 → SetAccessChild/Next 构建树 → SetWorkshopMenu 合并
6. **命令参数**：同一个类不同参数通过不同 Header 名称区分，用 CATINT32ToPtr 传递
7. **Addin 是 DataExtension**，不是独立组件——它扩展一个 late type，生命周期依附于该组件

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIWorkshop.htm](../api-reference/interfaces/CATIWorkshop.htm)
- 完整方法签名: [api-reference/interfaces/CATIEditModel.htm](../api-reference/interfaces/CATIEditModel.htm)
- 完整方法签名: [api-reference/interfaces/CATIMmiWorkspace.htm](../api-reference/interfaces/CATIMmiWorkspace.htm)
- 完整方法签名: [api-reference/interfaces/CATIMmiApplication.htm](../api-reference/interfaces/CATIMmiApplication.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)