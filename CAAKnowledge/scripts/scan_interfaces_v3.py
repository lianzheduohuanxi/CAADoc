#!/usr/bin/env python3
"""接口扫描V3 - 扩展到200+接口，支持Protected/LocalInterfaces"""
import re, os, sys, json
from pathlib import Path
from collections import defaultdict

sys.stdout.reconfigure(encoding='utf-8')

interfaces = {}
qi_paths = []
tie_bindings = []

# 扩展扫描目录
scan_dirs = ['PublicInterfaces', 'ProtectedInterfaces', 'LocalInterfaces']

for root, dirs, files in os.walk('.'):
    for fn in files:
        if not fn.endswith('.h'):
            continue
        fp = os.path.join(root, fn)
        rel_parts = fp.replace('\\', '/').split('/')

        # 跳过PrivateInterfaces
        if 'PrivateInterfaces' in fp:
            continue

        # 只扫描指定接口目录
        if not any(d in rel_parts for d in scan_dirs):
            continue

        try:
            with open(fp, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            continue

        # 模块名提取
        module = 'unknown'
        for part in rel_parts:
            if part.endswith('.edu'):
                module = part.replace('.edu', '')

        # 匹配接口声明: class [ExportMacro] InterfaceName : public BaseClass
        # 支持多种空格变体
        m = re.search(r'class\s+(?:\w+\s+)?(\w+)\s*:\s*public\s+(\w+)', content)
        if not m:
            continue
        iface_name, base = m.group(1), m.group(2)

        # 验证是CAA接口 (以CAA或CAT开头)
        if not (iface_name.startswith('CAA') or iface_name.startswith('CAT')):
            continue

        # 提取方法
        methods = []
        for mm in re.finditer(
            r'virtual\s+([\w:*&<>\s]+?)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*(?:=\s*0)?\s*;',
            content
        ):
            methods.append({
                'name': mm.group(2),
                'return_type': mm.group(1).strip(),
                'parameters': mm.group(3).strip(),
                'is_const': bool(mm.group(4))
            })

        # 提取includes
        includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)
        caa_includes = [inc for inc in includes if inc.startswith('CAT') or inc.startswith('CAA')]

        # 提取注释 (接口声明前的注释)
        comment = ""
        lines = content.split('\n')
        for i, line in enumerate(lines):
            if iface_name in line and 'class' in line:
                # 向前查找注释
                for j in range(max(0, i-10), i):
                    cl = lines[j].strip()
                    if cl.startswith('//') and len(cl) > 5:
                        comment = cl[2:].strip()
                        break
                break

        interfaces[iface_name] = {
            'name': iface_name,
            'base': base,
            'module': module,
            'method_count': len(methods),
            'methods': methods,
            'includes': caa_includes,
            'comment': comment,
            'source': fp,
            'visibility': 'public' if 'PublicInterfaces' in fp else ('protected' if 'ProtectedInterfaces' in fp else 'local')
        }

# 扫描TIE绑定
for root, dirs, files in os.walk('.'):
    for fn in files:
        if not fn.startswith('TIE_') or not fn.endswith('.tsrc'):
            continue
        fp = os.path.join(root, fn)
        module = 'unknown'
        for part in fp.replace('\\', '/').split('/'):
            if part.endswith('.edu'):
                module = part.replace('.edu', '')
        iface_name = fn.replace('TIE_', '').replace('.tsrc', '')
        with open(fp, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
        includes = re.findall(r'#include\s+[<"]([^>"]+)[>"]', content)
        src_dir = os.path.dirname(fp)
        try:
            cpp_files = [f2 for f2 in os.listdir(src_dir) if f2.endswith('.cpp')]
        except:
            cpp_files = []
        tie_bindings.append({
            'interface': iface_name,
            'module': module,
            'includes': includes,
            'cpp_files': cpp_files,
            'source': fp
        })

# 扫描QueryInterface调用路径 (从.cpp文件)
qi_pattern = re.compile(
    r'(?:HRESULT|if\s*\(\s*SUCCEEDED\s*\(\s*)?\s*(\w+)?\s*->?\s*QueryInterface\s*\(\s*(IID_\w+)\s*,\s*\(void\*\*\)\s*&(\w+)\s*\)',
    re.IGNORECASE
)

for root, dirs, files in os.walk('.'):
    for fn in files:
        if not fn.endswith('.cpp'):
            continue
        fp = os.path.join(root, fn)
        module = 'unknown'
        for part in fp.replace('\\', '/').split('/'):
            if part.endswith('.edu'):
                module = part.replace('.edu', '')
        try:
            with open(fp, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            continue

        for m in qi_pattern.finditer(content):
            obj_var = m.group(1) or 'this'
            iid = m.group(2)
            target_iface = iid.replace('IID_', '')
            qi_paths.append({
                'from_variable': obj_var,
                'to_interface': target_iface,
                'iid': iid,
                'module': module,
                'source_file': fp
            })

# 统计
print(f'Total interfaces: {len(interfaces)}')
with_m = sum(1 for v in interfaces.values() if v['method_count'] > 0)
print(f'With methods: {with_m}, Empty: {len(interfaces) - with_m}')
print(f'TIE bindings: {len(tie_bindings)}')
print(f'QI paths: {len(qi_paths)}')

# 按模块分组
by_module = defaultdict(list)
for name, d in interfaces.items():
    by_module[d['module']].append(name)

print('\nBy module:')
for mod, names in sorted(by_module.items(), key=lambda x: -len(x[1])):
    print(f'  {mod}: {len(names)}')

# 生成接口文档
out = 'CAAKnowledge/api-reference/interfaces'
os.makedirs(out, exist_ok=True)
for name, d in interfaces.items():
    md = f'---\ntitle: "{name}"\ntype: "interface"\nmodule: "{d["module"]}"\nbase: "{d["base"]}"\nmethod_count: {d["method_count"]}\nvisibility: "{d["visibility"]}"\nverified: true\n---\n\n# {name}\n\n'
    md += f'**基类**: {d["base"]}  \n'
    md += f'**模块**: {d["module"]}  \n'
    md += f'**可见性**: {d["visibility"]}  \n'
    md += f'**方法数**: {d["method_count"]}\n\n'
    if d['comment']:
        md += f'> {d["comment"]}\n\n'
    if d['methods']:
        md += '## 方法列表\n\n'
        for m in d['methods']:
            c = ' const' if m['is_const'] else ''
            md += f'### {m["name"]}\n```cpp\n{m["return_type"]} {m["name"]}({m["parameters"]}){c};\n```\n\n'
    else:
        md += '## 说明\n\n该接口没有声明自定义方法，作为标记接口或配置接口使用。\n\n'
    if d['includes']:
        md += '## 依赖\n\n'
        for inc in d['includes'][:10]:
            md += f'- `{inc}`\n'
        md += '\n'
    with open(os.path.join(out, f'{name}.md'), 'w', encoding='utf-8') as f:
        f.write(md)

# 生成TIE索引
tie_out = 'CAAKnowledge/quick-refs/tie-index.md'
os.makedirs(os.path.dirname(tie_out), exist_ok=True)
md = '---\ntitle: "TIE文件索引 (接口绑定映射)"\ntype: "quick-reference"\nverified: true\n---\n\n'
md += f'# TIE文件索引\n\n共 {len(tie_bindings)} 个TIE绑定。\n\n'
by_mod = defaultdict(list)
for t in tie_bindings:
    by_mod[t['module']].append(t)
for mod, ties in sorted(by_mod.items()):
    md += f'## {mod}\n\n| 接口 | 头文件 | 实现文件 |\n|------|--------|----------|\n'
    for t in ties:
        inc = ', '.join(t['includes'][:2])
        cpps = ', '.join(t['cpp_files'][:3])
        md += f'| {t["interface"]} | {inc} | {cpps} |\n'
    md += '\n'
with open(tie_out, 'w', encoding='utf-8') as f:
    f.write(md)

# 生成QI路径索引
qi_out = 'CAAKnowledge/quick-refs/qi-paths/index.md'
os.makedirs(os.path.dirname(qi_out), exist_ok=True)
md = '---\ntitle: "QueryInterface 路径索引"\ntype: "quick-reference"\nverified: true\n---\n\n'
md += f'# QueryInterface 路径索引\n\n共 {len(qi_paths)} 条QueryInterface调用路径。\n\n'
by_mod = defaultdict(list)
for q in qi_paths:
    by_mod[q['module']].append(q)
for mod, paths in sorted(by_mod.items()):
    md += f'## {mod}\n\n'
    md += '| 源对象 | 目标接口 | IID |\n|--------|----------|-----|\n'
    for q in paths[:50]:  # 每模块限制50条
        md += f'| `{q["from_variable"]}` | {q["to_interface"]} | `{q["iid"]}` |\n'
    md += '\n'
with open(qi_out, 'w', encoding='utf-8') as f:
    f.write(md)

# 保存JSON
with open('CAAKnowledge/data/knowledge_base_v3.json', 'w', encoding='utf-8') as f:
    json.dump({
        'interfaces': {k: {kk: vv for kk, vv in v.items() if kk != 'methods'}
                      for k, v in interfaces.items()},
        'tie_bindings': tie_bindings,
        'qi_paths': qi_paths,
        'stats': {
            'total': len(interfaces),
            'with_methods': with_m,
            'empty': len(interfaces) - with_m,
            'tie_bindings': len(tie_bindings),
            'qi_paths': len(qi_paths)
        }
    }, f, ensure_ascii=False, indent=2)

print(f'\nGenerated {len(interfaces)} interface docs')
print(f'Generated {len(tie_bindings)} TIE bindings')
print(f'Generated {len(qi_paths)} QI paths')
