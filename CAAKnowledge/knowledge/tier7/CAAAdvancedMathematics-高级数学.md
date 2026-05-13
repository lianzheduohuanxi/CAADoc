# CAAAdvancedMathematics — 高级数学函数扩展

**模块**: CAAAdvancedMathematics.edu | **层级**: Tier 7 | **规模**: 9 个文件（4 个头文件 + 4 个 .cpp + 1 个 XML）

---

## 模块定位

CAAAdvancedMathematics 演示如何在 CATIA CGM（CAT Geometric Modeler）数学框架中**自定义数学函数类型**，使其能够被几何算子（如曲面求值、求交等）使用。包含两个核心示例：
1. **蛋盒曲面二元函数** — 自定义 CATMathFunctionXY 子类
2. **有理分式一元函数** — 自定义 CATMathFunctionX 子类（含深拷贝）

---

## 架构概览

```
CAAAdvancedMathematics.edu/
├── IdentityCard/
│   └── IdentityCard.xml        依赖: Mathematics, AdvancedMathematics, System
├── PublicInterfaces/
│   ├── CAAAmtForeignFct.h      DLL 导出宏（支持 CGM 和 Windows 双平台）
│   └── CAAAmtForeignFctXY.h    蛋盒曲面函数类声明（继承 CATMathFunctionXY）
├── ProtectedInterfaces/
│   ├── CAAMyFraction.h         导出宏
│   └── CAAMyFract.h            有理分式类声明（继承 CATMathFunctionX）
├── CAAAmtFct.m/src/
│   ├── CAAAmtFctMain.cpp       蛋盒函数测试（批处理）
│   └── CAAAmtForeignFctXY.cpp  蛋盒函数实现
└── CAAMyFraction.m/src/
    ├── CAAAmtFraction.cpp      分式函数测试（批处理）
    └── CAAMyFract.cpp          分式函数实现
```

---

## 核心类详解

### 1. CAAAmtForeignFctXY — 蛋盒曲面二元函数

**继承**: `CATMathFunctionXY`（数学框架的二元函数基类）

**数学定义**:
```
F: R² → R
F(u, v) = a·u + b·v + c·cos(u)·cos(v) + Origin
```

**构造函数**:
```cpp
CAAAmtForeignFctXY(const double iA, const double iB,
                   const double iC, const double iOrigin);
```

**支持的求值选项**:
- `OptionEval` — 函数值
- `OptionEvalFirstDeriv` — 一阶偏导（∂F/∂u, ∂F/∂v）
- `OptionEvalSecondDeriv` — 二阶偏导（∂²F/∂u², ∂²F/∂u∂v, ∂²F/∂v²）

**偏导数公式**:
```
∂F/∂u    = a - c·sin(u)·cos(v)
∂F/∂v    = b - c·cos(u)·sin(v)
∂²F/∂u²  = -c·cos(u)·cos(v)
∂²F/∂u∂v = c·sin(u)·sin(v)
∂²F/∂v²  = -c·cos(u)·cos(v)
```

**三种求值模式**:

| 方法 | 用途 |
|------|------|
| `Eval(u,v)` | 单点函数值 |
| `EvalFirstDerivX/Y(u,v)` | 单点一阶偏导 |
| `EvalSecondDerivX2/XY/Y2(u,v)` | 单点二阶偏导 |
| `Eval(u,v, options, &f, &fx, &fy, &fx2, &fxy, &fy2)` | 单点多值同时求值 |
| `Eval(domain, nbPoints, options, f[], fx[], fy[], ...)` | 规则网格批量求值 |

**性能优化** — 多点网格求值使用三角函数递推公式:

```cpp
// cos(v+delta) = cos(v)·cos(delta) - sin(v)·sin(delta)
// sin(v+delta) = cos(v)·sin(delta) + sin(v)·cos(delta)

// 预计算 v 方向的 sin/cos 表
for (j = 1; j < nv; j++) {
    aCosTab[j] = aCosTab[j-1] * dcos - aSinTab[j-1] * dsin;
    aSinTab[j] = aCosTab[j-1] * dsin + aSinTab[j-1] * dcos;
}
```

单点同时求值时，sin/cos 只计算一次并缓冲复用:
```cpp
double cosu = cos(iX), cosv = cos(iY);
if (iOptions & OptionEval) {
    *f = a*iX + b*iY + c*cosu*cosv + Origin;
    if (iOptions == OptionEval) return; // 跳过 sin 计算
}
double sinu = sin(iX), sinv = sin(iY); // 仅当需要导数时才计算
```

**运行时类型识别**:
```cpp
CATMathClassId IsA() const { return "CAAAmtForeignFctXY"; }
CATBoolean IsAKindOf(const CATMathClassId iClassId) const {
    if (strcmp(iClassId, "CAAAmtForeignFctXY") == 0) return TRUE;
    return CATMathFunctionXY::IsAKindOf(iClassId);
}
```

---

### 2. CAAMyFract — 有理分式一元函数

**继承**: `CATMathFunctionX`（数学框架的一元函数基类）

**数学定义**: `F(x) = P(x) / Q(x)`（分子和分母都是 CATMathFunctionX）

**构造函数**:
```cpp
CAAMyFract(const CATMathFunctionX *P, const CATMathFunctionX *Q);
```

**关键方法**:

| 方法 | 功能 |
|------|------|
| `Eval(t)` | 求值: `P(t)/Q(t)`，分母为 0 返回 CATMathInfinite |
| `Duplicate()` | 浅拷贝（直接拷贝 P/Q 指针） |
| `DeepDuplicate()` | 深拷贝（递归拷贝 P 和 Q） |
| `GetNumerator()` | 获取分子函数 |
| `GetDenominator()` | 获取分母函数 |

**深拷贝实现**（关键设计）:
```cpp
CATMathFunctionX * DeepDuplicate() const {
    CATMathFunctionX *P = _P->Duplicate();  // 递归拷贝分子
    CATMathFunctionX *Q = _Q->Duplicate();  // 递归拷贝分母
    return new CAAMyFract(P, Q);
}
```

> 深拷贝 vs 浅拷贝的区别：浅拷贝只拷贝指针（`new CAAMyFract(*this)`），删除原对象后拷贝失效；深拷贝递归复制操作数，删除原对象后拷贝仍然可用。

---

## 测试程序

### CAAAmtFctMain — 蛋盒函数测试

**返回码**:
| 码 | 含义 |
|----|------|
| 0 | OK |
| 1 | IsAKindOf("CAAAmtForeignFctXY") 失败 |
| 2 | IsAKindOf("CATMathFunctionXY") 失败 |
| 3 | Eval(0,0) != c + Origin |
| 4 | 一阶/二阶偏导数值不正确 |
| 5 | 同时求值结果不正确 |
| 6 | 网格求值结果不正确 |

**测试覆盖**:
- 类型检查（IsA/IsAKindOf）
- 单点求值（Eval）
- 一阶偏导（EvalFirstDerivX/Y）
- 二阶偏导（EvalSecondDerivX2/XY/Y2）
- 单点多值同时求值（Eval with OptionEvalSecondDeriv）
- 规则网格批量求值（10×20 网格，验证特定点值精度 ≤ 1e-12）

### CAAAmtFraction — 分式函数测试

**流程**:
1. 创建分子 `F(x) = 1 + 2x`（CATMathPolynomX，degree 1）
2. 创建分母 `G(x) = 2 + 1.5x`
3. 构造 `CAAMyFract(F, G)`
4. 测试 Eval(0.0), Eval(1.0), Eval(2.0)
5. 深拷贝 → 删除原操作数 → 验证拷贝仍能求值（证明深拷贝正确）
6. 清理

---

## 关键设计模式

### 1. 模板方法模式
CATMathFunctionXY 定义求值框架（IsOption 检查能力），子类只需实现具体的 Eval 方法。

### 2. 原型模式（Duplicate/DeepDuplicate）
支持函数的拷贝语义，DeepDuplicate 确保拷贝后的对象独立于原对象。

### 3. 策略模式
自定义函数作为策略注入几何算子，算子通过基类接口调用而不关心具体实现。

---

## 依赖关系

```
Mathematics → AdvancedMathematics → System
```

---

## 总结

CAAAdvancedMathematics 展示了 CGM 数学框架的扩展机制。通过继承 CATMathFunctionXY/CATMathFunctionX 并实现求值方法，可以将任意数学函数注入 CATIA 的几何管线（如 ForeignSurface、求交算子等）。关键要点：
1. 正确实现 IsA/IsAKindOf 以支持运行时类型识别
2. 实现 IsOption 声明支持的求值能力
3. 多点求值时利用递推公式优化性能
4. 深拷贝确保函数对象可独立复制