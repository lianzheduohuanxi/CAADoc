---
module: "CAATopologicalObjects.edu"
category: "拓扑对象"
tier: "7"
status: "已完成"
---

# CAATopologicalObjects.edu — 拓扑对象

## 模块定位

CAATopologicalObjects 演示了 **CATIA 拓扑对象（Topological Objects）的 CAA 编程接口**。拓扑对象包括：
- 顶点、边、面、体
- 拓扑关系查询
- 拓扑修改

**依赖关系**：基于 CAAGeometricObjects。

---

## 核心接口

### CATIBrep — 边界表示接口

```cpp
class CATIBrep : public CATBaseUnknown {
    // 获取面
    virtual HRESULT GetFaces(CATLISTP(CATBaseUnknown) ** faces) = 0;
    
    // 获取边
    virtual HRESULT GetEdges(CATLISTP(CATBaseUnknown) ** edges) = 0;
    
    // 获取顶点
    virtual HRESULT GetVertices(CATLISTP(CATBaseUnknown) ** vertices) = 0;
    
    // 获取体
    virtual HRESULT GetBodies(CATLISTP(CATBaseUnknown) ** bodies) = 0;
}
```

### CATIFace / CATIEdge / CATIVertex — 拓扑元素

```cpp
// 面接口
class CATIFace : public CATBaseUnknown {
    virtual HRESULT GetSurface(CATISpecObject ** surface) = 0;
};

// 边接口
class CATIEdge : public CATBaseUnknown {
    virtual HRESULT GetCurve(CATISpecObject ** curve) = 0;
    virtual HRESULT GetVertices(CATIVertex ** v1, CATIVertex ** v2) = 0;
};

// 顶点接口
class CATIVertex : public CATBaseUnknown {
    virtual HRESULT GetPoint(CATMathPoint & point) = 0;
};
```

---

## 对 AI agent 的要点

1. **CATIBrep 提供拓扑访问**：面、边、顶点的遍历

2. **拓扑-几何映射**：CATIFace 对应 CATISpecSurface

3. **拓扑修改**：分割、合并、删除等操作

4. **与几何引擎集成**：底层几何操作

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIBrep.htm](../api-reference/interfaces/CATIBrep.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
