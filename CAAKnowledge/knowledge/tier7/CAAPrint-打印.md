# CAAPrint — 打印框架

**模块**: CAAPrint.edu | **层级**: Tier 7 | **规模**: 16 个文件（7 个头文件 + 8 个 .cpp + 1 个 IdentityCard）

---

## 模块定位

CAAPrint 是 CATIA Print 框架最完整的教学模块，覆盖了打印的全部场景：交互式应用中的图像显示与打印、批处理格式转换（CGM→TIFF）、批处理直接打印（JPEG→打印机）、以及自定义可打印对象（Printable Object）的开发模式。

---

## 架构概览

```
CAAPrint.edu/
├── IdentityCard/
│   └── IdentityCard.h             依赖: System, Mathematics, Dialog,
│                                      Visualization, VisualizationBase,
│                                      Print, PrintBase
├── PrivateInterfaces/
│   ├── CAAPrtPrintableObjects.h   导出宏
│   ├── CAAPrtStringDialog.h       字符串打印对话框
│   └── CAAPrtTestImage.h          测试图像（含 CATIPrintable 实现）
├── CAAPrtApplication.m/
│   ├── LocalInterfaces/
│   │   ├── CAAPrtApplication.h    交互式应用类
│   │   └── CAAPrtDialog.h         主窗口（菜单+2DViewer）
│   └── src/
│       ├── CAAPrtApplication.cpp  应用入口
│       └── CAAPrtDialog.cpp       主窗口实现（~300行）
├── CAAPrtChangeFormat.m/src/
│   └── CAAPrtChangeFormat.cpp     批处理: CGM → TIFF
├── CAAPrtPrintFile.m/src/
│   └── CAAPrtPrintFile.cpp        批处理: JPEG → 打印机
└── CAAPrtPrintableObjects.m/
    ├── LocalInterfaces/
    │   ├── CAAPrtPrintableString.h 可打印字符串对象
    │   └── CAAPrtStringImage.h     字符串图像
    └── src/
        ├── CAAPrtPrintableString.cpp
        ├── CAAPrtStringDialog.cpp
        ├── CAAPrtStringImage.cpp
        └── CAAPrtTestImage.cpp     测试图像（文本/颜色/线条/位图）
```

> 该项目没有 PublicInterfaces/ProtectedInterfaces 目录。

---

## 四个子模块详解

### 1. CAAPrtApplication.m — 交互式应用

**CAAPrtApplication** — 继承 CATInteractiveApplication（自动管理事件循环）。

```cpp
void BeginApplication() {
    // 1. 创建主窗口 CAAPrtDialog
    CAAPrtDialog *pMainWindow = new CAAPrtDialog(this, "mainWindow",
        CATDlgWndNoResize);
    pMainWindow->Init();
    pMainWindow->SetVisibility(CATDlgShow);

    // 2. 订阅窗口关闭事件 → DestroyCB → Destroy()
    AddAnalyseNotificationCB(pMainWindow,
        pMainWindow->GetWindCloseNotification(),
        (CATCommandMethod)&CAAPrtApplication::DestroyCB, NULL);

    // 3. 可选：读取命令行 TIFF 文件并显示
    if (argc == 2) pMainWindow->DisplayImage(argv[1]);
}
```

**CAAPrtDialog** — 主窗口，包含菜单栏和 2D Viewer。

**菜单结构**:
```
File 菜单:
  Open...       → CATDlgFile 选择 TIFF → DisplayImage
  Print...      → CATPrintDialog(this, "Print", _pViewer)
  Capture...    → CATPrintCaptureDialog(this, "Capture", _pViewer)
  Album...      → CATPrintAlbumDialog(this, "Album")
  PrintMan...   → CATPrinterManagerDialog(this, "PrintMan")
  Exit          → Clean() + SendNotification(close)

Printable Objects 菜单:
  Display...    → 创建 CAAPrtTestImage → CATPrint2DRep → Viewer
  Print...      → CAAPrtTestImage → CATPrintDialog(printable)
  Label...      → CAAPrtStringDialog → 输入字符串 → 打印标签
```

**DisplayImage 方法**:
```cpp
void DisplayImage(const char *iPath) {
    CATPrintFileImage *image = new CATPrintFileImage(iPath, "TIFF");
    CATPrintParameters parameters;
    parameters.SetMargins(0, 0, 0, 0);
    CAT2DRep *rep = new CATPrint2DRep(image, parameters);
    image->Release();
    _pViewer->AddRep(rep);
    _pViewer->Reframe();
}
```

---

### 2. CAAPrtChangeFormat.m — 格式转换（批处理）

**功能**: CGM 文件 → TIFF 光栅文件。

```cpp
int main(int argc, char* argv[]) {
    // 1. 输入: .cgm 文件
    // 2. 输出: CAAPrtOut环境变量指定目录 + 输入文件名 + ".tif"

    // 3. 初始化 Printer Manager
    CATPrinterManager::Begin();

    // 4. 创建图像
    CATPrintFileImage *pImage = new CATPrintFileImage(InputName, "CGM");

    // 5. 创建光栅文件设备
    CATPrintFileDevice *pDevice = new CATPrintFileDevice(TmpFile, "RASTER");

    // 6. 配置参数
    CATPrintParameters Parameters;
    Parameters.SetWhitePixel(1);          // 白像素不打印为黑
    Parameters.SetMapToPaper(1);          // 图像适配纸张
    Parameters.SetBanner("CAAPrtChangeFormat");
    Parameters.SetBannerPosition(CATPRINT_TOP);
    Parameters.SetLineWidthSpecificationMode(CATPRINT_SCALED);
    Parameters.SetLineTypeSpecificationMode(CATPRINT_SCALED);

    // 7. 打印（输出到文件）
    pImage->Print(pDevice, Parameters);

    // 8. 清理
    pDevice->Release();
    pImage->Release();
    CATPrinterManager::End();
}
```

**核心概念**:
- `CATPrintFileImage(format)` — 从文件读取图像
- `CATPrintFileDevice(format)` — 将图像写入文件（RASTER=TIFF）
- `CATPrintParameters` — 控制打印参数（边距、缩放、线宽、Banner等）
- `CATPrinterManager::Begin/End` — 打印管理器生命周期

---

### 3. CAAPrtPrintFile.m — 直接打印（批处理）

**功能**: JPEG 文件 → 用户选择的打印机。

```cpp
int main(int argc, char* argv[]) {
    // 1. 初始化
    CATPrinterManager::Begin();

    // 2. 列出所有打印机
    for (int i = 0; i < CATPrinterManager::GetPrinterCount(); i++) {
        CATPrinter printer = CATPrinterManager::GetPrinterFromIndex(i);
        cout << i+1 << " : " << printer.GetDescription() << endl;
    }

    // 3. 用户选择打印机（stdin 输入编号）
    cin >> PrinterIndex;
    CATPrinter Printer = CATPrinterManager::GetPrinterFromIndex(PrinterIndex - 1);

    // 4. 创建图像
    CATPrintFileImage *pImage = new CATPrintFileImage(InputName, "JPEG");

    // 5. 创建打印机设备
    CATPrinterDevice Device(&Printer);

    // 6. 配置参数
    CATPrintParameters Parameters;
    Parameters.SetRotation(CATPRINTCCW_90);  // 旋转 90°
    Parameters.SetMapToPaper(1);             // 适配纸张
    Parameters.SetMargins(20, 20, 10, 10);

    // 7. 打印
    pImage->Print(&Device, Parameters);

    // 8. 清理
    pImage->Release();
    CATPrinterManager::End();
}
```

**打印机管理 API**:
| API | 功能 |
|-----|------|
| CATPrinterManager::GetPrinterCount() | 获取可用打印机数量 |
| CATPrinterManager::GetPrinterFromIndex(i) | 按索引获取打印机 |
| CATPrinter::GetDescription() | 获取打印机描述 |

---

### 4. CAAPrtPrintableObjects.m — 可打印对象

展示了两种让对象变得"可打印"的模式。

#### 模式 A: 图像直接实现 CATIPrintable（CAAPrtTestImage）

```cpp
CATImplementClass(CAAPrtTestImage, Implementation, CATPrintImage, CATNull);
// OM-derives from CATPrintImage → 自动继承 CATIPrintable 实现
// 无需额外代码！
```

**CAAPrtTestImage::Decode** — 绘制四种元素类型:

```
┌─────────────────────────────────────┐
│  CATIA V5 Print Test Page           │  ← DrawTexts (黑体 Helvetica)
│  Congratulations : your printer ... │
├─────────────────────────────────────┤
│  Red gradient   ████████████████    │  ← DrawColors (RGB 渐变矩形)
│  Green gradient ████████████████    │
│  Blue gradient  ████████████████    │
│  Grey gradient  ████████████████    │
├─────────────────────────────────────┤
│  ═══ ─── ··· ─·─ ───               │  ← DrawLines (5种线型×6种线宽×5色)
│  ◜◝ ◜◝ ◜◝ ◜◝ ◜◝                    │    圆弧、椭圆弧、折线
├─────────────────────────────────────┤
│  [RGB Bitmap] [L Bitmap] ×4 旋转    │  ← DrawBitmaps (CATPixelImage)
└─────────────────────────────────────┘
```

#### 模式 B: 包装对象实现 CATIPrintable（CAAPrtPrintableString）

```cpp
TIE_CATIPrintable(CAAPrtPrintableString);
CATImplementClass(CAAPrtPrintableString, Implementation,
                  CATBaseUnknown, CATNull);

// CreatePrintableImage 返回实际的图像对象
CATPrintImage * CreatePrintableImage(void) {
    return new CAAPrtStringImage(_String);
}
```

**CAAPrtStringImage::Decode** — 绘制带锯齿边框的字符串:

```cpp
// 1. 绘制文本（Courier Bold, 黑色）
iGenerator->DrawGeometricText(x, y, _String);

// 2. 绘制锯齿边框（红色折线）
//    底部: ─┴─┴─┴─...  右侧: ─┤─┤─┤
//    顶部: ─┬─┬─┬─...  左侧: ─├─├─├
```

**CAAPrtStringDialog** — 交互式对话框:

```
┌──────────────────────────┐
│ StringLabel:             │
│ [________________]       │  ← CATDlgEditor（用户输入）
│          [Apply] [Cancel]│
└──────────────────────────┘
       ↓ ApplyCB
  1. 从 Editor 获取文本
  2. 创建 CAAPrtPrintableString(text)
  3. 打开 CATPrintDialog(printable)
```

---

## 关键设计模式对比

| 模式 | 实现方式 | 适用场景 |
|------|----------|----------|
| **图像即打印体** | OM-derive from CATPrintImage → 自动实现 CATIPrintable | 图像本身就需要被打印 |
| **包装打印体** | 独立类 + TIE_CATIPrintable + CreatePrintableImage | 已有组件需要打印能力，但不能改继承链 |

---

## 打印参数总结

| 参数 | 方法 | 说明 |
|------|------|------|
| 旋转 | SetRotation(CATPRINTCCW_90) | 逆时针旋转 90° |
| 适配纸张 | SetMapToPaper(1) | 图像缩放至纸张大小 |
| 边距 | SetMargins(L, R, T, B) | 上下左右边距（mm） |
| 白像素 | SetWhitePixel(1) | 白色像素不打印（透明） |
| Banner | SetBanner("text") | 页眉文字 |
| 线宽模式 | SetLineWidthSpecificationMode(CATPRINT_SCALED) | 线宽随缩放变化 |
| 线型模式 | SetLineTypeSpecificationMode(CATPRINT_SCALED) | 虚线长度随缩放变化 |

---

## 依赖关系

```
System → Mathematics → Dialog → Visualization
  → VisualizationBase → Print → PrintBase
```

---

## 总结

CAAPrint 是 Print 框架最全面的教学模块，覆盖四大场景：

1. **交互式应用** — CAAPrtApplication + CAAPrtDialog：菜单驱动，集成 Print/Capture/Album/PrinterManager 标准命令
2. **格式转换** — CAAPrtChangeFormat：CGM → TIFF，展示 CATPrintFileDevice 的文件输出能力
3. **直接打印** — CAAPrtPrintFile：JPEG → 用户选择的打印机，展示打印机列表查询和选择
4. **自定义打印体** — CAAPrtPrintableObjects：两种模式（继承 CATPrintImage 或 TIE_CATIPrintable），以及 CATPrintGenerator 的 Decode 绘制管线

关键设计要点：
- CATPrinterManager::Begin/End 管理打印生命周期
- CATPrintGenerator 是绘制的核心抽象（MoveTo/LineTo/DrawText/DrawBitmap/DrawArc...）
- CATPrintParameters 统一控制打印参数
- CATIPrintable 是"可打印"的契约接口