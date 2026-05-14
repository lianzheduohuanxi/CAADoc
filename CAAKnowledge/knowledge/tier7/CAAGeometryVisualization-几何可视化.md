---
module: "CAAGeometryVisualization.edu"
category: "几何可视化"
tier: "7"
status: "已完成"
---

# CAAGeometryVisualization.edu — 几何可视化

## 模块定位

CAAGeometryVisualization 演示了 **CATIA 几何可视化（Geometry Visualization）的 CAA 编程接口**。几何可视化用于：
- 图形渲染
- 视图控制
- 可视化效果

**依赖关系**：基于 CAAVisualization。

---

## 核心接口

### CATIVisu — 可视化接口

```cpp
class CATIVisu : public CATBaseUnknown {
    // 设置渲染模式
    virtual HRESULT SetRenderMode(CATRenderMode mode) = 0;
    
    // 应用高亮
    virtual HRESULT Highlight(CATISpecObject * obj) = 0;
    
    // 截图
    virtual HRESULT CaptureView(CATUnicodeString & path) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATIVisu 控制几何显示**：渲染模式、高亮等

2. **视图操作**：缩放、旋转、平移

3. **图像导出**：生成视图截图

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIVisu.htm](../api-reference/interfaces/CATIVisu.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
