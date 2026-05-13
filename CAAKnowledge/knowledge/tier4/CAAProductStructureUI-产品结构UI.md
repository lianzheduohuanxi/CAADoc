---
module: "CAAProductStructureUI.edu"
category: "产品结构 UI"
tier: "4"
status: "已完成"
---

# CAAProductStructureUI.edu — 产品结构 UI

## 模块定位

CAAProductStructureUI 演示了 **CATIA 产品结构管理的用户界面实现**。它展示了：
- PRD（Product）工作台 Addin 的实现
- Config（配置）Addin 的实现
- 工具栏和命令的创建
- 菜单和工具栏的布局

**依赖关系**：基于 CAAProductStructure，需要 CAAApplicationFrame 的命令框架。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────┐
│                   PRD Workshop (产品结构工作台)                    │
├─────────────────────────────────────────────────────────────────┤
│  CAAPuiPRDWorkshopAddin                                         │
│  ├── CreateCommands() — 创建命令                                │
│  └── CreateToolbars() — 创建工具栏                              │
├─────────────────────────────────────────────────────────────────┤
│  CAAPuiPRDWorkshopConfig                                         │
│  ├── CreateCommands() — 创建配置命令                             │
│  └── CreateToolbars() — 创建配置工具栏                          │
├─────────────────────────────────────────────────────────────────┤
│  CAAPuiPrsConfigAddin                                           │
│  ├── CreateCommands() — 创建表示配置命令                         │
│  └── CreateToolbars() — 创建表示配置工具栏                      │
└─────────────────────────────────────────────────────────────────┘
```

---

## 核心接口详解

### 1. CATIPRDWorkshopAddin — PRD 工作台 Addin

```cpp
class CAAPuiPRDWorkshopAddin: public CATBaseUnknown {
    void CreateCommands();
    CATCmdContainer * CreateToolbars();
};
```

**设计意图**：PRD Workshop 的 Addin 实现，用于创建产品结构管理的命令和工具栏。

### 2. CAAIPuiPRDWorkshopConfigAddin — 配置 Addin 接口

```cpp
// 接口定义
class CAAIPuiPRDWorkshopConfigAddin: public CATBaseUnknown {
    void CreateCommands();
    CATCmdContainer * CreateToolbars();
};

// 实现
class CAAPuiPRDWorkshopConfig: public CATBaseUnknown {
    // 实现 CAAIPuiPRDWorkshopConfigAddin 接口
};
```

### 3. CAAPuiPrsConfigAddin — 表示配置 Addin

```cpp
class CAAPuiPrsConfigAddin: public CATBaseUnknown {
    void CreateCommands();
    CATCmdContainer * CreateToolbars();
};
```

---

## 实现模式

### 1. Workshop Addin 模式

```cpp
// CAAPuiPRDWorkshopAddin.cpp
CATImplementClass(CAAPuiPRDWorkshopAddin,
    Implementation,           // ← Implementation 类型
    CATBaseUnknown,
    CAAPstBook);            // ← 扩展的产品组件
```

### 2. 命令创建模式

```cpp
void CAAPuiPRDWorkshopAddin::CreateCommands() {
    // 使用 MacDeclareHeader 创建命令
    MacDeclareHeader(CAAPuiPRDWorkshopAddinCmd);
    
    // 创建命令实例
    new CAAPuiPRDWorkshopAddinCmd(
        "标识名",           // Header 标识
        "CAAPuiPRDWorkshopAddin",  // 库名
        "CAAPuiPRDWorkshopAddinCmd", // 类名
        NULL);
}
```

### 3. 工具栏布局模式

```cpp
CATCmdContainer * CAAPuiPRDWorkshopAddin::CreateToolbars() {
    // 创建工具栏
    CATCmdContainer * pToolbar = NewAccess(CATCmdContainer, "PRDToolbar");
    
    // 设置子元素
    SetAccessChild(pToolbar, pCommand1);
    SetAccessNext(pCommand1, pCommand2);
    
    return pToolbar;
}
```

---

## 关键设计模式

| 模式 | CAA 实现 | 示例 |
|------|------|------|
| Workshop Addin | Implementation + TIE | CAAPuiPRDWorkshopAddin |
| 命令注册 | MacDeclareHeader | CAAPuiPRDWorkshopAddinCmd |
| 工具栏布局 | NewAccess + SetAccessChild | CreateToolbars() |
| 状态命令 | CATStateCommand | SaveToPDM 命令 |

---

## 对 AI agent 的要点

1. **PRD Workshop Addin 继承 CATBaseUnknown**，实现 CreateCommands() 和 CreateToolbars()

2. **工具栏布局使用链式结构**：SetAccessChild 设置父容器，SetAccessNext 连接兄弟元素

3. **命令通过 MacDeclareHeader 注册**：在 .cpp 顶部声明，构造函数中创建实例

4. **配置 Addin 用于管理产品配置**，如版本、状态等属性

5. **表示配置 Addin 用于管理产品外观**，如图标、显示模式等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIPRDWorkshopAddin.htm](../api-reference/interfaces/CATIPRDWorkshopAddin.htm)
- 完整方法签名: [api-reference/interfaces/CATIPrdConfigAddin.htm](../api-reference/interfaces/CATIPrdConfigAddin.htm)
- 完整方法签名: [api-reference/interfaces/CATCommandHeader.htm](../api-reference/interfaces/CATCommandHeader.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)
