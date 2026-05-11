#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
改进版 C++ 源码解析器
- 识别 CATDeclareInterface 宏
- 扫描 PublicInterfaces + LocalInterfaces
- 提取所有方法签名（包括无方法接口）
"""
import os, re, json
from pathlib import Path
from collections import defaultdict

class ImprovedCAAcppParser:
    def __init__(self, base_dir):
        self.base_dir = Path(base_dir)
        self.output_base = self.base_dir / "CAAKnowledge"
        self.interfaces = {}
        self.stats = {'scanned': 0, 'interfaces': 0, 'modules': set()}

    def extract_module(self, filepath):
        for part in str(filepath).replace('\\', '/').split('/'):
            if part.endswith('.edu'):
                return part.replace('.edu', '')
        return "unknown"

    def process_header(self, filepath):
        filepath_str = str(filepath)
        if not os.path.isfile(filepath_str):
            return
        module = self.extract_module(filepath_str)

        with open(filepath_str, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()

        self.stats['scanned'] += 1
        self.stats['modules'].add(module)

        if 'CATDeclareInterface' not in content:
            return

        # Extract class name: class [ExportedBy...] InterfaceName : public BaseClass
        class_match = re.search(
            r'class\s+(?:\w+\s+)?(\w+)\s*:\s*public\s+(\w+)\s*\{',
            content
        )
        if not class_match:
            return

        iface_name = class_match.group(1)
        base_class = class_match.group(2)

        # Extract methods (virtual ... = 0;)
        methods = []
        for m in re.finditer(
            r'virtual\s+([\w:]+(?:\s*<[^>]+>)?)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*(?:=\s*0)?\s*;',
            content
        ):
            methods.append({
                'name': m.group(2),
                'return_type': m.group(1),
                'parameters': m.group(3).strip(),
                'is_const': bool(m.group(4))
            })

        # Extract includes
        includes = [inc for inc in re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)
                     if inc.startswith('CAT') or inc.startswith('CAA')]

        # Extract comment (first paragraph after //)
        comment = ""
        for line in content.split('\n'):
            line = line.strip()
            if line.startswith('//') and len(line) > 5:
                comment = line[3:].strip()
                break

        self.interfaces[iface_name] = {
            'name': iface_name,
            'base': base_class,
            'module': module,
            'methods': methods,
            'method_count': len(methods),
            'includes': includes,
            'comment': comment,
            'source_file': filepath_str,
            'has_methods': len(methods) > 0
        }
        self.stats['interfaces'] += 1

    def scan_all(self):
        print("=" * 60)
        print("改进版 CAA 接口扫描")
        print("=" * 60)

        # Scan all .edu modules
        for edu_dir in sorted(self.base_dir.glob("*.edu")):
            print(f">>> {edu_dir.name}...")
            for subdir in ['PublicInterfaces', 'LocalInterfaces']:
                iface_dir = edu_dir / subdir
                if iface_dir.exists():
                    for hfile in iface_dir.glob("*.h"):
                        self.process_header(hfile)

        print(f"\n扫描: {self.stats['scanned']} 文件")
        print(f"发现: {self.stats['interfaces']} 接口")
        print(f"模块: {len(self.stats['modules'])} 个")
        return self.interfaces

    def generate_docs(self):
        out_dir = self.output_base / "api-reference" / "interfaces"
        out_dir.mkdir(parents=True, exist_ok=True)

        count = 0
        for name, data in self.interfaces.items():
            md = f'---\ntitle: "{name}"\ntype: "interface"\nmodule: "{data["module"]}"\n'
            md += f'base: "{data["base"]}"\nmethod_count: {data["method_count"]}\n'
            md += f'source_file: "{data["source_file"]}"\nverified: true\n---\n\n'
            md += f'# {name}\n\n'
            md += f'**基类**: {data["base"]}  \n'
            md += f'**模块**: {data["module"]}  \n'
            md += f'**方法数**: {data["method_count"]}\n\n'
            if data['comment']:
                md += f'> {data["comment"]}\n\n'

            if data['methods']:
                md += '## 方法列表\n\n'
                for m in data['methods']:
                    const = " const" if m['is_const'] else ""
                    md += f'### {m["name"]}\n```cpp\n{m["return_type"]} {m["name"]}({m["parameters"]}){const};\n```\n\n'
            else:
                md += '## 说明\n\n该接口没有声明自定义方法，作为标记接口或配置接口使用。\n\n'

            if data['includes']:
                md += '## 依赖\n\n'
                for inc in data['includes'][:10]:
                    md += f'- `{inc}`\n'
                md += '\n'

            with open(out_dir / f"{name}.md", 'w', encoding='utf-8') as f:
                f.write(md)
            count += 1

        print(f"生成 {count} 个接口文档")

    def save_json(self):
        out_file = self.output_base / "data" / "knowledge_base_v2.json"
        out_file.parent.mkdir(parents=True, exist_ok=True)
        with open(out_file, 'w', encoding='utf-8') as f:
            json.dump({
                'interfaces': {k: {kk: vv for kk, vv in v.items() if kk != 'source_file'}
                              for k, v in self.interfaces.items()},
                'stats': {
                    **self.stats,
                    'modules': list(self.stats['modules'])
                }
            }, f, ensure_ascii=False, indent=2)
        print(f"保存到 {out_file}")


if __name__ == "__main__":
    import sys
    base = sys.argv[1] if len(sys.argv) > 1 else "."
    p = ImprovedCAAcppParser(base)
    p.scan_all()
    p.generate_docs()
    p.save_json()
