---
module: "CAAObjectSpecsModeler.edu"
category: "CAA 规格化建模 — Feature / Extension / Build-Update / CCP"
tier: "1"
status: "已完成"
---

# CAAObjectSpecsModeler.edu — 规格化建模

## 模块定位

CAAObjectSpecsModeler 展示了 CAA 的**规格化特征建模（Object Specs Modeler, OSM）**框架，这是 CATIA 零件设计模块的核心基础设施。它通过一个完整的"小说/图书馆/出版社"领域模型，演示了：

- **特征（Feature）** 的完整生命周期：Catalog 定义 → StartUp 实例化 → 属性赋值 → 派生特征
- **扩展（Extension）** 机制：在不修改基础特征定义的情况下，动态添加数据和行为
- **Build/Update** 自动计算：通过实现 CATIBuild 接口，实现属性的自动派生计算
- **CCP（Cut/Copy/Paste）** 操作：批处理和交互模式下的对象复制粘贴

这个模块是理解 CATIA 特征建模架构的最完整案例，7 个 Use Case 覆盖了特征建模的全部核心模式。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────────┐
│                         CATSession                                  │
│                              │                                       │
│                     CATDocument (CATPart)                            │
│                              │                                       │
│              ┌───────────────┼───────────────┐                       │
│              │               │               │                       │
│      Root Container   CAAOsmApp1      CAAOsmApp2                     │
│     (CATFeatCont)    (CATFeatCont)   (CATFeatCont)                   │
│           │               │               │                          │
│     ┌─────┴──────┐  ┌────┴─────┐   ┌─────┴──────┐                   │
│   Novel1  Dict1  Add1│HistNovel│  ChildrensNovel│                    │
│     │        │       │BiogNovel│                │                    │
│  Chapter1  Chapter2  │         │                │                    │
│  Chapter3            │         │                │                    │
│                      │         │                │                    │
│   聚合特征 (Aggregated)  扩展特征 (Extensions)                         │
│   ─ 有 Father          ─ 通过 QueryExtension 访问                    │
│   ─ 父删则子删         ─ 按 ApplicativeContainer 管理                │
│   ─ 独占归属           ─ 通过 CAAIBiogNovel 自定义接口访问            │
│                                                                       │
│   Publisher1 ─────────→ 被 Novel1、Novel2、Dict1 引用                │
│   引用特征 (Referenced)                                               │
│   ─ 无 Father (GetFather() == NULL)                                  │
│   ─ 可被多个特征共享                                                  │
│   ─ 引用方删除不影响被引用对象                                         │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. Catalog 体系 — 特征的注册与发现

OSM 使用两级文件定义特征模型：

**CATSpecs（特征规格定义）** — XML 格式，定义 StartUp 类型和继承关系：

```xml
<!-- CAAOsmCatalogSU.CATSpecs -->
<CATSpecs>
  <StartUp Type="CAAOsmAdd" Derivable="TRUE"/>
  <StartUp Type="CAAOsmSquare" Derivable="FALSE"/>
</CATSpecs>
```

- `Derivable="TRUE"` 允许从该 StartUp 派生子类型
- `Derivable="FALSE"` 该类型不可派生

**CATfct（编译后的特征目录）** — 二进制格式，CATSpecs 编译后的运行时文件。包含了 StartUp 列表和属性定义。从 CATfct 二进制内容中可提取出完整的特征树：

```
CAAOsmCatalogSU.CATfct 包含 10 个 StartUp:
├── CAAOsmPublisher         PublisherName(string), PublisherAddress(string)
├── CAAOsmChapter           ChapterTitle(string), FirstPage(int), LastPage(int)
├── CAAOsmBook              Title(string), BookPublisher(specobject→CAAOsmPublisher)
├── CAAOsmNovel (extends Book)  Title, BookPublisher, Author(string), NovelChapter(list→Chapter)
├── CAAOsmDictionary (extends Book)  Title, BookPublisher, Language(string)
├── CAAOsmBarCode
├── CAAOsmAdd               First(int), Second(int), Sum(int)
├── CAAOsmSquare            Num(int), Square(int)
├── CAAOsmPublicLibrary
└── CAAOsmValue
```

**扩展目录** — 使用同样的 CATfct 格式，但定义的是扩展而非基础特征：
```
CAAOsmExt1Catalog.CATfct:
├── CAAOsmHistoricalNovel    Epoch(string: "Middle Ages")
└── CAAOsmBiographicalNovel  Domain(string: "Music"), Epoch(string)

CAAOsmExt2Catalog.CATfct:
└── CAAOsmChildrensNovel     AgeGroup(string)
```

---

### 2. StartUp Handler 模式 — 特征的检索与实例化

这是 OSM 的核心使用模式，贯穿所有 7 个 Use Case：

```cpp
// 步骤 1：打开 Catalog，获取 StartUp 的 Handler
CATUnicodeString CatalogName = "CAAOsmCatalogSU.CATfct";
CATUnicodeString clientId("CAAOsmClientId");
CATUnicodeString novelSUType("CAAOsmNovel");

CATOsmSUHandler novelSUHandler(novelSUType, clientId, CatalogName);
// CATOsmSUHandler(StartUp类型名, 客户端ID, 目录文件名)

// 步骤 2：检索 StartUp 模板
CATISpecObject_var spNovelSU = NULL_var;
rc = novelSUHandler.RetrieveSU(spNovelSU);
// spNovelSU 现在是 CAAOsmNovel 的模板对象

// 步骤 3：在容器中实例化
CATISpecObject_var spNovelInst1 = NULL_var;
rc = novelSUHandler.Instanciate(spNovelInst1, piRootContainer, "CAAOsmNovel1");
// 或使用 CATISpecObject 的 Instanciate 从已有特征派生：
CATISpecObject_var spNovelInst2 = spNovelInst1->Instanciate("CAAOsmNovel2", piRootContainer);
```

**关键区别**：
- `CATOsmSUHandler::Instanciate(su, container, name)` — 从 StartUp 模板实例化
- `CATISpecObject::Instanciate(name, container)` — 从已有特征派生（继承所有属性和值）

---

### 3. 属性访问模式 — CATISpecAttrAccess / CATISpecAttrKey

所有特征属性的读写通过两阶段完成：

```cpp
// 阶段 1：获取属性访问器
CATISpecAttrAccess *piAccess = NULL;
spFeature->QueryInterface(IID_CATISpecAttrAccess, (void**)&piAccess);

// 阶段 2：获取属性键（Key），然后用键读写值
CATISpecAttrKey *piKey = piAccess->GetAttrKey("Title");
piAccess->SetString(piKey, "The Three Musketeers");
piAccess->GetString(piKey);           // 读取字符串值
piAccess->SetInteger(piKey, 1);       // 整数读写
piAccess->GetInteger(piKey);

piKey->Release();
piAccess->Release();
```

**属性键的作用域**：
- 从 StartUp 获取的 Key 是**全局的**，可在同一 StartUp 的所有实例间复用
- 从实例获取的 Key 是**局部的**，仅对该实例有效
- 通过 `AddAttribute` 添加的属性，其 Key 必须从该实例重新获取

**支持的属性类型**：

| 类型 | Set/Get 方法 | 示例 |
|------|-------------|------|
| `tk_string` | `SetString` / `GetString` | "The Three Musketeers" |
| `tk_integer` | `SetInteger` / `GetInteger` | 1, 11, 27 |
| `tk_specobject` | `SetSpecObject` / `GetSpecObject` | 引用 Publisher1 |
| `tk_list(tk_specobject)` | `SetSpecObject` 多次 / `GetSpecObject(i)` / `GetListSize` | Chapter 列表 |

---

### 4. 特征之间的三种关系模式

**4.1 聚合特征（Aggregated Feature）**

```cpp
// NovelChapter 是一个 tk_list(tk_specobject) 属性
piSpecAttrAccessOnNov1->SetSpecObject(piKeyNovelChapter, spChapterInst1);
piSpecAttrAccessOnNov1->SetSpecObject(piKeyNovelChapter, spChapterInst2);
piSpecAttrAccessOnNov1->SetSpecObject(piKeyNovelChapter, spChapterInst3);

// 遍历列表
int size = piSpecAttrAccessOnNov1->GetListSize(piKeyNovelChapter);
for (int i = 1; i <= size; i++) {
    CATISpecObject *piChapter = piSpecAttrAccessOnNov1->GetSpecObject(piKeyNovelChapter, i);
    // 对每个 chapter 执行操作...
    piChapter->Release();
}
```

聚合特征的特性：
- **有 Father**：`GetFather()` 返回父特征（如 Novel1）
- **独占归属**：一个聚合特征只能属于一个父特征
- **级联删除**：父特征被删除时，聚合子特征也被删除
- **列表索引从 1 开始**（非 0-based）

**4.2 引用特征（Referenced Feature）**

```cpp
// 同一个 Publisher1 可以被多个特征引用
piSpecAttrAccessOnNov1->SetSpecObject(piKeyNovelPublisher, spPublisherInst1);
piSpecAttrAccessOnNov2->SetSpecObject(piKeyNovelPublisher, spPublisherInst1);
piSpecAttrAccessOnDict1->SetSpecObject(piKeyDictPublisher, spPubInst2);

// 验证：引用特征没有 Father
CATISpecObject *father = spPubInst2->GetFather();
if (NULL == father) {
    // 正确：引用特征没有 Father
}
```

引用特征的特性：
- **无 Father**：`GetFather()` 返回 NULL
- **可共享**：同一个被引用特征可被多个特征引用
- **独立生命周期**：删除引用方不影响被引用对象
  ```cpp
  LifeCycleObject *pDict = NULL;
  spDictionaryInst->QueryInterface(IID_LifeCycleObject, (void**)&pDict);
  pDict->remove();  // 删除 Dictionary1，但 Publisher2 仍然存在
  // 可以继续将 Publisher2 赋值给 Dictionary2
  ```

**4.3 扩展特征（Extension Feature）**

参见下文第 6 节。

---

### 5. 动态属性添加 — AddAttribute

StartUp 模板定义了初始属性集合，但运行时可以为实例添加新属性：

```cpp
// 为 Novel1 添加 Volume 属性（整数类型）
CATISpecAttribute *piVolume = spNovelInst->AddAttribute(
    CATUnicodeString("Volume"), tk_integer);
piVolume->Release();

// 注意：AddAttribute 返回的 CATISpecAttribute* 必须 Release

// 从该实例重新获取 Volume 的 Key（不能复用 StartUp 的 Key）
CATISpecAttrKey *piKeyVolume = piSpecAttrAccess->GetAttrKey("Volume");
piSpecAttrAccess->SetInteger(piKeyVolume, 1);

// 派生实例会继承动态添加的属性及其值
CATISpecObject_var spNovelInst2 = spNovelInst1->Instanciate("CAAOsmNovel2", piRootContainer);
// Novel2 也有 Volume 属性，但需要从 Novel2 重新获取 Key
```

---

### 6. 扩展机制 — Extension 的完整生命周期

扩展机制是 OSM 最强大的特性，允许在不修改基础特征定义的情况下增强特征的数据和行为。

**6.1 自定义接口定义（CAAIBiogNovel）**

```cpp
// PrivateInterfaces/CAAIBiogNovel.h
class CAAIBiogNovel : public CATBaseUnknown {
    CATDeclareInterface;
public:
    virtual HRESULT GetEpoch(CATUnicodeString *opEpoch) = 0;
    virtual HRESULT SetEpoch(const CATUnicodeString iEpoch) = 0;
    virtual HRESULT GetDomain(CATUnicodeString *opDomain) = 0;
    virtual HRESULT SetDomain(const CATUnicodeString iDomain) = 0;
};
```

- 使用 `CATDeclareInterface` 声明为 CAA 接口
- 通过 `CATImplementInterface(CAAIBiogNovel, CATBaseUnknown)` 注册
- IID 在 `.iid` 文件中定义：`{c36df0e2-d28e-11d4-9f14-00d0b7511dfd}`

**6.2 扩展实现类（CAAEOsmBiogNovel）**

```cpp
// LocalInterfaces/CAAEOsmBiogNovel.h
class CAAEOsmBiogNovel : public CATBaseUnknown {
    CATDeclareClass;
public:
    HRESULT GetEpoch(CATUnicodeString *opEpoch);
    HRESULT SetEpoch(const CATUnicodeString iEpoch);
    HRESULT GetDomain(CATUnicodeString *opDomain);
    HRESULT SetDomain(const CATUnicodeString iDomain);
};
```

实现中，每个方法遵循统一的属性访问模式：
```cpp
// CAAEOsmBiogNovel.cpp - GetEpoch 的实现
HRESULT CAAEOsmBiogNovel::GetEpoch(CATUnicodeString *pEpoch) {
    // 1. 通过 QueryInterface 获取属性访问器
    CATISpecAttrAccess *piAccess = NULL;
    this->QueryInterface(IID_CATISpecAttrAccess, (void**)&piAccess);

    // 2. 获取属性键
    CATISpecAttrKey *piKey = piAccess->GetAttrKey("Epoch");

    // 3. 读取属性值
    *pEpoch = piAccess->GetString(piKey);

    piAccess->Release();
    piKey->Release();
    return S_OK;
}
```

**6.3 TIE 绑定和字典注册**

```cpp
// CAAEOsmBiogNovel.cpp
#include "TIE_CAAIBiogNovel.h"
TIE_CAAIBiogNovel(CAAEOsmBiogNovel);  // 绑定：CAAEOsmBiogNovel 实现了 CAAIBiogNovel

CATImplementClass(CAAEOsmBiogNovel,    // 实现类
                  DataExtension,       // 扩展类型
                  CATBaseUnknown,      // 基类
                  CAAOsmBiographicalNovel);  // 对应的 late type
```

字典文件绑定：
```
# CAAObjectSpecsModeler.edu.dico
CAAOsmBiographicalNovel    CAAIBiogNovel    libCAAOsmManageExtensions
CAAOsmAdd                  CATIBuild        CAAOsmBuildUpdate
CAAOsmSquare               CATIBuild        CAAOsmBuildUpdate
```

字典条目含义：`LateType → Interface → 所在共享库`

**6.4 扩展的添加、查询和移除**

```cpp
// 获取扩展管理接口
CATIOsmExtendable *piExtendable = NULL;
spNovelInst1->QueryInterface(IID_CATIOsmExtendable, (void**)&piExtendable);

// 添加扩展（语法：`扩展名`#序号@`目录名.CATfct`）
const char *extName = "`CAAOsmBiographicalNovel`#3@`CAAOsmExt1Catalog.CATfct`";
piExtendable->AddExtension(extName);

// 查询扩展 — 获取自定义接口
CAAIBiogNovel *piBiogNovel = NULL;
piExtendable->QueryExtension(extName, IID_CAAIBiogNovel, (void**)&piBiogNovel);

// 使用自定义接口
CATUnicodeString epoch;
piBiogNovel->GetEpoch(&epoch);    // 读取 Epoch 属性
piBiogNovel->SetEpoch("Renaissance");  // 修改 Epoch 属性

// 查询所有扩展
CATListPtrCATBaseUnknown *paExtList = NULL;
piExtendable->QueryAllExtensions(IID_CATISpecObject, &paExtList);
for (int jj = 1; jj <= paExtList->Size(); jj++) {
    CATBaseUnknown *pInt = (*paExtList)[jj];
    CATIOsmExtension *piExt = NULL;
    pInt->QueryInterface(IID_CATIOsmExtension, (void**)&piExt);
    char *pExtId = NULL;
    piExt->GetID(pExtId);  // 获取扩展的 ID 名称
    free(pExtId);
    piExt->Release();
    pInt->Release();
}
delete paExtList;

// 按应用容器移除扩展
piExtendable->RemoveApplicativeExtensions("CAAOsmApplication1");
```

**扩展管理的核心概念**：
- 扩展按 **ApplicativeContainer** 分组管理
- 一个特征可以从多个 ApplicativeContainer 添加扩展
- 移除某个容器的扩展不影响其他容器的扩展
- `QueryAllExtensions` 返回当前所有活跃扩展

---

### 7. Applicative Container — 应用容器管理

Applicative Container 是特征的分组/命名空间机制：

```cpp
// 创建应用容器
CATIdent idAppliCont = "CATFeatCont";              // 容器类型
CATUnicodeString appliContId("CAAOsmApplication1"); // 容器标识名
CATBaseUnknown *pAppliCont = NULL;
CATCreateApplicativeContainer(&pAppliCont, pDoc,
    idAppliCont, IID_CATIContainer, "", appliContId);

// 在容器中实例化特征
CATOsmSUHandler handler(novelSUType, clientId, CatalogName);
handler.Instanciate(spNovelInst, piAppliCont, "Novel1");

// 保存文档后重新打开，按名称检索容器
CATDocumentServices::OpenDocument(fileName, pDoc);
CATGetApplicativeContainer(&pAppliCont, pDoc,
    IID_CATIContainer, appliContId);

// 列出容器中的所有成员
CATIClientContainer *piClient = NULL;
pAppliCont->QueryInterface(IID_CATIClientContainer, (void**)&piClient);
CATListPtrCATBaseUnknown *pMemberList = new CATListPtrCATBaseUnknown();
piClient->ListMembers(IID_CATISpecObject, clientId, &pMemberList);
// pMemberList->Size() 返回成员数量
delete pMemberList;
```

---

### 8. Build/Update 机制 — 属性的自动计算

当特征的某些属性依赖于其他属性时，可以实现 CATIBuild 接口来自动计算派生值：

**8.1 CATIBuild 实现**

```cpp
// CAAOsmAddOp.h
class CAAOsmAddOp : public CATBaseUnknown {
    CATDeclareClass;
public:
    HRESULT Build();  // CATIBuild 接口的唯一方法
};

// CAAOsmAddOp.cpp
TIE_CATIBuild(CAAOsmAddOp);
CATImplementClass(CAAOsmAddOp, DataExtension, CATBaseUnknown, CAAOsmAdd);

HRESULT CAAOsmAddOp::Build() {
    // 获取属性访问器
    CATISpecAttrAccess *piAccess = NULL;
    this->QueryInterface(IID_CATISpecAttrAccess, (void**)&piAccess);

    // 获取输入属性的键
    CATISpecAttrKey *piKeyFirst = piAccess->GetAttrKey("First");
    CATISpecAttrKey *piKeySecond = piAccess->GetAttrKey("Second");
    CATISpecAttrKey *piKeySum = piAccess->GetAttrKey("Sum");

    // 读取输入，计算输出
    int f = piAccess->GetInteger(piKeyFirst);
    int s = piAccess->GetInteger(piKeySecond);
    piAccess->SetInteger(piKeySum, f + s);  // Sum = First + Second

    // 释放所有指针
    piAccess->Release();
    piKeyFirst->Release();
    piKeySecond->Release();
    piKeySum->Release();
    return 0;
}
```

**8.2 使用 Build/Update**

```cpp
// 1. 设置输入属性
piSpecAttrAccess->SetInteger(piKeyFirst, 1);
piSpecAttrAccess->SetInteger(piKeySecond, 2);

// 2. 触发 Update — 自动调用 CATIBuild::Build()
spAddOpInst1->Update();  // Sum 自动计算为 3

// 3. 修改输入后再次 Update
piSpecAttrAccess->SetInteger(piKeyFirst, 2);
spAddOpInst1->Update();  // Sum 自动更新为 4
```

**8.3 属性间的跨特征引用**

```cpp
// 将 CAAOsmAdd.Sum 的值赋值给 CAAOsmSquare.Num
piSpecAttrAccessOnSq1->SetSpecAttribute(piKeyNum, spAddOpInst1, piKeySum);
// SetSpecAttribute(目标键, 源特征, 源键)

// 此时修改 Add.First → Update Add → Sum 变化 → Update Square → Square 自动重算
spAddOpInst1->Update();
spSqInst1->Update();
// Square = (First + Second)²
```

**Build/Update 关键规则**：
- `Update()` 触发 `CATIBuild::Build()` 回调
- Build 负责读取当前属性值并计算派生属性
- 当特征间有 `SetSpecAttribute` 引用时，必须先 Update 源特征再 Update 目标特征
- 字典中注册：`CAAOsmAdd → CATIBuild → CAAOsmBuildUpdate`

---

### 9. CCP（Cut/Copy/Paste）操作

OSM 支持两种 CCP 模式：

**9.1 批处理模式（直接操作）**

```cpp
// 获取目标容器的 CutAndPastable 接口
CATICutAndPastable *piCCP = NULL;
pTargetContainer->QueryInterface(IID_CATICutAndPastable, (void**)&piCCP);

// 创建待粘贴对象列表
ListOfVarBaseUnknown listToPaste;
listToPaste.Append(spChapterInst1);
listToPaste.Append(spChapterInst2);

// 直接 Paste
ListOfVarBaseUnknown listPasted = piCCP->Paste(listToPaste, NULL, NULL);

// 直接 Remove（Cut）
ListOfVarBaseUnknown listToRemove;
listToRemove.Append(spChapterInst1);
piCCPOnSource->Remove(listToRemove, NULL);
```

**9.2 交互模式（通过剪贴板）**

```cpp
// 需要先初始化格式系统
IdFormat FEATURE_FORMAT = "CATFeatCont";
SpecBindNativeFormat(FEATURE_FORMAT);

// 步骤 1：BoundaryExtract — 从源容器提取对象
ListOfVarBaseUnknown newListToCopy;
ListOfVarBaseUnknown listFromCopy;
listFromCopy.Append(spChapterInst3);
piCCP->BoundaryExtract(newListToCopy, &listFromCopy, NULL);

// 步骤 2：Extract — 将对象存入剪贴板容器
VarBaseUnknown pExtractedList = piCCP->Extract(newListToCopy, NULL);

// 步骤 3：从剪贴板取出对象
CATICutAndPastable *piClipboard = NULL;
pExtractedList->QueryInterface(IID_CATICutAndPastable, (void**)&piClipboard);

ListOfVarBaseUnknown extractedListToCopy;
piClipboard->BoundaryExtract(extractedListToCopy, NULL, NULL);

// 步骤 4：Paste 到目标容器
ListOfVarBaseUnknown result = piTargetCCP->Paste(extractedListToCopy, NULL, NULL);
```

**CCP 注意事项**：
- 操作前需 `CATLockDocument(*pDoc)`，操作后需 `CATUnLockDocument(*pDoc)`
- `BoundaryExtract` 第二个参数为 NULL 时提取全部对象
- 批处理模式无需剪贴板中转

---

## 关键接口速查

| 接口 | 关键方法 | 用途 |
|------|---------|------|
| **CATISpecObject** | `Instanciate`, `AddAttribute`, `Update`, `GetFather`, `GetName` | 特征核心操作 |
| **CATISpecAttrAccess** | `GetAttrKey`, `SetString`/`GetString`, `SetInteger`/`GetInteger`, `SetSpecObject`/`GetSpecObject`, `GetListSize`, `SetSpecAttribute` | 属性读写 |
| **CATISpecAttrKey** | (不透明句柄) | 属性键，标识一个属性 |
| **CATISpecAttribute** | (AddAttribute 的返回值) | 新添加的属性对象 |
| **CATIOsmExtendable** | `AddExtension`, `QueryExtension`, `QueryAllExtensions`, `RemoveApplicativeExtensions` | 扩展管理 |
| **CATIOsmExtension** | `GetID` | 扩展标识 |
| **CATIBuild** | `Build` | Build/Update 回调 |
| **CATICutAndPastable** | `Paste`, `Remove`, `BoundaryExtract`, `Extract` | CCP 操作 |
| **CATIClientContainer** | `ListMembers` | 列出容器成员 |
| **CATOsmSUHandler** | `RetrieveSU`, `Instanciate` | StartUp 检索与实例化 |
| **LifeCycleObject** | `remove` | 特征删除 |

---

## 字典（.dico）绑定

```
CAAOsmBiographicalNovel    CAAIBiogNovel    libCAAOsmManageExtensions
CAAOsmAdd                  CATIBuild        CAAOsmBuildUpdate
CAAOsmSquare               CATIBuild        CAAOsmBuildUpdate
```

字典条目的语义：
- 当查询 LateType = "CAAOsmBiographicalNovel" 的扩展时，返回 CAAIBiogNovel 接口
- 该实现位于 `libCAAOsmManageExtensions` 共享库
- 当对 LateType = "CAAOsmAdd" 的特征执行 Update 时，调用 CATIBuild::Build，实现位于 CAAOsmBuildUpdate 模块

---

## 7 个 Use Case 模块对照

| 模块 (.m) | 核心教学内容 | 关键 API |
|-----------|------------|---------|
| **CAAOsmSimpleAttr** | 简单属性：StartUp 实例化、属性赋值、AddAttribute、特征派生 | `Instanciate`, `GetAttrKey`, `SetString`, `SetInteger`, `AddAttribute` |
| **CAAOsmAggregatedAttr** | 聚合特征：列表属性、SetSpecObject 多次、GetListSize 遍历、GetFather 父子关系 | `SetSpecObject`, `GetListSize`, `GetSpecObject(i)`, `GetFather` |
| **CAAOsmReferencedAttr** | 引用特征：多特征共享引用、无 Father、独立生命周期、LifeCycleObject::remove | `SetSpecObject`, `GetFather`(NULL), `LifeCycleObject::remove` |
| **CAAOsmAppliCont** | 应用容器：创建容器、在容器中实例化、保存/重新打开、按名称检索容器、ListMembers | `CATCreateApplicativeContainer`, `CATGetApplicativeContainer`, `ListMembers` |
| **CAAOsmBuildUpdate** | Build/Update：CATIBuild 实现、Update 触发计算、SetSpecAttribute 跨特征引用、级联更新 | `Build`, `Update`, `SetSpecAttribute` |
| **CAAOsmManageExtensions** | 扩展机制：自定义接口、TIE 绑定、扩展实现类、AddExtension、QueryExtension、QueryAllExtensions、RemoveApplicativeExtensions | `AddExtension`, `QueryExtension`, `QueryAllExtensions`, `RemoveApplicativeExtensions` |
| **CAAOsmCCP** | CCP 操作：批处理 Paste/Remove、交互模式 BoundaryExtract/Extract/Paste、格式初始化 | `Paste`, `Remove`, `BoundaryExtract`, `Extract`, `SpecBindNativeFormat` |

---

## 设计模式总结

1. **Handler 模式**：`CATOsmSUHandler` 封装了 Catalog 访问和 StartUp 操作的复杂性，提供统一的 `RetrieveSU → Instanciate` 两步接口

2. **两阶段属性访问**：`GetAttrKey` → `Set/Get`，Key 作为不透明句柄，解耦属性名称和内部存储

3. **TIE + 字典注册**：`TIE_CAAIBiogNovel(CAAEOsmBiogNovel)` + `.dico` 条目，实现了接口与实现的运行时绑定，是 CAA 扩展机制的核心

4. **DataExtension 模式**：扩展实现类继承 `CATBaseUnknown`，通过 `CATImplementClass(..., DataExtension, ..., LateType)` 注册为特定 LateType 的扩展

5. **Applicative Container 隔离**：通过不同的 ApplicativeContainer 管理不同来源的扩展，支持按容器批量移除扩展

6. **聚合 vs 引用的语义区分**：
   - 聚合 = `tk_list(tk_specobject)` = 独占父子关系
   - 引用 = `tk_specobject` = 共享引用关系

7. **Observer 模式的 Build/Update**：`Update()` 触发 `CATIBuild::Build()`，实现响应式属性计算

---

## AI Agent 学习要点

1. **特征创建的完整链路**：CATSpecs 定义 → CATfct 编译 → CATOsmSUHandler 检索 → Instanciate 实例化 → 属性赋值 → 可能的 Update 触发

2. **扩展是可插拔的模块**：通过 `AddExtension` 动态附加，通过 `RemoveApplicativeExtensions` 按容器批量移除，不影响基础特征

3. **属性键的作用域规则**：StartUp 键是全局的，实例键是局部的——错误地在不同实例间复用键会导致未定义行为

4. **特征间的三种关系**（聚合、引用、扩展）各有不同的生命周期语义——理解这些差异是正确使用 OSM 的前提

5. **Build/Update 是同步的**：`Update()` 立即调用 `Build()`，调用者可以紧接着读取计算结果

6. **CCP 操作需要格式初始化**：即使是批处理模式也需要 `SpecBindNativeFormat`

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATOsmSUHandler.htm](../api-reference/interfaces/CATOsmSUHandler.htm)
- 完整方法签名: [api-reference/interfaces/CATISpecObject.htm](../api-reference/interfaces/CATISpecObject.htm)
- 完整方法签名: [api-reference/interfaces/CATIBuild.htm](../api-reference/interfaces/CATIBuild.htm)
- 完整方法签名: [api-reference/interfaces/CATIPLMEntity.htm](../api-reference/interfaces/CATIPLMEntity.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/caascdstrusecases/](../use-cases/caascdstrusecases/)