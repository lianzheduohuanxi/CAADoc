#!/usr/bin/env python3
"""解析TIE文件，构建接口→实现映射"""
import re, os, sys, json
sys.stdout.reconfigure(encoding='utf-8')

tie_data = []
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
        tie_data.append({
            'interface': iface_name, 'module': module,
            'includes': includes, 'cpp_files': cpp_files
        })

print(f'Total TIE files: {len(tie_data)}')

md = '---\ntitle: "TIE文件索引 (接口绑定映射)"\ntype: "quick-reference"\nverified: true\n---\n\n'
md += f'# TIE文件索引\n\n共 {len(tie_data)} 个TIE绑定。\n\n'

by_mod = {}
for t in tie_data:
    by_mod.setdefault(t['module'], []).append(t)

for mod, ties in sorted(by_mod.items()):
    md += f'## {mod}\n\n| 接口 | 头文件 | 实现文件 |\n|------|--------|----------|\n'
    for t in ties:
        inc = ', '.join(t['includes'][:2])
        cpps = ', '.join(t['cpp_files'][:3])
        md += f'| {t["interface"]} | {inc} | {cpps} |\n'
    md += '\n'

with open('CAAKnowledge/quick-refs/tie-index.md', 'w', encoding='utf-8') as f:
    f.write(md)
with open('CAAKnowledge/data/tie_bindings.json', 'w', encoding='utf-8') as f:
    json.dump(tie_data, f, ensure_ascii=False, indent=2)
print('Done')
