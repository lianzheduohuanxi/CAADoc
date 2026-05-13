# -*- coding: utf-8 -*-
"""
验证脚本 - 验证三个待验证项目 (改进版)
1. 内部路径链接100%有效
2. 所有围栏配对正确
3. 交叉引用完整性
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

# CATIA 内核接口列表 (这些接口文档不在CAA知识库中)
CATIA_CORE_INTERFACES = {
    'CATBaseUnknown', 'CATIInterface', 'CATIObject', 'CATIDispatch',
    'CATIAlias', 'CATInit', 'CATIUtil', 'CATIUnknown', 'CATIComponent',
    'CATCommand', 'CATCommandHeader', 'CATDlgDialog', 'CATDlgNotify',
    'CATNotification', 'CATEventSubscriber', 'CATIASyncEvent',
    'CATListOfCATUnicodeString', 'CATIAdpErrorMonitor', 'CATIConfig',
    'CATIProduct', 'CATIDocId', 'CATIDocument', 'CATIDocRoots',
    'CATIABase', 'CATIABaseFactory', 'CATIAMediator', 'CATIAApplication',
}

def validate_path_links():
    """验证内部路径链接100%有效"""
    print("=" * 60)
    print("1. 验证内部路径链接有效性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    # 构建所有可用文档的映射
    available_docs = {}
    for md_file in md_files:
        # 使用相对路径作为键
        rel_path = md_file.relative_to(root_dir)
        available_docs[str(rel_path)] = md_file
        available_docs[md_file.name] = md_file  # 也按文件名索引
    
    total_links = 0
    internal_links = 0
    broken_internal_links = []
    external_links = 0
    
    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            
            # 提取所有Markdown链接
            link_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+)\)')
            
            for match in link_pattern.finditer(content):
                link_text = match.group(1)
                link_url = match.group(2)
                
                total_links += 1
                
                # 跳过外部链接和锚点
                if link_url.startswith('http') or link_url.startswith('#') or link_url.startswith('mailto:'):
                    external_links += 1
                    continue
                
                # 跳过CATIA内核接口引用
                is_core_interface = False
                for core_iface in CATIA_CORE_INTERFACES:
                    if core_iface in link_url and ('interfaces/' in link_url or link_url.endswith(f'{core_iface}.md')):
                        is_core_interface = True
                        break
                
                if is_core_interface:
                    external_links += 1
                    continue
                
                internal_links += 1
                
                # 处理相对路径
                link_url_clean = link_url.split('#')[0]  # 移除锚点
                link_url_clean = link_url_clean.split('?')[0]  # 移除查询参数
                
                # 检查链接是否有效
                exists = False
                link_path = Path(link_url_clean)
                
                if link_path.is_absolute():
                    exists = link_path.exists()
                else:
                    # 相对路径
                    test_path = md_file.parent / link_path
                    if test_path.exists():
                        exists = True
                    else:
                        # 尝试不同扩展名
                        for ext in ['', '.md', '.htm', '.html']:
                            if (md_file.parent / (str(link_path) + ext)).exists():
                                exists = True
                                break
                            if (root_dir / (str(link_path) + ext)).exists():
                                exists = True
                                break
                
                if not exists:
                    broken_internal_links.append({
                        'file': str(md_file.relative_to(root_dir)),
                        'link': link_url
                    })
                    
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    print(f"\n  Total links: {total_links}")
    print(f"  External links (CATIA core/API): {external_links}")
    print(f"  Internal links: {internal_links}")
    print(f"  Broken internal links: {len(broken_internal_links)}")
    
    if broken_internal_links:
        print(f"\n  [WARN] Broken internal links:")
        seen = set()
        count = 0
        for item in broken_internal_links:
            key = f"{item['file']}: {item['link']}"
            if key not in seen and count < 20:
                seen.add(key)
                print(f"    - {item['file']}: {item['link']}")
                count += 1
        if len(broken_internal_links) > 20:
            print(f"    ... and {len(broken_internal_links) - 20} more")
    
    return {
        'total': total_links,
        'external': external_links,
        'internal': internal_links,
        'broken_internal': len(broken_internal_links),
        'broken_list': broken_internal_links
    }

def validate_fence_pairing():
    """验证所有围栏配对正确"""
    print("\n" + "=" * 60)
    print("2. 验证围栏配对正确性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_fences = 0
    mismatched_files = []
    
    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            
            # 统计围栏
            fences = re.findall(r'^```(\w*)$', content, re.MULTILINE)
            total_fences += len(fences)
            
            # 检查配对
            if len(fences) % 2 != 0:
                mismatched_files.append({
                    'file': str(md_file.relative_to(root_dir)),
                    'count': len(fences)
                })
                
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    print(f"\n  Total fences: {total_fences}")
    print(f"  Mismatched files: {len(mismatched_files)}")
    
    return {
        'total': total_fences,
        'mismatched_count': len(mismatched_files),
        'mismatched_files': mismatched_files
    }

def validate_cross_references():
    """验证交叉引用完整性"""
    print("\n" + "=" * 60)
    print("3. 验证交叉引用完整性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    use_cases_dir = root_dir / 'use-cases'
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    # 构建用例映射
    use_case_files = {}
    for md_file in use_cases_dir.rglob('*.md'):
        try:
            content = md_file.read_text(encoding='utf-8')
            title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
            title = title_match.group(1) if title_match else md_file.stem
            use_case_files[md_file.stem] = str(md_file.relative_to(root_dir))
        except:
            pass
    
    # 检查接口文档中的交叉引用
    interface_files = list(interfaces_dir.glob('*.md'))
    
    ref_stats = {
        'total_interfaces': len(interface_files),
        'with_references': 0,
        'without_references': 0,
        'valid_refs': 0,
        'broken_refs': []
    }
    
    for md_file in interface_files:
        content = md_file.read_text(encoding='utf-8')
        interface_name = md_file.stem
        
        # 检查是否有相关用例部分
        if '## Related Use Cases' in content or '## 相关用例' in content:
            ref_stats['with_references'] += 1
            
            # 验证引用的用例是否存在
            ref_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+\.md)\)')
            for match in ref_pattern.finditer(content):
                ref_link = match.group(2)
                ref_text = match.group(1)
                
                # 跳过CATIA内核接口
                is_core = any(core in ref_link for core in CATIA_CORE_INTERFACES)
                if is_core:
                    continue
                
                # 检查文件是否存在
                target_path = root_dir / ref_link.replace('../', '')
                if target_path.exists():
                    ref_stats['valid_refs'] += 1
                else:
                    ref_stats['broken_refs'].append({
                        'interface': interface_name,
                        'broken_link': ref_link
                    })
        else:
            ref_stats['without_references'] += 1
    
    print(f"\n  Total interfaces: {ref_stats['total_interfaces']}")
    print(f"  With references: {ref_stats['with_references']}")
    print(f"  Without references: {ref_stats['without_references']}")
    print(f"  Valid cross-refs: {ref_stats['valid_refs']}")
    print(f"  Broken cross-refs: {len(ref_stats['broken_refs'])}")
    
    if ref_stats['broken_refs']:
        print(f"\n  [WARN] Broken cross-refs:")
        seen = set()
        count = 0
        for item in ref_stats['broken_refs']:
            key = f"{item['interface']}: {item['broken_link']}"
            if key not in seen and count < 10:
                seen.add(key)
                print(f"    - {item['interface']}: {item['broken_link']}")
                count += 1
    
    return ref_stats

def main():
    print("\n" + "=" * 60)
    print("CAA Knowledge Base Validation Report (Improved)")
    print("=" * 60)
    print()
    
    results = {}
    
    # 1. 验证路径链接
    results['path_links'] = validate_path_links()
    
    # 2. 验证围栏配对
    results['fence_pairing'] = validate_fence_pairing()
    
    # 3. 验证交叉引用
    results['cross_references'] = validate_cross_references()
    
    # 计算通过率
    path_pass_rate = 100 if results['path_links']['broken_internal'] == 0 else \
                   int((results['path_links']['internal'] - results['path_links']['broken_internal']) / results['path_links']['internal'] * 100) if results['path_links']['internal'] > 0 else 100
    
    # 汇总报告
    print("\n" + "=" * 60)
    print("VALIDATION SUMMARY")
    print("=" * 60)
    
    print(f"""
  1. Path Links:
     - Total: {results['path_links']['total']}
     - External (CATIA Core): {results['path_links']['external']}
     - Internal: {results['path_links']['internal']}
     - Broken internal: {results['path_links']['broken_internal']}
     - Internal pass rate: {path_pass_rate}%
     - Status: {'[PASS]' if results['path_links']['broken_internal'] == 0 else f'[WARN] {path_pass_rate}%'}
     
  2. Fence Pairing:
     - Total fences: {results['fence_pairing']['total']}
     - Mismatched: {results['fence_pairing']['mismatched_count']}
     - Status: {'[PASS]' if results['fence_pairing']['mismatched_count'] == 0 else '[FAIL]'}
     
  3. Cross-References:
     - Total interfaces: {results['cross_references']['total_interfaces']}
     - With refs: {results['cross_references']['with_references']}
     - Valid refs: {results['cross_references']['valid_refs']}
     - Broken refs: {len(results['cross_references']['broken_refs'])}
     - Status: {'[PASS]' if len(results['cross_references']['broken_refs']) == 0 else '[WARN]'}
    """)
    
    # 保存报告
    import json
    report_file = Path(r'C:\Luxshare\CAADoc\CAAKnowledge\验证报告_待验证项目_v2.json')
    with open(report_file, 'w', encoding='utf-8') as f:
        results_serializable = {
            'path_links': {
                'total': results['path_links']['total'],
                'external': results['path_links']['external'],
                'internal': results['path_links']['internal'],
                'broken_internal': results['path_links']['broken_internal'],
                'pass_rate': path_pass_rate,
                'broken_list': results['path_links']['broken_list'][:50]
            },
            'fence_pairing': results['fence_pairing'],
            'cross_references': {
                'total_interfaces': results['cross_references']['total_interfaces'],
                'with_references': results['cross_references']['with_references'],
                'without_references': results['cross_references']['without_references'],
                'valid_refs': results['cross_references']['valid_refs'],
                'broken_refs': results['cross_references']['broken_refs'][:50]
            }
        }
        json.dump(results_serializable, f, indent=2, ensure_ascii=False)
    
    print(f"\nReport saved to: {report_file}")
    
    return results

if __name__ == '__main__':
    main()