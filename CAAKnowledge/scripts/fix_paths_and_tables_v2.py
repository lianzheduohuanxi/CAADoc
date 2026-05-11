#!/usr/bin/env python3
"""
CATIA CAA V5 知识库修复脚本 v2
正确修复文档中的路径引用问题
"""
import re
import os
from pathlib import Path

def fix_use_case_docs():
    """修复Use-Case文档中的路径问题"""
    use_case_dir = Path('CAAKnowledge/use-cases')
    if not use_case_dir.exists():
        print(f"目录不存在: {use_case_dir}")
        return
    
    fixed_count = 0
    
    for md_file in use_case_dir.rglob('*.md'):
        try:
            with open(md_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original = content
            
            # 1. 修复 source_file 路径 - 只修复分隔符，不改变扩展名
            # Doc\online\xxx\yyy.htm -> Doc/online/xxx/yyy.htm (保持.htm)
            content = re.sub(
                r'source_file:\s*"([^"]*\\[^"]+\.htm)"',
                lambda m: f'source_file: "{m.group(1).replace(chr(92), "/")}"',
                content
            )
            
            # 2. 修复内容中的 .md 链接（如果有的话改回 .htm）
            # 但这个情况很少见，暂时不处理
            
            # 3. 修复 ../ 相对路径
            # 保留图片路径 ../CAAScrBase/images/xxx.gif 样式不变
            # 但确保使用正斜杠
            content = re.sub(r'\.\.\\', '../', content)
            
            # 4. 修复内容中的 .htm 链接 -> .md
            # 但只在正文中，不在 source_file 中
            def replace_htm_link(match):
                prefix = match.group(1)
                htm_file = match.group(2)
                md_file = htm_file.replace('.htm', '.md')
                suffix = match.group(3)
                # 确保链接指向正确的位置
                return f'{prefix}{md_file}{suffix}'
            
            # 替换正文中的 .htm 链接
            content = re.sub(
                r'(\[.*?\])\(([^)]*)\.htm\)',
                replace_htm_link,
                content
            )
            
            # 5. 清理HTML表格残留 - 单列空表格
            content = clean_empty_table_rows(content)
            
            if content != original:
                with open(md_file, 'w', encoding='utf-8') as f:
                    f.write(content)
                fixed_count += 1
                
        except Exception as e:
            print(f"Error processing {md_file}: {e}")
    
    print(f"修复了 {fixed_count} 个 Use-Case 文档")

def clean_empty_table_rows(content):
    """清理空的单列表格行"""
    lines = content.split('\n')
    result = []
    skip_next = 0
    
    for i, line in enumerate(lines):
        if skip_next > 0:
            skip_next -= 1
            continue
        
        stripped = line.strip()
        
        # 检测空单列表格行: |  或 | 或 |  | 
        if re.match(r'^(\|\s*)+$', stripped):
            # 检查是否是连续的
            if i > 0 and re.match(r'^(\|\s*)+$', lines[i-1].strip()):
                continue  # 跳过连续的
        
        # 检测纯分隔符行: |---|---|
        if re.match(r'^\|?\s*[-=]+\s*\|', stripped):
            # 检查前一行是否是空内容
            if i > 0:
                prev_stripped = lines[i-1].strip()
                # 如果前一行是空或只有分隔符，移除
                if prev_stripped == '' or re.match(r'^\|?\s*[-=]+\s*\|', prev_stripped):
                    continue
        
        # 检测只有图标列的空表格行（后面有内容）
        # 例如: |  | 内容 或 | ![](xxx.gif) | 内容
        if re.match(r'^(\|\s*)+$', stripped) or stripped == '':
            # 检查下一行
            if i < len(lines) - 1:
                next_line = lines[i + 1].strip()
                # 如果下一行是代码或标题开头，跳过当前空行
                if (next_line.startswith("'") or 
                    next_line.startswith('#') or
                    next_line.startswith('##') or
                    next_line.startswith('####')):
                    continue
        
        result.append(line)
    
    return '\n'.join(result)

def main():
    print("=" * 60)
    print("CATIA CAA V5 知识库修复脚本 v2")
    print("=" * 60)
    
    print("\n修复 Use-Case 文档中的路径问题...")
    fix_use_case_docs()
    
    print("\n" + "=" * 60)
    print("修复完成!")
    print("=" * 60)

if __name__ == '__main__':
    main()
