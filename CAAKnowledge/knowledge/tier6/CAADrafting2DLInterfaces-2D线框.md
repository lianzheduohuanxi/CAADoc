---
module: "CAADrafting2DLInterfaces.edu"
category: "2D 线框接口"
tier: "6"
status: "已完成"
---

# CAADrafting2DLInterfaces.edu — 2D 线框接口

## 模块定位

CAADrafting2DLInterfaces 演示了 **CATIA 2D 线框（2D Layout）模块的 CAA 编程接口**。2D 线框用于：
- 创建 2D 线框几何
- 定义投影关系
- 管理 2D/3D 关联

**依赖关系**：基于 CAADraftingInterfaces。

---

## 核心接口

### 2D 线框操作

```cpp
// 2D 线框相关的接口
class CATI2DLayout {
    // 创建 2D 线框
    virtual HRESULT CreateLayout() = 0;
    
    // 添加几何元素
    virtual HRESULT AddElement(CATISpecObject * elem) = 0;
    
    // 设置投影
    virtual HRESULT SetProjection(CATISpecObject * proj) = 0;
}
```

---

## 对 AI agent 的要点

1. **2D 线框是工程图的基础**：先创建 2D 线框，再生成视图

2. **投影关系维护 2D/3D 关联**：修改 3D 模型，2D 线框自动更新

3. **CATI2DLayout 接口是核心**：管理 2D 线框的创建和修改

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATI2DLayout.htm](../api-reference/interfaces/CATI2DLayout.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
