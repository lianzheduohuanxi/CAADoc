# -*- coding: utf-8 -*-
"""
生成交叉引用 - P2-2
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def extract_interface_references(content):
    """从文档中提取接口引用"""
    interfaces = re.findall(r'`(CATI[A-Z][a-zA-Z0-9]+)`', content)
    interfaces += re.findall(r'\*\*(CATI[A-Z][a-zA-Z0-9]+)\*\*', content)
    return list(set(interfaces))

def find_usecases_using_interface(interface_name, root_dir):
    """查找使用特定接口的用例"""
    use_cases_dir = root_dir / 'use-cases'
    results = []
    
    if not use_cases_dir.exists():
        return results
    
    for md_file in use_cases_dir.rglob('*.md'):
        try:
            content = md_file.read_text(encoding='utf-8')
            if interface_name in content:
                title_match = re.search(r'^#\s+(.+)$', content, re.MULTILINE)
                title = title_match.group(1) if title_match else md_file.stem
                path = str(md_file.relative_to(root_dir))
                results.append({'title': title, 'path': path})
        except:
            pass
    
    return results

def generate_cross_references():
    """生成交叉引用"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    
    print("P2-2: Generating Cross-References")
    print("=" * 50)
    
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    if not interfaces_dir.exists():
        print("Error: interfaces directory not found")
        return
    
    interface_files = list(interfaces_dir.glob('*.md'))
    print(f"Processing {len(interface_files)} interface documents...")
    
    modified_count = 0
    
    for md_file in interface_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            
            # 提取接口名
            interface_name = md_file.stem
            
            # 查找相关用例
            related_usecases = find_usecases_using_interface(interface_name, root_dir)
            
            # 去重
            seen = set()
            unique_usecases = []
            for uc in related_usecases:
                if uc['path'] not in seen:
                    seen.add(uc['path'])
                    unique_usecases.append(uc)
            
            # 添加交叉引用
            if unique_usecases and '## Related Use Cases' not in content:
                refs_section = "\n\n---\n\n## Related Use Cases\n\n"
                for uc in unique_usecases[:5]:
                    refs_section += f"- [{uc['title']}](../{uc['path']})\n"
                
                content = content.rstrip() + refs_section
                md_file.write_text(content, encoding='utf-8')
                modified_count += 1
                
        except Exception as e:
            print(f"  Warning: Error processing {md_file}: {e}")
    
    print(f"\n[OK] Cross-references generated!")
    print(f"   - Enhanced interfaces: {modified_count}")

if __name__ == '__main__':
    generate_cross_references()