# -*- coding: utf-8 -*-
"""
验证脚本 - 验证三个待验证项目 (最终版)
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

# CATIA 内核接口列表
CATIA_CORE_INTERFACES = {
    'CATBaseUnknown', 'CATIInterface', 'CATIObject', 'CATIDispatch',
    'CATIAlias', 'CATInit', 'CATIUtil', 'CATIUnknown', 'CATIComponent',
    'CATCommand', 'CATCommandHeader', 'CATDlgDialog', 'CATDlgNotify',
    'CATNotification', 'CATStateCommand', 'CATMathFunctionXY',
    'CAAPspBaseEnvProtected', 'CATAfrCommandHeaderRep',
}

def validate_path_links():
    """验证路径链接"""
    print("=" * 60)
    print("1. 验证路径链接有效性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_links = 0
    broken_links = []
    
    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            link_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+)\)')
            
            for match in link_pattern.finditer(content):
                link_url = match.group(2)
                total_links += 1
                
                # 跳过外部链接和锚点
                if link_url.startswith('http') or link_url.startswith('#') or link_url.startswith('mailto:'):
                    continue
                
                # 跳过CATIA内核接口
                is_core = any(core in link_url for core in CATIA_CORE_INTERFACES)
                if is_core and ('interfaces/' in link_url or link_url.endswith(f'{core}.md')):
                    continue
                
                # 解析相对路径
                # 处理 ../
                parts = link_url.split('/')
                resolved_path = md_file.parent
                
                for part in parts:
                    if part == '..':
                        resolved_path = resolved_path.parent
                    elif part and part != '.':
                        resolved_path = resolved_path / part
                
                # 移除锚点和查询参数
                resolved_path = Path(str(resolved_path).split('#')[0].split('?')[0])
                
                # 检查是否存在
                exists = False
                if resolved_path.exists():
                    exists = True
                else:
                    # 尝试添加扩展名
                    for ext in ['.md', '.htm', '.html']:
                        if resolved_path.with_suffix(ext).exists():
                            exists = True
                            break
                
                if not exists:
                    broken_links.append({
                        'file': str(md_file.relative_to(root_dir)),
                        'link': link_url,
                        'resolved': str(resolved_path)
                    })
                    
        except Exception as e:
            pass
    
    print(f"\n  Total links: {total_links}")
    print(f"  Broken links: {len(broken_links)}")
    
    if broken_links:
        seen = set()
        count = 0
        print(f"\n  [WARN] Sample broken links:")
        for item in broken_links:
            key = item['link']
            if key not in seen and count < 15:
                seen.add(key)
                print(f"    - {item['link']}")
                count += 1
    
    return {'total': total_links, 'broken': len(broken_links), 'broken_list': broken_links}

def validate_fence_pairing():
    """验证围栏配对"""
    print("\n" + "=" * 60)
    print("2. 验证围栏配对正确性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_fences = 0
    mismatched = []
    
    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            fences = re.findall(r'^```(\w*)$', content, re.MULTILINE)
            total_fences += len(fences)
            
            if len(fences) % 2 != 0:
                mismatched.append(str(md_file.relative_to(root_dir)))
        except:
            pass
    
    print(f"\n  Total fences: {total_fences}")
    print(f"  Mismatched files: {len(mismatched)}")
    
    return {'total': total_fences, 'mismatched_count': len(mismatched), 'mismatched': mismatched}

def validate_cross_references():
    """验证交叉引用"""
    print("\n" + "=" * 60)
    print("3. 验证交叉引用完整性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    use_cases_dir = root_dir / 'use-cases'
    
    # 构建用例文件映射
    usecase_files = {}
    for md_file in use_cases_dir.rglob('*.md'):
        usecase_files[str(md_file.relative_to(root_dir))] = md_file
        usecase_files[md_file.name] = md_file
    
    broken_refs = []
    valid_refs = 0
    with_refs = 0
    without_refs = 0
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        
        if '## Related Use Cases' in content:
            with_refs += 1
            
            # 检查用例链接
            ref_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+\.md)\)')
            for match in ref_pattern.finditer(content):
                link_url = match.group(2)
                
                # 跳过CATIA内核接口
                if any(core in link_url for core in CATIA_CORE_INTERFACES):
                    continue
                
                # 解析路径
                parts = link_url.split('/')
                resolved_path = md_file.parent
                for part in parts:
                    if part == '..':
                        resolved_path = resolved_path.parent
                    elif part and part != '.':
                        resolved_path = resolved_path / part
                
                if resolved_path.exists():
                    valid_refs += 1
                else:
                    broken_refs.append({
                        'interface': md_file.stem,
                        'link': link_url
                    })
        else:
            without_refs += 1
    
    print(f"\n  Total interfaces: {len(list(interfaces_dir.glob('*.md')))}")
    print(f"  With references: {with_refs}")
    print(f"  Without references: {without_refs}")
    print(f"  Valid refs: {valid_refs}")
    print(f"  Broken refs: {len(broken_refs)}")
    
    if broken_refs:
        seen = set()
        count = 0
        print(f"\n  [WARN] Sample broken cross-refs:")
        for item in broken_refs:
            key = item['link']
            if key not in seen and count < 10:
                seen.add(key)
                print(f"    - {item['interface']}: {item['link']}")
                count += 1
    
    return {
        'with_refs': with_refs,
        'without_refs': without_refs,
        'valid_refs': valid_refs,
        'broken_refs': len(broken_refs)
    }

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    
    print("\n" + "=" * 60)
    print("CAA Knowledge Base Final Validation")
    print("=" * 60)
    print()
    
    path_result = validate_path_links()
    fence_result = validate_fence_pairing()
    ref_result = validate_cross_references()
    
    print("\n" + "=" * 60)
    print("FINAL VALIDATION SUMMARY")
    print("=" * 60)
    
    path_rate = 100 if path_result['broken'] == 0 else int((path_result['total'] - path_result['broken']) / path_result['total'] * 100)
    
    print(f"""
  1. Path Links:
     - Total: {path_result['total']}
     - Broken: {path_result['broken']}
     - Pass rate: {path_rate}%
     - Status: {'[PASS]' if path_result['broken'] == 0 else f'[WARN] {path_rate}%'}
     
  2. Fence Pairing:
     - Total fences: {fence_result['total']}
     - Mismatched: {fence_result['mismatched_count']}
     - Status: {'[PASS]' if fence_result['mismatched_count'] == 0 else '[FAIL]'}
     
  3. Cross-References:
     - With refs: {ref_result['with_refs']}
     - Without refs: {ref_result['without_refs']}
     - Valid refs: {ref_result['valid_refs']}
     - Broken refs: {ref_result['broken_refs']}
     - Status: {'[PASS]' if ref_result['broken_refs'] == 0 else '[WARN]'}
    """)
    
    # 保存报告
    import json
    report_file = root_dir / '验证报告_最终版.json'
    with open(report_file, 'w', encoding='utf-8') as f:
        json.dump({
            'timestamp': '2026-05-12',
            'path_links': path_result,
            'fence_pairing': fence_result,
            'cross_references': ref_result,
            'overall_pass': path_result['broken'] == 0 and fence_result['mismatched_count'] == 0 and ref_result['broken_refs'] == 0
        }, f, indent=2, ensure_ascii=False)
    
    print(f"Report saved to: {report_file}")

if __name__ == '__main__':
    main()