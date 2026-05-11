#!/usr/bin/env python3
"""
CATIA CAA V5 知识库简单修复脚本
直接修复常见的格式问题
"""
import re
from pathlib import Path

def fix_use_case_docs():
    """修复Use-Case文档中的问题"""
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
            
            # 1. 修复 source_file 路径 - 使用正斜杠
            content = re.sub(
                r'source_file:\s*"([^"]+)"',
                lambda m: f'source_file: "{m.group(1).replace(chr(92), "/")}"',
                content
            )
            
            # 2. 移除错误的 ```vbscript```vbscript 配对
            content = re.sub(r'```vbscript\n```vbscript', '```vbscript', content)
            
            # 3. 移除单独的 ```vbscript``` 标签（没有配对的）
            # 先处理连续的
            lines = content.split('\n')
            new_lines = []
            i = 0
            while i < len(lines):
                line = lines[i]
                # 检测孤立的开始标签
                if line.strip() == '```vbscript':
                    # 检查前后
                    prev_line = new_lines[-1].strip() if new_lines else ''
                    next_line = lines[i+1].strip() if i+1 < len(lines) else ''
                    
                    # 如果前后都是普通文本行（不是代码），跳过这个标签
                    if (prev_line and not prev_line.startswith("'") and
                        not prev_line.startswith('Set ') and
                        not prev_line.startswith('Dim ') and
                        not prev_line.startswith('CATIA.') and
                        not prev_line.startswith('Err.') and
                        not prev_line.startswith('If ') and
                        not prev_line.startswith('For ') and
                        next_line and
                        not next_line.startswith("'") and
                        not next_line.startswith('Set ') and
                        not next_line.startswith('Dim ') and
                        not next_line.startswith('CATIA.') and
                        not next_line.startswith('Err.') and
                        not next_line.startswith('If ') and
                        not next_line.startswith('For ')):
                        i += 1
                        continue
                
                new_lines.append(line)
                i += 1
            
            content = '\n'.join(new_lines)
            
            # 4. 清理连续的空行
            content = re.sub(r'\n{3,}', '\n\n', content)
            
            # 5. 清理HTML表格残留
            lines = content.split('\n')
            new_lines = []
            skip_separator = False
            
            for i, line in enumerate(lines):
                stripped = line.strip()
                
                # 检测空单列表格
                if re.match(r'^(\|\s*)+$', stripped):
                    new_lines.append(line)
                    continue
                
                # 检测纯分隔符行
                if re.match(r'^\|?\s*[-=]+\s*\|', stripped):
                    # 如果前一行是空单列表格，跳过分隔符
                    if new_lines and re.match(r'^(\|\s*)+$', new_lines[-1].strip()):
                        continue
                    new_lines.append(line)
                    continue
                
                new_lines.append(line)
            
            content = '\n'.join(new_lines)
            
            if content != original:
                with open(md_file, 'w', encoding='utf-8') as f:
                    f.write(content)
                fixed_count += 1
                
        except Exception as e:
            print(f"Error processing {md_file}: {e}")
    
    print(f"修复了 {fixed_count} 个 Use-Case 文档")

def main():
    print("=" * 60)
    print("CATIA CAA V5 知识库简单修复")
    print("=" * 60)
    
    fix_use_case_docs()
    
    print("\n" + "=" * 60)
    print("修复完成!")
    print("=" * 60)

if __name__ == '__main__':
    main()
