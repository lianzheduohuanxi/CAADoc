# -*- coding: utf-8 -*-
"""
修复接口文档中的use-case链接
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_interface_usecase_links():
    """修复接口文档中的use-case链接"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    use_cases_dir = root_dir / 'use-cases'
    
    # 构建所有可用用例的映射 (按不同目录)
    usecase_files = {}
    for md_file in use_cases_dir.rglob('*.md'):
        # 按完整相对路径
        rel_path = str(md_file.relative_to(root_dir))
        usecase_files[rel_path] = md_file
        # 按文件名
        usecase_files[md_file.name] = md_file
        # 按去掉前缀的名称
        name = md_file.name.replace('.md', '')
        usecase_files[name] = md_file
    
    print(f"Available use-case files: {len(usecase_files)}")
    
    fixed_count = 0
    
    print("Fixing use-case links in interface documents...")
    
    for md_file in interfaces_dir.glob('*.md'):
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 查找所有 ../use-cases/... 链接
        def fix_usecase_link(match):
            link_url = match.group(1)
            
            # 提取文件名
            filename = link_url.split('/')[-1]
            filename = filename.split('\\')[-1]
            
            # 检查是否存在
            if filename in usecase_files:
                # 文件存在，保留相对路径
                return match.group(0)
            else:
                # 文件不存在，查找可能的替代
                # 去掉目录前缀尝试
                base_name = filename.replace('.md', '')
                
                # 在所有可能的位置查找
                for key, path in usecase_files.items():
                    if path.name.replace('.md', '') == base_name:
                        # 找到替代路径
                        rel_path = str(path.relative_to(root_dir))
                        # 计算正确的相对路径
                        interface_dir = md_file.parent
                        try:
                            new_rel = str(path.relative_to(interface_dir))
                            return f'](../{new_rel})'
                        except:
                            return f']({rel_path})'
                
                # 找不到，删除链接
                return ''
        
        # 修复 ../use-cases/ 链接
        content = re.sub(r'\]\(([^)]*use-cases/[^)]+\.md)\)', fix_usecase_link, content)
        
        # 修复反斜杠
        content = content.replace('\\', '/')
        
        # 清理空链接和空行
        content = re.sub(r'\]\(\s*\)', '](#)', content)
        content = re.sub(r'\n{3,}', '\n\n', content)
        
        # 清理空的 Related Use Cases 部分
        if '## Related Use Cases' in content:
            # 检查后续是否有有效内容
            section_match = re.search(r'## Related Use Cases\n+(.+?)(?=\n##|\Z)', content, re.DOTALL)
            if section_match:
                section_content = section_match.group(1).strip()
                if not section_content or section_content == '\n' * section_content.count('\n'):
                    # 内容为空或只有空行，移除整个部分
                    content = content.replace(section_match.group(0), '')
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Fixed {fixed_count} interface files")
    return fixed_count

def normalize_all_paths():
    """标准化所有文档的路径"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    fixed_count = 0
    
    print("Normalizing all paths...")
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        original = content
        
        # 修复反斜杠
        content = content.replace('\\', '/')
        
        # 修复多重 ../
        content = re.sub(r'\.\./\.\./', '../', content)
        
        if content != original:
            md_file.write_text(content, encoding='utf-8')
            fixed_count += 1
    
    print(f"  Normalized {fixed_count} files")
    return fixed_count

def main():
    print("=" * 60)
    print("Final Link Fix")
    print("=" * 60)
    
    fix_interface_usecase_links()
    normalize_all_paths()
    
    print("\n[OK] Links fixed!")

if __name__ == '__main__':
    main()