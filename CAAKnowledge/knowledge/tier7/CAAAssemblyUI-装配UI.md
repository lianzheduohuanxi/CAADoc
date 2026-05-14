---
module: "CAAAssemblyUI.edu"
category: "装配 UI"
tier: "7"
status: "已完成"
---

# CAAAssemblyUI.edu — 装配用户界面

## 模块定位

CAAAssemblyUI 演示了 **CATIA 装配模块用户界面的 CAA 编程接口**。装配 UI 包括：
- 装配工作台 Addin
- 约束命令
- 导航工具

**依赖关系**：基于 CAAProductStructureUI。

---

## 核心组件

### 装配 Addin

```cpp
class CAAAssemblyAddin : public CATBaseUnknown {
    void CreateCommands();
    CATCmdContainer * CreateToolbars();
}
```

### 约束命令

```cpp
class CAAAssemblyConstraintCmd : public CATStateCommand {
    void BuildGraph();
    CATBoolean CreateConstraint(void *);
}
```

---

## 对 AI agent 的要点

1. **装配 UI 使用 CATStateCommand**：引导用户添加约束

2. **约束类型**：接触、距离、角度等

3. **与其他模块集成**：与几何、体积产品协同

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIAssembling.htm](../api-reference/interfaces/CATIAssembling.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
