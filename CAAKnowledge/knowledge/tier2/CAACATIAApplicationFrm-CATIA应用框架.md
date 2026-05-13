---
module: "CAACATIAApplicationFrm.edu"
category: "CAA CATIA 应用框架 — 文档定制/设置/ToolsOptions/属性页/右键菜单/搜索/特征树"
tier: "2"
status: "已完成"
---

# CAACATIAApplicationFrm.edu — CATIA 应用框架

## 模块定位

CAACATIAApplicationFrm 是 CAA 中展示 CATIA 应用级定制能力的核心框架，包含 14 个模块。它教授如何将自定义应用深度集成到 CATIA 的基础设施中：

- **新文档类型**：通过 CATIDocumentEdit 注册自定义文档
- **Tools/Options 设置**：CATIIniSettingManagment + CATSettingRepository 的设置系统
- **属性编辑页**：Edit → Properties 对话框的自定义页面
- **右键菜单**：CATIContextualMenu 扩展
- **搜索系统**：CATIIniSearchEngine 查询构建与执行
- **特征树操作**：CATNavigController 的展开/折叠
- **Viewer 视觉反馈**：CAT2DBagRep + 回调式鼠标跟踪
- **可视化扩展**：CATI3DGeoVisu / CATExtIVisu

这个框架展示了 CATIA 应用与平台深度集成的所有关键扩展点。

---

## 架构总览

```
┌─────────────────────────────────────────────────────────────────────────┐
│                     CATIA 应用级定制架构                                  │
│                                                                          │
│  ┌─────────────────┐  ┌──────────────────┐  ┌──────────────────────┐   │
│  │ Tools/Options   │  │ Edit Properties  │  │ Contextual Menu      │   │
│  │ (工具→选项)      │  │ (编辑→属性)       │  │ (右键菜单)            │   │
│  │                 │  │                  │  │                      │   │
│  │ SettingCtrl     │  │ PropertyPageEdt  │  │ CATIContextualMenu   │   │
│  │ + SettingAtt    │  │ + PropertyPageDlg│  │ + CATExtIContextual..│   │
│  │ + CATIIniSet-   │  │ + Factory        │  │                      │   │
│  │   tingManagment │  │                  │  │                      │   │
│  └─────────────────┘  └──────────────────┘  └──────────────────────┘   │
│                                                                          │
│  ┌─────────────────┐  ┌──────────────────┐  ┌──────────────────────┐   │
│  │ Document        │  │ Root Properties  │  │ Search               │   │
│  │ (新文档类型)     │  │ (根属性)          │  │ (搜索)                │   │
│  │                 │  │                  │  │                      │   │
│  │ CATIDocumentEdit│  │ CATIRoot-        │  │ CATIIniSearchEngine  │   │
│  │ CreateDefault-  │  │ Properties       │  │ + CATPSO             │   │
│  │ Window          │  │ GetListOfEditors │  │                      │   │
│  └─────────────────┘  └──────────────────┘  └──────────────────────┘   │
│                                                                          │
│  ┌─────────────────┐  ┌──────────────────┐  ┌──────────────────────┐   │
│  │ SpecTree        │  │ Viewer Feedback  │  │ Visualization        │   │
│  │ (特征树)         │  │ (视觉反馈)        │  │ (可视化)              │   │
│  │                 │  │                  │  │                      │   │
│  │ CATNavig-       │  │ CAT2DBagRep      │  │ CATI3DGeoVisu        │   │
│  │ Controller      │  │ + Callback       │  │ + CATExtIVisu        │   │
│  └─────────────────┘  └──────────────────┘  └──────────────────────┘   │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## 核心知识

### 1. 文档定制 — CATIDocumentEdit

定义新的文档类型（如 CAAGeometry），使其出现在 File → New 对话框中：

```cpp
// 字典注册
// CAAGeom  CATIDocumentEdit  libCAACafGeoDocument

class CAAECafGeoDocument : public CATBaseUnknown {
    CATDeclareClass;
public:
    CATFrmWindow* CreateDefaultWindow(CATFrmEditor* iEditor);
    CATPathElement GetActiveObject();
    void Activate();
    void Deactivate();
    void* MemoryDraw(unsigned short iFormat, int iWidth, int iHeight);
};

// 实现
CATImplementClass(CAAECafGeoDocument, DataExtension, CATBaseUnknown, CAAGeom);
TIE_CATIDocumentEdit(CAAECafGeoDocument);
```

**CreateDefaultWindow** — 创建文档的显示窗口：
```cpp
CATFrmWindow* CAAECafGeoDocument::CreateDefaultWindow(CATFrmEditor* iEditor) {
    // 1. 创建几何窗口（CAAAfrGeometryWks 中定义的）
    CATFrmWindow* pWindow = CAAAfrGeoWksWindow::CreateWindow(iEditor);
    // 2. 创建规范树窗口
    CATFrmWindow* pSpecTreeWindow = CAAAfrNavigatorWindow::CreateWindow(iEditor);
    // 3. 附加到编辑器
    iEditor->AttachWindow(pWindow);
    iEditor->AttachWindow(pSpecTreeWindow);
    return pWindow;
}
```

**GetActiveObject** — 返回文档激活后的初始选中对象路径：
```cpp
CATPathElement CAAECafGeoDocument::GetActiveObject() {
    CATPathElement path = _ActivePath;  // 在构造函数中从容器获取
    return path;
}
```

---

### 2. Tools/Options 设置系统

CATIA 的 Tools → Options 对话框可通过三层组件扩展：

**2.1 Setting Controller（设置控制器）**

全局单例，管理设置仓库的生命周期：

```cpp
// CAACafGeometryEltSettingCtrl — 控制器类
class CAACafGeometryEltSettingCtrl : public CATBaseUnknown {
    static HRESULT GetSettingController(CAACafGeometryEltSettingCtrl** oCtrl);
private:
    static CATIniCleanerSettingCtrl _CleanerCtrl;  // 会话结束时自动清理
};

// 全局获取函数（ProtectedInterfaces 中）
ExportedByCAACafCtrlToolsOptions 
HRESULT GetCAACafGeometryEltSettingCtrl(CAACafGeometryEltSettingCtrl** oCtrl);

// 控制器注册为 CATIIniSettingManagment
// 字典: CAACafGeometryEltSettingCtrl  CATIIniSettingManagment  libCAACafCtrlToolsOptions
TIE_CATIIniSettingManagment(CAACafGeometryEltSettingCtrl);
```

**2.2 Setting Attribute（设置属性接口）**

定义具体的设置项和读写方法：

```cpp
// CAAICafGeometryEltSettingAtt — 自定义设置接口
class CAAICafGeometryEltSettingAtt : public IUnknown {
public:
    virtual HRESULT Initialize() = 0;  // 初始化，读取所有设置项的默认值
    
    virtual HRESULT GetIdentifierVisibility(CATString& oIdVisibility) = 0;
    virtual HRESULT SetIdentifierVisibility(const CATString& iIdVisibility) = 0;
    // 取值: "IdHide" | "IdShow" | "IdPreSelectShow"
    
    virtual HRESULT GetMaxPointCurve(int& oMaxPoint) = 0;
    virtual HRESULT SetMaxPointCurve(const int iMaxPoint) = 0;
    // 取值: 2 ~ 100
    
    virtual HRESULT GetImplPointVisibility(CATString& oImplPointVisibility) = 0;
    virtual HRESULT SetImplPointVisibility(const CATString& iImplPointVisibility) = 0;
    // 取值: "ImplPointShow" | "ImplPointHide"
    
    virtual HRESULT GetInfoXxx(CATSettingInfo* oInfo) = 0;  // 获取设置元信息
};
```

**2.3 Setting Attribute 实现**

```cpp
// CAAECafGeometryEltSettingAtt — 设置属性的具体实现
class CAAECafGeometryEltSettingAtt : public CATBaseUnknown {
    CATSettingRepository* _pSettingRep;  // 底层设置仓库
};

// TIE 绑定 + 字典注册
TIE_CAAICafGeometryEltSettingAtt(CAAECafGeometryEltSettingAtt);
CATImplementClass(CAAECafGeometryEltSettingAtt, DataExtension, CATBaseUnknown, 
                  CAACafGeometryEltSettingCtrl);
// 字典: CAACafGeometryEltSettingCtrl  CAAICafGeometryEltSettingAtt  libCAACafCtrlToolsOptions

HRESULT Initialize() {
    _pSettingRep = CATSettingRepository::GetRepository("CAACafGeometryElt");
    // 调用所有 GetXxx 方法，触发默认值的写入
    CATString visibility;
    GetIdentifierVisibility(visibility);
    int maxPoint;
    GetMaxPointCurve(maxPoint);
    CATString implVisibility;
    GetImplPointVisibility(implVisibility);
    return S_OK;
}

HRESULT GetMaxPointCurve(int& oMaxPoint) {
    HRESULT rc = _pSettingRep->ReadSetting("MaxPointCurve", &oMaxPoint);
    if (FAILED(rc)) {
        oMaxPoint = 50;  // 默认值
    }
    return S_OK;
}
```

**2.4 Property Page Dialog（设置页面对话框）**

```cpp
// CAACafElementPropertyPageDlg — 设置页面 UI
class CAACafElementPropertyPageDlg : public CATDlgFrame {
    void Build();          // 构建 UI 控件
    void ValueSettings();  // 从设置仓库读取值并填充 UI
    
    // 回调：每个控件修改时立即更新设置仓库
    void IdHideCB(...);
    void IdShowCB(...);
    void MaxPointCB(...);
    
    CAAICafGeometryEltSettingAtt* _pISettingAttForCtrl;  // 设置接口
};

// 控件修改回调
void CAACafElementPropertyPageDlg::MaxPointCB(...) {
    int maxPoint = _pMaxPoint->GetCurrentValue();
    _pISettingAttForCtrl->SetMaxPointCurve(maxPoint);
    // 立即写入设置仓库（无需手动 Commit）
}
```

**2.5 Property Page Editor（设置页编辑器）**

```cpp
// CAACafElementPropertyPageEdt — 管理设置页面的生命周期
class CAACafElementPropertyPageEdt : public CATBaseUnknown {
    // 实现 CATIUserSettings 接口
    // - SetUserSettingsValue: 调用 Dlg->Build() + Dlg->ValueSettings()
    // - Reset: 重置为默认值
    // - Commit: 提交更改
    // - Rollback: 回滚更改
};
```

**2.6 Property Page Factory**

```cpp
// CAACafElementPropertyPageEdtFactory — 工厂类
TIE_CAAICafElementPropertyPageEdtFactory(CAACafElementPropertyPageEdtFactory);

// 字典注册（.dico）
// CATUserSettingsManager  CAAICafElementPropertyPageEdtFactory  libCAACafEltToolsOptions

// 工厂注册（.fact）
// CAACafElementPropertyPageEdt  CAAICafElementPropertyPageEdtFactory
```

**设置系统数据流**：
```
Tools → Options 对话框
        │
        ▼
CATUserSettingsManager (系统组件)
        │ 查询 .dico
        ▼
CAAICafElementPropertyPageEdtFactory (工厂)
        │ CreateInstance
        ▼
CAACafElementPropertyPageEdt (编辑器)
        │ 管理生命周期
        ▼
CAACafElementPropertyPageDlg (UI 页面)
        │ 读写设置
        ▼
CAAICafGeometryEltSettingAtt (设置接口)
        │ ReadSetting / WriteSetting
        ▼
CATSettingRepository (设置仓库)
```

---

### 3. 属性编辑页 — Edit → Properties

与 Tools/Options 类似，但对话框位置在 Edit → Properties：

```cpp
// CATEditorManager  CAAICafColorPropertyPageEdtFactory  libCAACafEditColorProp
// CATEditorManager  CAAICafTexturePropertyPageEdtFactory  libCAACafEditTextureProp

// .fact 文件:
// CAACafColorPropertyPageEdt  CAAICafColorPropertyPageEdtFactory
// CAACafTexturePropertyPageEdt  CAAICafTexturePropertyPageEdtFactory
```

**区别**：Tools/Options 使用 `CATUserSettingsManager`，Properties 使用 `CATEditorManager`。两者模式完全相同（Factory → Editor → Dialog）。

---

### 4. 右键菜单 — CATIContextualMenu

为特定对象类型添加右键菜单项：

```cpp
// 字典: CAASysEllipse  CATIContextualMenu  libCAACafContextualMenu

class CAAECafContextualMenuEllipse : public CATExtIContextualMenu {
    CATDeclareClass;
};

CATImplementClass(CAAECafContextualMenuEllipse, DataExtension, CATBaseUnknown, CAASysEllipse);
TIE_CATIContextualMenu(CAAECafContextualMenuEllipse);
```

**菜单构建**：
```cpp
CAAECafContextualMenuEllipse::CAAECafContextualMenuEllipse() {
    // 1. 获取默认菜单（Cut, Copy, Paste, Properties, ...）
    CATCmdContainer* pMenu = NULL;
    CATExtIContextualMenu::GetContextualMenu(pMenu);

    if (pMenu) {
        // 2. 创建自定义菜单项
        NewAccess(CATCmdStarter, pStEllipse, CAACafContextualMenuEllipseStr);
        NewAccess(CATCmdStarter, pStCircle, CAACafContextualMenuCircleStr);
        NewAccess(CATCmdSeparator, pSep1, CAACafContextualMenuSep);

        // 3. 绑定命令头部（命令头部在 Workshop 中定义）
        SetAccessCommand(pStEllipse, "CAAAfrEllipseHdr");
        SetAccessCommand(pStCircle, "CAAAfrCircleHdr");

        // 4. 链式排列
        SetAccessNext(pStEllipse, pStCircle);
        SetAccessNext(pStCircle, pSep1);

        // 5. 添加到默认菜单末尾
        AddAccessChild(pMenu, pStEllipse);
    }
}
```

---

### 5. 根属性 — CATIRootProperties

定义当选中根对象时，Properties 对话框中显示哪些属性编辑页：

```cpp
// 字典: CAASysGeomRootObj  CATIRootProperties  libCAACafRootProperties

class CAAECafRootProperties : public CATBaseUnknown {
    CATDeclareClass;
public:
    virtual CATListOfCATString GetListOfEditors();
    virtual void GetAssociatedObject();
};

CATImplementClass(CAAECafRootProperties, DataExtension, CATBaseUnknown, CAASysGeomRootObj);
TIE_CATIRootProperties(CAAECafRootProperties);

CATListOfCATString CAAECafRootProperties::GetListOfEditors() {
    CATListOfCATString ListOfEditor;
    ListOfEditor.Append("CAACafTexturePropertyPageEdt");
    ListOfEditor.Append("CAACafColorPropertyPageEdt");
    return ListOfEditor;
}
```

---

### 6. 搜索系统 — CATIIniSearchEngine

构建查询并在 PSO（Pre-Selected Objects）中显示结果：

```cpp
// 搜索命令中使用三个核心组件
CATIIniSearchEngine*   _pIniSearchEngine;    // 搜索引擎
CATIIniSearchContext*  _pIniSearchContext;    // 搜索上下文
CATIIniSearchServices* _pIniSearchServices;   // 搜索服务
CATPSO*                _pPso;                // 预选对象（显示搜索结果）
```

**搜索流程**：
```cpp
// 1. Init — 创建搜索组件
void CAACafSearchCmd::Init() {
    // 获取搜索引擎
    ::CATGetSearchEngine("CAA", &_pIniSearchEngineOnCurrentEngine);
    
    // 获取搜索上下文
    ::CATGetSearchContext("CAA", &_pIniSearchContextOnCurrentContext);
    
    // 获取搜索服务
    ::CATGetSearchServices("CAA", &_pIniSearchServices);
    
    // 创建查询条件
    CreateCriteria();
}

// 2. CreateCriteria — 创建所有查询条件
HRESULT CreateCriteria() {
    // 创建查询条件（如 "Type=Point", "Color=Red" 等）
    // 保存条件文本供 UI 显示
    _pCriterionTextList->Append("All Points");
    _pCriterionTextList->Append("All Lines");
    // ...
}

// 3. LaunchQuery — 执行查询
CATBoolean LaunchQuery(void*) {
    // 获取当前选中的条件和上下文
    int criterion;
    CATIIniSearchContext::Scope context;
    _pSearchDlg->GetCurrentCriterion(criterion);
    _pSearchDlg->GetCurrentContext(context);
    
    // 执行搜索
    // ...
    
    // 在 PSO 中高亮显示结果
    _pPso = new CATPSO();
    // 将搜索结果加入 PSO
}
```

**搜索对话框**：
```cpp
class CAACafSearchDlg : public CATDlgDialog {
    CATDlgCombo*     _pCriteriaCombo;     // 查询条件选择
    CATDlgCombo*     _pContextCombo;      // 搜索范围选择
    CATDlgPushButton* _pLaunchBtn;        // 启动按钮
    CATDlgEditor*    _pResultQueryEditor; // 结果计数显示
    CATPSO*          _pPso;              // 预选对象
};
```

---

### 7. 特征树操作 — CATNavigController

展开/折叠规范树节点：

```cpp
// CAACafCollapseExpandCmd — 展开/折叠命令
class CAACafCollapseExpandCmd : public CATStateCommand {
    CATPathElementAgent* _daObjectToExpandNode;  // 选择节点
    CATNavigController*  _pNavigController;      // 导航控制器
    char*                _pExpandMode;           // "Expand" / "Collapse" / "ExpandAll"
};

// 获取 NavigController
void GetNavigController() {
    CATFrmEditor* pEditor = GetEditor();
    CATFrmWindow* pWindow = pEditor->GetSpecTreeWindow();
    pWindow->GetNavigController(&_pNavigController);
}

// 展开节点
void ExpandCollapseNode(CATBaseUnknown_var iObject) {
    if (!strcmp(_pExpandMode, "Expand")) {
        _pNavigController->Expand(iObject);
    } else if (!strcmp(_pExpandMode, "Collapse")) {
        _pNavigController->Collapse(iObject);
    }
}

// 展开全部子节点
void ExpandAllNode(CATBaseUnknown_var iObject) {
    _pNavigController->ExpandAll(iObject);
}
```

---

### 8. Viewer 视觉反馈 — CAT2DBagRep + Callback

在 Viewer 中实时显示鼠标位置、对象信息等：

```cpp
// CAACafViewerFeedbackManager — 全局单例反馈管理器
class CAACafViewerFeedbackManager : public CATBaseUnknown {
    CAT2DBagRep*  _pInformationsToDisplay;  // 2D 图形包（文字信息）
    CATViewer*    _pCurrentViewer;          // 当前 Viewer
    CATCallback   _ViewerFeedbackCB;        // Viewer 事件回调
    CATCallback   _WindowActivatedCB;       // 窗口激活回调
    CATCallback   _WindowDeactivatedCB;     // 窗口停用回调
};

// 获取单例
static void GetManager(CAACafViewerFeedbackManager** opManager);

// 激活反馈
void SetViewerFeedbackOn() {
    CATFrmLayout* pLayout = CATFrmLayout::GetCurrentLayout();
    CATFrmWindow* pWindow = pLayout->GetCurrentWindow();
    _pCurrentViewer = pWindow->GetViewer();
    
    // 创建 2D 图形包
    _pInformationsToDisplay = new CAT2DBagRep();
    
    // 订阅 Viewer 鼠标移动事件
    AddCallback(_pCurrentViewer, CATViewer::MouseMove,
        (CATSubscriberMethod)&CAACafViewerFeedbackManager::ViewerFeedbackCB, ...);
}

// 回调：鼠标移动时更新信息
void ViewerFeedbackCB(CATCallbackEvent, void*, CATNotification*, ...) {
    // 获取鼠标位置
    // 获取鼠标下的对象
    // 更新 CAT2DBagRep 中的文字
    // 刷新显示
}
```

**ViewerFeedbackCmd** — 通过 Check Header 控制的开关命令：
```cpp
// 继承 CATCommand（非 CATStateCommand），是简单的切换命令
class CAACafViewerFeedbackCmd : public CATCommand {
    CAACafViewerFeedbackCmd(void* iArgument);
    // iArgument: 1 = check（激活）, 2 = uncheck（停用）
};
```

---

### 9. 可视化扩展 — CATI3DGeoVisu

为自定义几何体（如椭圆）添加 3D 可视化：

```cpp
// 字典: CAASysEllipse  CATI3DGeoVisu  libCAACafUseToolsOptions

class CAAECafVisuEllipse : public CATExtIVisu {
    CATDeclareClass;
public:
    virtual CATRep* BuildRep();  // 构建图形表示
};

CATImplementClass(CAAECafVisuEllipse, DataExtension, CATBaseUnknown, CAASysEllipse);
TIE_CATI3DGeoVisu(CAAECafVisuEllipse);

CATRep* CAAECafVisuEllipse::BuildRep() {
    // 从 CAASysEllipse 读取几何数据
    // 构建 CAT3DRep（线段、曲线等）
    // 返回图形表示
}
```

---

### 10. 设置系统的可视化应用

CAACafUseToolsOptions 展示了如何使用 Tools/Options 中的设置控制可视化：

```cpp
// CAACafCircleWindowCmd — 创建圆的命令，使用设置值
void CAACafCircleWindowCmd::CreateCircle() {
    // 获取设置控制器
    CAACafGeometryEltSettingCtrl* pCtrl = NULL;
    GetCAACafGeometryEltSettingCtrl(&pCtrl);
    
    // 获取设置接口
    CAAICafGeometryEltSettingAtt* pSettingAtt = NULL;
    pCtrl->QueryInterface(IID_CAAICafGeometryEltSettingAtt, (void**)&pSettingAtt);
    
    // 读取设置值
    int maxPoint;
    pSettingAtt->GetMaxPointCurve(maxPoint);  // 用于圆的离散化精度
    
    CATString visibility;
    pSettingAtt->GetIdentifierVisibility(visibility);  // 控制标识符显示
    
    // 应用设置值到可视化...
}
```

---

## 关键接口速查

| 接口/类 | 关键方法 | 用途 |
|---------|---------|------|
| **CATIDocumentEdit** | `CreateDefaultWindow`, `GetActiveObject` | 新文档类型注册 |
| **CATIIniSettingManagment** | (生命周期管理) | 设置管理器接口 |
| **CAAICafGeometryEltSettingAtt** | `Initialize`, `Get/SetXxx`, `GetInfoXxx` | 自定义设置属性接口 |
| **CATSettingRepository** | `GetRepository`, `ReadSetting`, `WriteSetting` | 设置持久化仓库 |
| **CATIniCleanerSettingCtrl** | (自动清理) | 设置控制器清理器 |
| **CAAICafElementPropertyPageEdtFactory** | `CreateInstance` | 属性页工厂 |
| **CATIUserSettings** | `SetUserSettingsValue`, `Reset`, `Commit`, `Rollback` | 设置页编辑器接口 |
| **CATIEditProperties** | (同上) | 属性编辑页接口 |
| **CATIRootProperties** | `GetListOfEditors`, `GetAssociatedObject` | 根对象属性列表 |
| **CATIContextualMenu** | (通过 CATExtIContextualMenu 使用) | 右键菜单扩展 |
| **CATExtIContextualMenu** | `GetContextualMenu` | 右键菜单适配器 |
| **CATIIniSearchEngine** | (查询构建) | 搜索引擎 |
| **CATIIniSearchContext** | (查询范围) | 搜索上下文 |
| **CATPSO** | (预选对象集) | 搜索结果可视化 |
| **CATNavigController** | `Expand`, `Collapse`, `ExpandAll` | 特征树导航 |
| **CATI3DGeoVisu** | `BuildRep` | 3D 可视化接口 |
| **CATExtIVisu** | `BuildRep` | 可视化适配器基类 |
| **CAT2DBagRep** | (2D 图形包) | Viewer 覆盖层显示 |

---

## 14 个 Use Case 模块对照

| 模块 (.m) | 核心教学内容 | 关键技术 |
|-----------|------------|---------|
| **CAACafGeoDocument** | 新文档类型 | CATIDocumentEdit, CreateDefaultWindow, GetActiveObject |
| **CAACafCtrlToolsOptions** | 设置控制器 | CATIIniSettingManagment, CATSettingRepository, CAAICafGeometryEltSettingAtt |
| **CAACafEltToolsOptions** | Tools/Options 元素页 | Factory + Editor + Dialog 三层模式 |
| **CAACafViewToolsOptions** | Tools/Options 视图页 | 同上 |
| **CAACafEditColorProp** | Edit→Properties 颜色页 | CATEditorManager, CATIEditProperties |
| **CAACafEditTextureProp** | Edit→Properties 纹理页 | 同上 |
| **CAACafRootProperties** | 根对象属性列表 | CATIRootProperties, GetListOfEditors |
| **CAACafContextualMenu** | 右键菜单 | CATIContextualMenu, CATExtIContextualMenu |
| **CAACafSearch** | 搜索系统 | CATIIniSearchEngine, CATPSO, SearchDlg |
| **CAACafSpecTree** | 特征树操作 | CATNavigController, Expand/Collapse |
| **CAACafViewerFeedback** | Viewer 视觉反馈 | CAT2DBagRep, Callback, CheckHeader 开关 |
| **CAACafUseToolsOptions** | 设置可视化应用 | CATExtIVisu, CATI3DGeoVisu, BuildRep |
| **CAACafGrapPropCombo** | 图形属性 Combo | Combo 控件与属性联动 |
| **CAACafDlgView** | ListView/MVC | SampleViewModel, SampleViewController, CATDlgListView |

---

## 设计模式总结

1. **三层设置架构**：Controller（管理生命周期）+ Attribute（定义设置项）+ Dialog（UI 页面）— 职责清晰分离

2. **Factory + Editor + Dialog 模式**：工厂创建编辑器，编辑器管理对话框生命周期和设置提交/回滚

3. **双字典注册**：`.dico`（接口-实现绑定）+ `.fact`（工厂-产品绑定）— 两层间接寻址

4. **Cleaner 单例模式**：`CATIniCleanerSettingCtrl` 确保设置控制器在会话结束时正确清理

5. **DataExtension 扩展模式**：右键菜单（`CAAECafContextualMenuEllipse`）、可视化（`CAAECafVisuEllipse`）、根属性（`CAAECafRootProperties`）都是 DataExtension

6. **CATExtIContextualMenu 适配器模式**：在默认菜单基础上追加自定义项，无需重写整个菜单

7. **PSO 搜索可视化**：搜索结果通过 CATPSO 预选高亮，而非直接选中

8. **Callback 视觉反馈**：`AddCallback` 订阅 Viewer 事件，`CAT2DBagRep` 渲染覆盖层信息

---

## AI Agent 学习要点

1. **新文档类型需要实现 CATIDocumentEdit**，核心是 `CreateDefaultWindow`（创建显示窗口）和 `GetActiveObject`（返回初始选中路径）。

2. **Tools/Options 需要三层组件**：Factory（.fact 注册）→ Editor（管理生命周期）→ Dialog（UI + 设置读写）。`.dico` 注册 Factory 到系统管理器。

3. **设置属性接口（如 CAAICafGeometryEltSettingAtt）** 中的每个 `GetXxx` 方法必须提供默认值（当 `ReadSetting` 失败时），这是 Reset 功能的基础。

4. **右键菜单通过 CATExtIContextualMenu** 获取默认菜单后追加，使用 `SetAccessNext` 链式排列，`AddAccessChild` 添加到菜单。

5. **CATIRootProperties.GetListOfEditors** 返回编辑器名称列表（字符串），系统据此决定显示哪些属性页。

6. **搜索系统使用 CATIIniSearchEngine + CATIIniSearchContext + CATIIniSearchServices** 三个组件协作，结果通过 CATPSO 可视化。

7. **特征树操作通过 CATNavigController** 完成，需要从 SpecTreeWindow 获取。

---

## 相关资源

- 完整方法签名: [api-reference/interfaces/CATIDocumentEdit.htm](../api-reference/interfaces/CATIDocumentEdit.htm)
- 完整方法签名: [api-reference/interfaces/CATIWebWindow.htm](../api-reference/interfaces/CATIWebWindow.htm)
- 完整方法签名: [api-reference/interfaces/CATIPSO.htm](../api-reference/interfaces/CATIPSO.htm)
- 完整方法签名: [api-reference/interfaces/CATISearchServices.htm](../api-reference/interfaces/CATISearchServices.htm)
- 结构化查询: [knowledge_base.json → method_index](../data/knowledge_base.json)
- 使用案例: [use-cases/](../use-cases/)