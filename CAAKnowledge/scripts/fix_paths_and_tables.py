#!/usr/bin/env python3
"""
CATIA CAA V5 知识库修复脚本
修复文档中的路径引用和HTML表格残留问题
"""
import re
import os
from pathlib import Path

def fix_use_case_docs():
    """修复Use-Case文档中的路径和表格问题"""
    use_case_dir = Path('CAAKnowledge/use-cases')
    if not use_case_dir.exists():
        print(f"目录不存在: {use_case_dir}")
        return
    
    # 构建目录映射：源目录 -> 目标目录
    dir_mapping = {}
    for src_dir in use_case_dir.rglob('*'):
        if src_dir.is_dir():
            src_name = src_dir.name.lower()
            # 标准化目录名
            parts = src_name.split('cases')
            if len(parts) == 2:
                normalized = parts[0].rstrip('c') + 'cases'
                dir_mapping[src_name] = normalized
    
    fixed_count = 0
    
    for md_file in use_case_dir.rglob('*.md'):
        try:
            with open(md_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
            
            original = content
            file_path_str = str(md_file)
            
            # 1. 修复反斜杠路径
            # Doc\online\xxx\yyy.htm -> Doc/online/xxx/yyy.htm
            content = re.sub(r'source_file:\s*"Doc\\([^"]+)"', 
                           lambda m: f'source_file: "Doc/{m.group(1).replace(chr(92), "/")}"', 
                           content)
            content = re.sub(r'([a-zA-Z]):\\', lambda m: m.group(1) + '/', content)
            
            # 2. 修复 ../ 相对路径引用
            # 图片路径: ../CAAScrBase/images/xxx.gif -> 相对路径保留，但标准化
            # 链接路径: ../CAAScdAniTechArticles/xxx.htm -> 转换为 .md
            content = re.sub(
                r'\.\./([A-Za-z]+)/(images?/[^"\'\s]+)',
                r'../\1/\2',
                content
            )
            
            # 3. 修复 .htm 链接 -> .md
            content = re.sub(
                r'\.htm(?=["\'\s\)])',
                '.md',
                content
            )
            
            # 4. 修复HTML表格残留
            # 将单列表格行转换为更好的格式
            content = fix_table_rows(content)
            
            # 5. 修复代码块（确保围栏正确）
            content = fix_code_fences(content)
            
            if content != original:
                with open(md_file, 'w', encoding='utf-8') as f:
                    f.write(content)
                fixed_count += 1
                
        except Exception as e:
            print(f"Error processing {md_file}: {e}")
    
    print(f"修复了 {fixed_count} 个 Use-Case 文档")

def fix_table_rows(content):
    """修复HTML表格残留，转换为更好的格式"""
    lines = content.split('\n')
    result = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # 检测表格分隔线行: |---|---|
        if re.match(r'^\|?\s*-+?\s*\|', line) or re.match(r'^\|?\s*=+\s*\|', line):
            # 这是一个表格分隔行
            # 检查前一行是否是单列表格
            if len(result) > 0:
                prev = result[-1]
                if re.match(r'^\|\s*$', prev) or re.match(r'^\|\s*\|?\s*$', prev):
                    # 前一行是空的单列表格，移除它
                    result.pop()
                    i += 1
                    continue
            
            result.append(line)
            i += 1
            continue
        
        # 检测空的单列表格行: | 
        if re.match(r'^\|\s*$', line):
            # 检查上下文
            if i > 0 and i < len(lines) - 1:
                prev_line = lines[i-1] if i > 0 else ''
                next_line = lines[i+1] if i < len(lines) - 1 else ''
                
                # 如果前后都是表格相关行，可能是HTML残留
                if '|' in prev_line or '|' in next_line:
                    i += 1
                    continue
            result.append(line)
            i += 1
            continue
        
        # 检测只有分隔符的表格: |--- 或 |===
        if re.match(r'^\|?\s*={3,}\s*\|?\s*$', line):
            i += 1
            continue
        
        # 检测包含图片但格式奇怪的行
        if '![' in line and '|' in line:
            # 可能是图标+内容的表格，尝试修复
            parts = line.split('|')
            if len(parts) >= 2:
                # 保留图片和主要内容
                fixed_line = '|'.join([p for p in parts if p.strip() and not re.match(r'^\s*!?\[.*\]\(', p)])
                if fixed_line.strip() != '|':
                    result.append(fixed_line)
                    i += 1
                    continue
        
        result.append(line)
        i += 1
    
    return '\n'.join(result)

def fix_code_fences(content):
    """确保代码块有正确的围栏"""
    lines = content.split('\n')
    result = []
    in_code = False
    code_lines = []
    
    for line in lines:
        stripped = line.strip()
        
        # 检测代码开始（VBScript特征）
        if not in_code:
            if (stripped.startswith("'") or 
                re.match(r"^\s*(Set |Dim |CATIA\.|Err\.|If \(|For |While |Do |Select |Next |End If)", stripped) or
                re.match(r"^\s*[a-zA-Z_]\w*\s*=\s*", stripped)):
                
                # 检查是否是连续代码行
                if stripped and not stripped.startswith('#') and not stripped.startswith('**') and '```' not in stripped:
                    # 检查是否应该开始代码块
                    if (re.match(r"^\s*(Set |Dim |CATIA\.|Err\.)", stripped) or
                        stripped.startswith("' ___")):
                        in_code = True
                        code_lines = [line]
                        continue
        
        if in_code:
            # 检查代码是否结束
            if (stripped.startswith('---') or 
                stripped.startswith('**') or 
                stripped.startswith('## ') or
                stripped.startswith('# ') or
                (stripped and not stripped.startswith("'") and 
                 not re.match(r"^\s*(Set |Dim |CATIA\.|Err\.|If |For |While |Do |Select |Next |End )", stripped) and
                 not re.match(r"^\s*[a-zA-Z_]\w*\s*=\s*", stripped) and
                 not re.match(r"^\s*\(?", stripped))):
                
                # 写入代码块
                if code_lines:
                    result.append('```vbscript')
                    result.extend(code_lines)
                    result.append('```')
                    result.append('')
                in_code = False
                result.append(line)
            else:
                code_lines.append(line)
        else:
            result.append(line)
    
    # 处理未关闭的代码块
    if in_code and code_lines:
        result.append('```vbscript')
        result.extend(code_lines)
        result.append('```')
    
    return '\n'.join(result)

def fix_api_changes_docs():
    """修复API变更文档，添加版本字段"""
    api_changes_dir = Path('CAAKnowledge/use-cases')
    if not api_changes_dir.exists():
        return
    
    version_patterns = [
        (r'caacenapichangesr7', 'V5R7'),
        (r'caacenapichangesr8', 'V5R8'),
        (r'caacenapichangesr9', 'V5R9'),
        (r'caacenapichangesr10', 'V5R10'),
        (r'caacenapichangesr11', 'V5R11'),
        (r'caacenapichangesr12', 'V5R12'),
        (r'caacenapichangesr13', 'V5R13'),
        (r'caacenapichangesr14', 'V5R14'),
        (r'caacenapichangesr15', 'V5R15'),
        (r'caacenapichangesr16', 'V5R16'),
        (r'caacenapichangesr17', 'V5R17'),
        (r'caacenapichangesr18', 'V5R18'),
        (r'caacenapichangesr19', 'V5R19'),
        (r'caacenapichangesr20', 'V5R20'),
        (r'caacenapichangesr21', 'V5R21'),
        (r'caacenapichangesr22', 'V5R22'),
        (r'caacenapichangesr23', 'V5R23'),
        (r'caacenapichangesr24', 'V5R24'),
        (r'caacenapichangesr25', 'V5R25'),
        (r'caacenapichangesr26', 'V5R26'),
        (r'caacenapichangesr27', 'V5R27'),
        (r'caacenapichanges$', 'V5Base'),
    ]
    
    fixed = 0
    for pattern, version in version_patterns:
        for md_file in api_changes_dir.rglob(f'{pattern}/*.md'):
            try:
                with open(md_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                
                if 'version:' in content:
                    continue
                
                # 在frontmatter的module行后添加version
                if re.search(r'^module:', content, re.MULTILINE):
                    content = re.sub(
                        r'^(module:.*)$',
                        rf'\1\nversion: "{version}"',
                        content,
                        flags=re.MULTILINE,
                        count=1
                    )
                    
                    with open(md_file, 'w', encoding='utf-8') as f:
                        f.write(content)
                    fixed += 1
                    
            except Exception as e:
                pass
    
    print(f"修复了 {fixed} 个 API 变更文档的版本字段")

def normalize_directory_names():
    """规范化目录命名"""
    use_case_dir = Path('CAAKnowledge/use-cases')
    if not use_case_dir.exists():
        return
    
    renamed = 0
    for dir_path in use_case_dir.rglob('*'):
        if dir_path.is_dir():
            name = dir_path.name
            # 检查是否需要规范化
            # 例如: caascdpstcases -> caascdpstcases (已经是统一格式)
            # 但 caascdanicases 可能需要检查
            
            # 统一规则：全部小写，无前缀c
            new_name = name.lower()
            
            if name != new_name:
                new_path = dir_path.parent / new_name
                try:
                    if not new_path.exists():
                        os.rename(str(dir_path), str(new_path))
                        renamed += 1
                        print(f"重命名: {dir_path.name} -> {new_name}")
                except Exception as e:
                    print(f"重命名失败 {dir_path}: {e}")
    
    print(f"规范化了 {renamed} 个目录")

def main():
    print("=" * 60)
    print("CATIA CAA V5 知识库修复脚本")
    print("=" * 60)
    
    print("\n1. 修复 Use-Case 文档中的路径和表格问题...")
    fix_use_case_docs()
    
    print("\n2. 修复 API 变更文档的版本字段...")
    fix_api_changes_docs()
    
    print("\n3. 规范化目录命名...")
    normalize_directory_names()
    
    print("\n" + "=" * 60)
    print("修复完成!")
    print("=" * 60)

if __name__ == '__main__':
    main()
