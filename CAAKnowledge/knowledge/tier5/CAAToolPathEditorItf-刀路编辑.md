---
module: "CAAToolPathEditorItf.edu"
category: "刀路编辑接口"
tier: "5"
status: "已完成"
---

# CAAToolPathEditorItf.edu — 刀路编辑接口

## 模块定位

CAAToolPathEditorItf 演示了 **CATIA 刀路编辑（Tool Path Editor）模块的 CAA 编程接口**。刀路编辑主要用于：
- 编辑和优化刀具路径
- 调整进给率和转速
- 添加自定义刀具路径操作
- 后处理优化

**依赖关系**：基于 CAAManufacturingItf。

---

## 核心概念

### 刀路编辑功能

| 功能 | 说明 |
|------|------|
| 路径裁剪 | 删除不需要的刀路段 |
| 路径连接 | 连接断开的刀路 |
| 进给率调整 | 修改切削参数 |
| 刀轨优化 | 优化空切和提刀 |

### 关键接口

```cpp
// 刀路编辑器相关的接口
class CATIMfgToolPathEditor {
    // 获取刀路
    virtual HRESULT GetToolPath(CATIMfgToolPath ** tp) = 0;
    
    // 编辑刀路段
    virtual HRESULT EditSegment(int index, CATISpecObject * newSeg) = 0;
    
    // 删除刀路段
    virtual HRESULT DeleteSegment(int index) = 0;
    
    // 添加刀路段
    virtual HRESULT AddSegment(CATISpecObject * seg, int position) = 0;
}

// 刀路段接口
class CATIMfgToolPathSegment {
    // 获取类型（快速、切削、提刀等）
    virtual CATBSTR GetSegmentType() = 0;
    
    // 获取几何
    virtual HRESULT GetGeometry(CATISpecObject ** geom) = 0;
    
    // 获取参数
    virtual HRESULT GetParameters(CATIMfgParameters ** params) = 0;
}
```

---

## 对 AI agent 的要点

1. **刀路由多个段（Segment）组成**：每个段有类型（快速、切削、提刀等）

2. **刀路段的几何通常是 CATIGSMCurve**：曲线、曲面边界等

3. **参数包括**：
   - 进给率（Feedrate）
   - 主轴转速（Spindle Speed）
   - 冷却液状态
   - 刀具补偿

4. **后处理输入**：编辑后的刀路送往后处理器生成 G 代码

5. **自定义刀路操作**：可以实现特定加工策略

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIMfgToolPathEditor.htm](../api-reference/interfaces/CATIMfgToolPathEditor.htm)
- 完整方法签名: [api-reference/interfaces/CATIMfgToolPath.htm](../api-reference/interfaces/CATIMfgToolPath.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
