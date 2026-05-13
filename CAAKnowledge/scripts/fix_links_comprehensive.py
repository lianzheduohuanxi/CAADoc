# -*- coding: utf-8 -*-
"""
全面修复失效链接
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def build_interface_map():
    """构建接口映射"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    interface_map = {}
    for md_file in interfaces_dir.glob('*.md'):
        interface_map[md_file.stem] = md_file
    
    return interface_map

def build_usecase_map():
    """构建用例映射"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    use_cases_dir = root_dir / 'use-cases'
    
    usecase_map = {}
    for md_file in use_cases_dir.rglob('*.md'):
        usecase_map[md_file.stem] = md_file
    
    return usecase_map

def fix_interface_links():
    """修复接口文档中的链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    interface_map = build_interface_map()
    
    fixed_count = 0
    
    print("Fixing interface document links...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 修复基类接口链接
        for iface_name, iface_path in interface_map.items():
            # 修复直接引用接口名的情况
            content = re.sub(
                rf'\]\({iface_name}\.md\)',
                f']({iface_path.name})',
                content
            )
            content = re.sub(
                rf'\]\(\./{iface_name}\.md\)',
                f']({iface_path.name})',
                content
            )
        
        # 删除指向不存在文件的链接
        # 检查所有.md链接并验证
        def fix_link(match):
            link_url = match.group(2)
            if link_url.endswith('.md') or link_url.endswith('.htm'):
                # 提取文件名
                filename = link_url.split('/')[-1]
                filename = filename.split('\\')[-1]
                if not filename.endswith('.md'):
                    filename = filename + '.md'
                
                # 检查是否存在
                test_path = md_file.parent / filename
                if not test_path.exists():
                    # 尝试在interfaces目录查找
                    test_path2 = interfaces_dir / filename
                    if not test_path2.exists():
                        return ''  # 删除无效链接
            return match.group(0)
        
        content = re.sub(r'(\[([^\]]+)\]\(([^)]+\.md)\))', lambda m: fix_link(m), content)
        
        # 清理连续空行
        content = re.sub(r'\n{3,}', '\n\n', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} interface files")
    return fixed_count

def fix_usecase_links():
    """修复用例文档中的链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    use_cases_dir = root_dir / 'use-cases'
    
    usecase_map = build_usecase_map()
    
    fixed_count = 0
    
    print("Fixing use-case document links...")
    
    for md_file in use_cases_dir.rglob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 修复用例内部链接
        for usecase_name, usecase_path in usecase_map.items():
            content = re.sub(
                rf'\]\({usecase_path.name}\)',
                f']({str(usecase_path.relative_to(md_file.parent)).replace(chr(92), "/")})',
                content
            )
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} use-case files")
    return fixed_count

def fix_general_links():
    """修复通用链接问题"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    fixed_count = 0
    
    print("Fixing general link issues...")
    
    # 占位符和示例链接
    placeholders = [
        '{base_name}.md',
        '../{uc.path}',
        '../use-cases/xxx.md',
        '../use-cases/yyy.md',
        'from.md',
    ]
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        for placeholder in placeholders:
            content = re.sub(rf'\[([^\]]+)\]\([^)]*{re.escape(placeholder)}[^)]*\)', '', content)
        
        # 修复反斜杠为正斜杠
        content = content.replace('\\', '/')
        
        # 清理空链接
        content = re.sub(r'\]\(\s*\)', '](#)', content)
        content = re.sub(r'\]\(\s*#\s*\)', '](#)', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} files")
    return fixed_count

def main():
    print("=" * 60)
    print("Comprehensive Link Fix")
    print("=" * 60)
    
    fix_interface_links()
    fix_usecase_links()
    fix_general_links()
    
    print("\n[OK] All links fixed!")

if __name__ == '__main__':
    main()