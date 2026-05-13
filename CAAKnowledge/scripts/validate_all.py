# -*- coding: utf-8 -*-
"""
验证脚本 - 验证三个待验证项目
1. 路径链接100%有效
2. 所有围栏配对正确
3. 交叉引用完整性
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def validate_path_links():
    """验证路径链接100%有效"""
    print("=" * 60)
    print("1. 验证路径链接有效性")
    print("=" * 60)
    
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_links = 0
    broken_links = []
    valid_links = []
    
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
                    valid_links.append((str(md_file.relative_to(root_dir)), link_url, 'external'))
                    continue
                
                # 处理相对路径
                if link_url.startswith('./'):
                    target_path = md_file.parent / link_url[2:]
                    target_path = Path(target_path.as_posix())
                elif link_url.startswith('../'):
                    # 计算相对路径
                    rel_depth = link_url.count('../')
                    parent = md_file.parent
                    for _ in range(rel_depth):
                        parent = parent.parent
                    target_path = parent / link_url.lstrip('../').lstrip('/')
                else:
                    target_path = md_file.parent / link_url
                
                # 检查文件是否存在
                # 尝试多种扩展名
                exists = False
                for ext in ['', '.md', '.htm', '.html']:
                    if target_path.with_suffix(ext).exists():
                        exists = True
                        break
                
                if exists:
                    valid_links.append((str(md_file.relative_to(root_dir)), link_url, 'valid'))
                else:
                    broken_links.append((str(md_file.relative_to(root_dir)), link_url))
                    
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    print(f"\n  Total links: {total_links}")
    print(f"  Valid links: {len(valid_links)}")
    print(f"  Broken links: {len(broken_links)}")
    
    if broken_links:
        print(f"\n  [WARN] Broken links found:")
        for file, link in broken_links[:20]:
            print(f"    - {file}: {link}")
        if len(broken_links) > 20:
            print(f"    ... and {len(broken_links) - 20} more")
    
    return {
        'total': total_links,
        'valid': len(valid_links),
        'broken': len(broken_links),
        'broken_list': broken_links
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
                    'count': len(fences),
                    'fences': fences
                })
                
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    print(f"\n  Total fences: {total_fences}")
    print(f"  Mismatched files: {len(mismatched_files)}")
    
    if mismatched_files:
        print(f"\n  [WARN] Mismatched fence files:")
        for item in mismatched_files[:10]:
            print(f"    - {item['file']}: {item['count']} fences (odd)")
    
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
    
    # 加载搜索索引获取所有文档
    index_file = root_dir / 'data' / 'search-index.json'
    use_cases_dir = root_dir / 'use-cases'
    
    # 获取所有用例文档
    use_case_files = {}
    for md_file in use_cases_dir.rglob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
        title = title_match.group(1) if title_match else md_file.stem
        use_case_files[str(md_file.relative_to(root_dir))] = title
    
    # 检查接口文档中的交叉引用
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    interface_files = list(interfaces_dir.glob('*.md'))
    
    ref_stats = {
        'total_interfaces': len(interface_files),
        'with_references': 0,
        'without_references': 0,
        'broken_refs': []
    }
    
    for md_file in interface_files:
        content = md_file.read_text(encoding='utf-8')
        interface_name = md_file.stem
        
        # 检查是否有相关用例部分
        if '## Related Use Cases' in content or '## 相关用例' in content or '## Related Usecases' in content:
            ref_stats['with_references'] += 1
            
            # 验证引用的用例是否存在
            ref_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+\.md)\)')
            for match in ref_pattern.finditer(content):
                ref_link = match.group(2)
                target_path = root_dir / ref_link.replace('../', '')
                
                if not target_path.exists():
                    ref_stats['broken_refs'].append({
                        'interface': interface_name,
                        'broken_link': ref_link
                    })
        else:
            ref_stats['without_references'] += 1
    
    print(f"\n  Total interfaces: {ref_stats['total_interfaces']}")
    print(f"  With references: {ref_stats['with_references']}")
    print(f"  Without references: {ref_stats['without_references']}")
    print(f"  Broken references: {len(ref_stats['broken_refs'])}")
    
    if ref_stats['broken_refs']:
        print(f"\n  [WARN] Broken references:")
        for item in ref_stats['broken_refs'][:10]:
            print(f"    - {item['interface']}: {item['broken_link']}")
    
    return ref_stats

def main():
    print("\n" + "=" * 60)
    print("CAA Knowledge Base Validation Report")
    print("=" * 60)
    print()
    
    results = {}
    
    # 1. 验证路径链接
    results['path_links'] = validate_path_links()
    
    # 2. 验证围栏配对
    results['fence_pairing'] = validate_fence_pairing()
    
    # 3. 验证交叉引用
    results['cross_references'] = validate_cross_references()
    
    # 汇总报告
    print("\n" + "=" * 60)
    print("VALIDATION SUMMARY")
    print("=" * 60)
    
    print(f"""
  1. Path Links:
     - Total: {results['path_links']['total']}
     - Valid: {results['path_links']['valid']}
     - Broken: {results['path_links']['broken']}
     - Status: {'[PASS]' if results['path_links']['broken'] == 0 else '[FAIL]'}
     
  2. Fence Pairing:
     - Total fences: {results['fence_pairing']['total']}
     - Mismatched: {results['fence_pairing']['mismatched_count']}
     - Status: {'[PASS]' if results['fence_pairing']['mismatched_count'] == 0 else '[FAIL]'}
     
  3. Cross-References:
     - Total interfaces: {results['cross_references']['total_interfaces']}
     - With refs: {results['cross_references']['with_references']}
     - Broken refs: {len(results['cross_references']['broken_refs'])}
     - Status: {'[PASS]' if len(results['cross_references']['broken_refs']) == 0 else '[FAIL]'}
    """)
    
    # 保存报告
    import json
    report_file = Path(r'C:\Luxshare\CAADoc\CAAKnowledge\验证报告_待验证项目.json')
    with open(report_file, 'w', encoding='utf-8') as f:
        # Convert Path objects to strings for JSON serialization
        results_serializable = {
            'path_links': {
                'total': results['path_links']['total'],
                'valid': results['path_links']['valid'],
                'broken': results['path_links']['broken'],
                'broken_list': results['path_links']['broken_list'][:50]  # Limit to 50
            },
            'fence_pairing': {
                'total': results['fence_pairing']['total'],
                'mismatched_count': results['fence_pairing']['mismatched_count'],
                'mismatched_files': results['fence_pairing']['mismatched_files'][:20]
            },
            'cross_references': {
                'total_interfaces': results['cross_references']['total_interfaces'],
                'with_references': results['cross_references']['with_references'],
                'without_references': results['cross_references']['without_references'],
                'broken_refs': results['cross_references']['broken_refs'][:50]
            }
        }
        json.dump(results_serializable, f, indent=2, ensure_ascii=False)
    
    print(f"\nReport saved to: {report_file}")
    
    return results

if __name__ == '__main__':
    main()