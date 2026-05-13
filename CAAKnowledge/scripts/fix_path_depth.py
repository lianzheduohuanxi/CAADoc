# -*- coding: utf-8 -*-
"""
修复接口文档到用例文档的相对路径
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_interface_to_usecase_paths():
    """修复接口文档到用例文档的路径"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    use_cases_dir = root_dir / 'use-cases'
    
    # 构建用例文件映射
    usecase_files = {}
    for md_file in use_cases_dir.rglob('*.md'):
        rel_path = str(md_file.relative_to(root_dir))
        usecase_files[rel_path] = md_file
        usecase_files[md_file.name] = md_file
    
    fixed_count = 0
    fixed_links = 0
    
    print("Fixing interface to use-case paths...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 查找 ../use-cases/ 链接
        def fix_link(match):
            global fixed_links
            full_link = match.group(0)
            link_url = match.group(1)
            
            # 计算正确路径
            # 接口文档在 api-reference/interfaces/
            # 用例在 use-cases/*/
            # 需要 ../../use-cases/...
            
            # 提取相对路径部分
            rel_path = link_url.replace('../use-cases/', '')
            
            # 在用例映射中查找
            for key, path in usecase_files.items():
                if path.name == rel_path or path.name == rel_path + '.md':
                    # 找到文件，计算正确相对路径
                    try:
                        correct_rel = str(path.relative_to(md_file.parent))
                        fixed_links += 1
                        return f']({correct_rel})'
                    except:
                        pass
            
            # 尝试其他可能位置
            for key, path in usecase_files.items():
                if rel_path in key or key.endswith(rel_path):
                    try:
                        correct_rel = str(path.relative_to(md_file.parent))
                        fixed_links += 1
                        return f']({correct_rel})'
                    except:
                        pass
            
            return full_link
        
        # 替换 ../use-cases/ 开头的链接
        content = re.sub(r'\]\(\.\./use-cases/([^)]+\.md)\)', fix_link, content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} files")
    print(f"  Fixed {fixed_links} links")
    return fixed_count, fixed_links

def main():
    print("=" * 60)
    print("Fixing Interface to Use-Case Paths")
    print("=" * 60)
    
    fix_interface_to_usecase_paths()
    
    print("\n[OK] Paths fixed!")

if __name__ == '__main__':
    main()