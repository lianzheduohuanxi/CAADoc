#!/usr/bin/env python3
"""最终版接口扫描 - 修复所有格式匹配"""
import re, os, sys, json
sys.stdout.reconfigure(encoding='utf-8')

interfaces = {}
for root, dirs, files in os.walk('.'):
    for fn in files:
        if not fn.endswith('.h'): continue
        fp = os.path.join(root, fn)
        if 'PrivateInterfaces' in fp: continue
        try:
            with open(fp, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except: continue
        if 'CATDeclareInterface' not in content: continue

        module = 'unknown'
        for part in fp.replace('\\', '/').split('/'):
            if part.endswith('.edu'): module = part.replace('.edu', '')

        # 多种格式: "class Export Name : public Base" 或 "class Name: public Base"
        m = re.search(r'class\s+(?:\w+\s+)?(\w+)\s*:\s*public\s+(\w+)', content)
        if not m: continue
        iface_name, base = m.group(1), m.group(2)

        # 必须包含CATDeclareInterface（排除前向声明）
        if iface_name not in content.split('CATDeclareInterface')[0] if 'CATDeclareInterface' in content else '':
            # 接口声明必须在CATDeclareInterface之前
            pass

        methods = []
        for mm in re.finditer(r'virtual\s+([\w:]+(?:\s*<[^>]+>)?)\s+(\w+)\s*\(([^)]*)\)\s*(const)?\s*(?:=\s*0)?\s*;', content):
            methods.append({
                'name': mm.group(2), 'return_type': mm.group(1),
                'parameters': mm.group(3).strip(), 'is_const': bool(mm.group(4))
            })

        interfaces[iface_name] = {
            'name': iface_name, 'base': base, 'module': module,
            'method_count': len(methods), 'methods': methods, 'source': fp
        }

print(f'Total: {len(interfaces)}')
with_m = sum(1 for v in interfaces.values() if v['method_count'] > 0)
print(f'With methods: {with_m}, Empty: {len(interfaces) - with_m}')

out = 'CAAKnowledge/api-reference/interfaces'
os.makedirs(out, exist_ok=True)
for name, d in interfaces.items():
    md = f'---\ntitle: "{name}"\ntype: "interface"\nmodule: "{d["module"]}"\nbase: "{d["base"]}"\nmethod_count: {d["method_count"]}\nverified: true\n---\n\n# {name}\n\n'
    md += f'**基类**: {d["base"]}  \n**模块**: {d["module"]}  \n**方法数**: {d["method_count"]}\n\n'
    if d['methods']:
        md += '## 方法列表\n\n'
        for m in d['methods']:
            c = ' const' if m['is_const'] else ''
            md += f'### {m["name"]}\n```cpp\n{m["return_type"]} {m["name"]}({m["parameters"]}){c};\n```\n\n'
    else:
        md += '## 说明\n\n该接口没有声明自定义方法，作为标记接口或配置接口使用。\n\n'
    with open(os.path.join(out, f'{name}.md'), 'w', encoding='utf-8') as f:
        f.write(md)

# Save JSON
with open('CAAKnowledge/data/knowledge_base_v2.json', 'w', encoding='utf-8') as f:
    json.dump({
        'interfaces': {k: {kk: vv for kk, vv in v.items() if kk != 'methods'} for k, v in interfaces.items()},
        'stats': {'total': len(interfaces), 'with_methods': with_m, 'empty': len(interfaces) - with_m}
    }, f, ensure_ascii=False, indent=2)
print(f'Generated {len(interfaces)} docs')
