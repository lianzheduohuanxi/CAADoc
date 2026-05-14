---
module: "CAATessellation.edu"
category: "曲面细分"
tier: "7"
status: "已完成"
---

# CAATessellation.edu — 曲面细分

## 模块定位

CAATessellation 演示了 **CATIA 曲面细分（Tessellation）的 CAA 编程接口**。曲面细分用于：
- 多边形网格生成
- STL/VRML 导出
- 快速可视化

**依赖关系**：基础框架。

---

## 核心接口

### CATITessellation — 细分接口

```cpp
class CATITessellation : public CATBaseUnknown {
    // 生成网格
    virtual HRESULT Tessellate(double sag, double chord) = 0;
    
    // 获取三角形
    virtual HRESULT GetTriangles(CATLISTP(CATMathPoint) ** vertices, CATLISTP(int) ** indices) = 0;
    
    // 导出 STL
    virtual HRESULT ExportSTL(const CATUnicodeString & path) = 0;
}
```

---

## 对 AI agent 的要点

1. **CATITessellation 将 NURBS 曲面转换为多边形网格**：用于快速成型、3D 打印

2. **精度控制**：sag 和 chord 控制网格精度

3. **格式支持**：STL、VRML、OBJ 等

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATITessellation.htm](../api-reference/interfaces/CATITessellation.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
