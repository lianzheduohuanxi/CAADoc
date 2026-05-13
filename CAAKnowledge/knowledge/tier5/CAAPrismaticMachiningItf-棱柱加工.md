---
module: "CAAPrismaticMachiningItf.edu"
category: "棱柱加工接口"
tier: "5"
status: "已完成"
---

# CAAPrismaticMachiningItf.edu — 棱柱加工接口

## 模块定位

CAAPrismaticMachiningItf 演示了 **CATIA 棱柱加工（Prismatic Machining）模块的 CAA 编程接口**。棱柱加工主要用于：
- 2.5 轴铣削加工
- 轮廓铣削
- 钻孔加工
- 凹槽加工

**依赖关系**：基于 CAAManufacturingItf，继承制造环境的基本框架。

---

## 核心概念

### 棱柱加工的特点

| 特点 | 说明 |
|------|------|
| 轴向限制 | 刀具主要沿 Z 轴移动 |
| 几何形状 | 主要处理平面和垂直壁 |
| 应用场景 | 腔体、凹槽、钻孔 |

### 关键接口

```cpp
// 棱柱加工操作相关的接口
class CATIMfgPrismaticOperation {
    // 设置加工区域
    virtual HRESULT SetMachiningArea(CATISpecObject * area) = 0;
    
    // 设置刀具
    virtual HRESULT SetTool(CATIMfgTool * tool) = 0;
    
    // 设置进给率
    virtual HRESULT SetFeedrate(double rate) = 0;
}
```

---

## 对 AI agent 的要点

1. **棱柱加工是 CATIA 制造的基础模块**，几乎所有加工都从它开始

2. **主要操作类型**：
   - 轮廓铣削（Profile Contouring）
   - 腔体铣削（Pocket Milling）
   - 钻孔（Drilling）
   - 镗孔（Boring）

3. **刀具路径通常是 2.5 轴**：刀具只在 XY 平面运动，Z 轴作为切入深度

4. **与曲面加工的区别**：棱柱加工处理平面几何，曲面加工处理复杂曲面

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIMfgPrismaticOperation.htm](../api-reference/interfaces/CATIMfgPrismaticOperation.htm)
- 完整方法签名: [api-reference/interfaces/CATIMfgTool.htm](../api-reference/interfaces/CATIMfgTool.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
