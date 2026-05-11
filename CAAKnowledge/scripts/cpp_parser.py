#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
CATIA CAA V5 知识库蒸馏 - C++源码解析器 (Windows兼容版)
支持 CATDeclareInterface 格式的接口声明
"""

import os
import re
import json
from pathlib import Path
from collections import defaultdict

class CAAcppParser:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"
        
        self.stats = {
            'files_scanned': 0,
            'interfaces_found': 0,
            'classes_found': 0,
            'qi_paths_found': 0,
            'by_module': {}
        }
        
        self.knowledge = {
            'interfaces': {},
            'classes': {},
            'qi_paths': [],
            'includes': defaultdict(list)
        }
        
    def extract_module_name(self, filepath):
        parts = str(filepath).replace('\\', '/').split('/')
        for part in parts:
            if part.endswith('.edu'):
                return part.replace('.edu', '')
        return "unknown"
    
    def process_file(self, filepath):
        filepath_str = str(filepath)
        
        if not os.path.isfile(filepath):
            return True
            
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            module = self.extract_module_name(filepath_str)
            
            if filepath_str.endswith('.h') or filepath_str.endswith('.hpp') or filepath_str.endswith('.H'):
                self.process_header(content, filepath_str, module)
            
            elif filepath_str.endswith('.cpp') or filepath_str.endswith('.cxx') or filepath_str.endswith('.m'):
                self.process_source(content, filepath_str, module)
            
            self.stats['files_scanned'] += 1
            return True
            
        except Exception as e:
            return False
    
    def process_header(self, content, filepath, module):
        # 匹配 CAA 接口格式:
        # class [ExportMacro] InterfaceName : public BaseInterface { ... CATDeclareInterface; ... }
        # 或者
        # interface InterfaceName : public BaseInterface { ... }
        
        # 模式1: class ExportedByXXX InterfaceName : public BaseInterface
        interface_pattern1 = re.compile(
            r'class\s+\w+\s+(\w+)\s*:\s*public\s+(\w+)\s*\{([^}]+(?:\{[^}]*\}[^}]*)*)\}',
            re.MULTILINE | re.DOTALL
        )
        
        # 模式2: interface InterfaceName : public BaseInterface
        interface_pattern2 = re.compile(
            r'^interface\s+(\w+)\s*:\s*public\s+(\w+)\s*\{([^}]+(?:\{[^}]*\}[^}]*)*)\}',
            re.MULTILINE | re.DOTALL
        )
        
        for pattern in [interface_pattern1, interface_pattern2]:
            for match in pattern.finditer(content):
                if match.lastindex == 3:
                    iface_name = match.group(1)
                    base_iface = match.group(2)
                    body = match.group(3)
                    
                    methods = []
                    # 匹配 virtual 返回类型 方法名(参数) const = 0;
                    method_pattern = re.compile(
                        r'virtual\s+([\w:]+)\s+([\w:]+)\s*\(([^)]*)\)\s*(const)?\s*(?:=\s*0)?\s*;',
                        re.MULTILINE
                    )
                    
                    for m_match in method_pattern.finditer(body):
                        methods.append({
                            'name': m_match.group(2),
                            'return_type': m_match.group(1),
                            'parameters': m_match.group(3).strip(),
                            'is_const': bool(m_match.group(4))
                        })
                    
                    # 避免重复添加
                    if methods and iface_name not in self.knowledge['interfaces']:
                        self.knowledge['interfaces'][iface_name] = {
                            'name': iface_name,
                            'base': base_iface,
                            'module': module,
                            'methods': methods,
                            'source_file': filepath,
                            'method_count': len(methods)
                        }
                        self.stats['interfaces_found'] += 1
        
        # 提取 #include 依赖
        includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)
        caa_includes = [inc for inc in includes if inc.startswith('CAT') or inc.startswith('CAA')]
        if caa_includes:
            self.knowledge['includes'][module].extend(caa_includes)
    
    def process_source(self, content, filepath, module):
        # 提取 QueryInterface 实现
        qi_pattern = re.compile(
            r'STMETHODIMP\s+(\w+)::QueryInterface\s*\([^)]+\)\s*\{([^}]*(?:\{[^}]*\}[^}]*)*)\}',
            re.MULTILINE | re.DOTALL
        )
        
        for match in qi_pattern.finditer(content):
            class_name = match.group(1)
            body = match.group(2)
            
            supported = re.findall(r'CATI\w+', body)
            if 'CATBaseUnknown' in body:
                supported.append('CATBaseUnknown')
            
            if supported:
                self.knowledge['qi_paths'].append({
                    'from': class_name,
                    'to_interfaces': list(set(supported)),
                    'module': module,
                    'source_file': filepath
                })
                self.stats['qi_paths_found'] += 1
        
        # 提取 TIE 包含
        tie_pattern = re.compile(r'#include\s+"TIE_(\w+)\.tsrc"')
        for match in tie_pattern.finditer(content):
            self.knowledge['qi_paths'].append({
                'type': 'TIE',
                'interface': match.group(1),
                'module': module,
                'source_file': filepath
            })
            self.stats['qi_paths_found'] += 1
    
    def process_module(self, module_path):
        module_path = Path(module_path)
        
        for ext in ['*.h', '*.hpp', '*.H', '*.cpp', '*.cxx', '*.m']:
            for filepath in module_path.rglob(ext):
                if not filepath.is_file():
                    continue
                if 'PrivateInterfaces' in str(filepath):
                    continue
                self.process_file(filepath)
    
    def generate_api_reference(self):
        output_dir = self.output_base / "api-reference" / "interfaces"
        output_dir.mkdir(parents=True, exist_ok=True)
        
        count = 0
        for iface_name, data in self.knowledge['interfaces'].items():
            md = f'''---
title: "{iface_name}"
type: "interface"
module: "{data['module']}"
base: "{data['base']}"
source_file: "{data['source_file']}"
method_count: {data['method_count']}
---

# {iface_name}

**基类**: {data['base']}  
**模块**: {data['module']}  
**方法数**: {data['method_count']}

## 方法列表

'''
            for m in data['methods']:
                const = " const" if m['is_const'] else ""
                md += f'''### {m['name']}
```cpp
{m['return_type']} {m['name']}({m['parameters']}){const};
```

'''
            
            try:
                safe_name = iface_name.replace('/', '_').replace('\\', '_')
                with open(output_dir / f"{safe_name}.md", 'w', encoding='utf-8') as f:
                    f.write(md)
                count += 1
            except Exception as e:
                pass
        
        print(f"Generated {count} interface references")
    
    def generate_qi_index(self):
        output_dir = self.output_base / "quick-refs" / "qi-paths"
        output_dir.mkdir(parents=True, exist_ok=True)
        
        by_module = defaultdict(list)
        for qi in self.knowledge['qi_paths']:
            by_module[qi['module']].append(qi)
        
        md = '''---
title: "QueryInterface 路径索引"
type: "quick-reference"
---

# QueryInterface 路径索引

'''
        
        for module, paths in sorted(by_module.items()):
            md += f'\n## {module}\n\n'
            for qi in paths:
                if qi.get('from'):
                    md += f"- `{qi['from']}` → {', '.join(qi['to_interfaces'])}\n"
                elif qi.get('interface'):
                    md += f"- TIE: {qi['interface']}\n"
        
        with open(output_dir / "index.md", 'w', encoding='utf-8') as f:
            f.write(md)
        
        print(f"Generated QI index with {len(self.knowledge['qi_paths'])} paths")
    
    def save_knowledge_base(self):
        output_file = self.output_base / "data" / "knowledge_base.json"
        output_file.parent.mkdir(parents=True, exist_ok=True)
        
        knowledge = {
            'interfaces': dict(self.knowledge['interfaces']),
            'classes': dict(self.knowledge['classes']),
            'qi_paths': self.knowledge['qi_paths'],
            'includes': dict(self.knowledge['includes']),
            'stats': self.stats
        }
        
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(knowledge, f, ensure_ascii=False, indent=2)
        
        print(f"Saved to {output_file}")
    
    def run(self):
        print("=" * 60)
        print("CATIA CAA V5 知识库蒸馏 - C++源码解析")
        print("=" * 60)
        
        # P0 + P1 + P2 + P3 全部模块
        modules = [
            # P0
            'CAAApplicationFrame.edu',
            'CAADialog.edu',
            'CAAObjectModelerBase.edu',
            'CAAProductStructure.edu',
            # P1
            'CAAGeometricObjects.edu',
            'CAATopologicalObjects.edu',
            'CAATopologicalOperators.edu',
            'CAASketcherInterfaces.edu',
            'CAAGSMInterfaces.edu',
            # P2
            'CAAAssemblyUI.edu',
            'CAADraftingInterfaces.edu',
            'CAADrafting2DLInterfaces.edu',
            'CAAManufacturingItf.edu',
            'CAAPrismaticMachiningItf.edu',
            'CAASurfaceMachiningItf.edu',
            'CAAElecHarnessItf.edu',
            'CAAElecRoutingItf.edu',
            'CAAElecSchematicItf.edu',
            'CAAAnalysisInterfaces.edu',
            'CAAKinematicsInterfaces.edu',
            'CAAVisualization.edu',
            'CAAMechanicalModeler.edu',
            'CAASimulationInterfaces.edu',
            'CAABatchInfrastructure.edu',
            # P3
            'CAAAdvancedMathematics.edu',
            'CAAOptimizationInterfaces.edu',
            'CAAxPDMInterfaces.edu',
            'CAACATPDMReconcile.edu',
            'CAACollabDesignItf.edu',
            'CAAXMLParser.edu',
            'CAACATIAV4Interfaces.edu',
            'CAAAdvancedTopologicalOpe.edu',
            'CAAKnowHow.edu',
        ]
        
        for module in modules:
            path = self.base_dir / module
            if path.exists():
                print(f">>> Processing {module}...")
                self.process_module(path)
        
        self.generate_api_reference()
        self.generate_qi_index()
        self.save_knowledge_base()
        
        print("\n" + "=" * 60)
        print(f"扫描文件: {self.stats['files_scanned']}")
        print(f"发现接口: {self.stats['interfaces_found']}")
        print(f"发现类: {self.stats['classes_found']}")
        print(f"发现QI路径: {self.stats['qi_paths_found']}")
        print("=" * 60)


if __name__ == "__main__":
    import sys
    base_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    parser = CAAcppParser(base_dir)
    parser.run()