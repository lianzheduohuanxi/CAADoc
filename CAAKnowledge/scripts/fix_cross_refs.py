# -*- coding: utf-8 -*-
"""
修复接口文档中的交叉引用链接
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_interface_cross_refs():
    """修复接口文档中的交叉引用"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    use_cases_dir = root_dir / 'use-cases'
    
    # CATIA内核接口 (不在本知识库中)
    CATIA_CORE = {
        'CATBaseUnknown', 'CATIInterface', 'CATIObject', 'CATIDispatch',
        'CATCommand', 'CATCommandHeader', 'CATDlgDialog', 'CATDlgNotify',
        'CATNotification', 'CATStateCommand', 'CATMathFunctionXY',
        'CAAPspBaseEnvProtected', 'CATAfrCommandHeaderRep',
    }
    
    # 构建用例映射
    usecase_map = {}
    for md_file in use_cases_dir.rglob('*.md'):
        usecase_map[md_file.stem] = md_file
    
    fixed_count = 0
    
    print("Fixing interface cross-references...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 检查是否有 Related Use Cases 部分
        if '## Related Use Cases' not in content:
            continue
        
        lines = content.split('\n')
        new_lines = []
        skip_usecase_section = False
        
        for line in lines:
            # 开始用例部分
            if '## Related Use Cases' in line:
                skip_usecase_section = True
                new_lines.append(line)
                continue
            
            # 跳过CATIA内核接口链接
            is_core_link = False
            for core in CATIA_CORE:
                if core in line:
                    is_core_link = True
                    break
            
            if is_core_link:
                continue
            
            # 检查用例链接
            if skip_usecase_section:
                match = re.search(r'-\s+\[([^\]]+)\]\(([^)]+\.md)\)', line)
                if match:
                    usecase_name = match.group(2).replace('.md', '').replace('../use-cases/', '')
                    usecase_name = usecase_name.replace('caaafrcases/', '')
                    usecase_name = usecase_name.replace('caavistecharticles/', '')
                    usecase_name = usecase_name.replace('caadegcases/', '')
                    usecase_name = usecase_name.replace('caadegtecharticles/', '')
                    usecase_name = usecase_name.replace('caadlgtecharticles/', '')
                    usecase_name = usecase_name.replace('caadlgcases/', '')
                    
                    # 检查用例是否存在
                    if usecase_name in usecase_map:
                        # 保留有效链接
                        new_lines.append(line)
                        continue
                    else:
                        # 跳过不存在的用例
                        continue
            
            new_lines.append(line)
        
        content = '\n'.join(new_lines)
        
        # 清理空行
        content = re.sub(r'\n{3,}', '\n\n', content)
        
        # 移除空的 Related Use Cases 部分
        if '## Related Use Cases' in content:
            # 检查是否只有标题没有内容
            match = re.search(r'(## Related Use Cases\n\n)(\n|$)', content)
            if match:
                content = content.replace(match.group(0), '')
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} interface files")
    return fixed_count

def clean_interface_docs():
    """清理接口文档中的无效内容"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    fixed_count = 0
    
    print("Cleaning interface documents...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 移除无用的继承引用行
        content = re.sub(r'\*\*接口继承\*\*.*?(?=\n|$)', '', content)
        content = re.sub(r'\*\*Base Interface\*\*.*?(?=\n|$)', '', content)
        
        # 移除空的from.md链接
        content = re.sub(r'-\s+\*\*.*?\*from\.md\*.*', '', content)
        
        # 清理空行
        content = re.sub(r'\n{3,}', '\n\n', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Cleaned {fixed_count} files")
    return fixed_count

def main():
    print("=" * 60)
    print("Fixing Interface Cross-References")
    print("=" * 60)
    
    fix_interface_cross_refs()
    clean_interface_docs()
    
    print("\n[OK] Cross-references fixed!")

if __name__ == '__main__':
    main()