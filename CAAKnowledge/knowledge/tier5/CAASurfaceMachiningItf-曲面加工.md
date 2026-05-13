---
module: "CAASurfaceMachiningItf.edu"
category: "曲面加工接口"
tier: "5"
status: "已完成"
---

# CAASurfaceMachiningItf.edu — 曲面加工接口

## 模块定位

CAASurfaceMachiningItf 演示了 **CATIA 曲面加工（Surface Machining）模块的 CAA 编程接口**。曲面加工主要用于：
- 3 轴联动铣削
- 多轴加工
- 螺旋铣削
- 清根加工

**依赖关系**：基于 CAAManufacturingItf 和 CAAGSMInterfaces（曲面几何）。

---

## 核心概念

### 曲面加工 vs 棱柱加工

| 特点 | 棱柱加工 | 曲面加工 |
|------|----------|----------|
| 轴数 | 2.5 轴 | 3 轴及以上 |
| 几何 | 平面 | 曲面 |
| 刀具 | 端铣刀 | 球头铣刀 |
| 应用 | 腔体、凹槽 | 模具、叶轮 |

### 关键接口

```cpp
// 曲面加工操作相关的接口
class CATIMfgSurfaceOperation {
    // 设置驱动曲面
    virtual HRESULT SetDriveSurface(CATISpecObject * surface) = 0;
    
    // 设置检查曲面
    virtual HRESULT SetCheckSurface(CATISpecObject * surface) = 0;
    
    // 设置刀具轴向
    virtual HRESULT SetToolAxis(CATMathDirection * axis) = 0;
    
    // 设置刀轴控制
    virtual HRESULT SetAxisControl(CATIMfgAxisControl * ctrl) = 0;
}
```

---

## 对 AI agent 的要点

1. **曲面加工需要 3 轴或更多轴联动**：刀具路径更复杂

2. **关键参数**：
   - 驱动曲面（Drive Surface）
   - 检查曲面（Check Surface）
   - 刀具轴向（Tool Axis）
   - 残余高度（Scallop Height）/ 行距（Stepover）

3. **多轴加工**：5 轴联动可以实现更复杂的加工策略

4. **与几何操作的关联**：使用 CATIGSMCurve、CATIGSMSurface 等接口

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIMfgSurfaceOperation.htm](../api-reference/interfaces/CATIMfgSurfaceOperation.htm)
- 完整方法签名: [api-reference/interfaces/CATIGSMSurface.htm](../api-reference/interfaces/CATIGSMSurface.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
