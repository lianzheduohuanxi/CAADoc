#!/usr/bin/env python3
"""
CATIA CAA V5 Use-Case 文档清理脚本 v2
智能检测连续代码块并添加围栏
"""
import re
from pathlib import Path

def is_code_line(line):
    """检测是否是代码行"""
    if not line:
        return False
    
    stripped = line.strip()
    
    # 跳过非代码行
    if stripped.startswith('#'):
        return False
    if stripped.startswith('**'):
        return False
    if stripped.startswith('>'):
        return False
    if stripped.startswith('- ['):
        return False
    if stripped == '':
        return False
    if stripped == '---':
        return False
    if '|' in stripped and stripped.count('|') > 2:
        return False  # 可能是表格行
    if stripped.startswith('!['):
        return False  # 图片
    
    # VBScript特征
    if stripped.startswith("'"):
        return True
    if re.match(r"^\s*Set\s+\w+", stripped, re.I):
        return True
    if re.match(r"^\s*Dim\s+\w+", stripped, re.I):
        return True
    if re.match(r"^\s*If\s+", stripped, re.I):
        return True
    if re.match(r"^\s*End\s+(If|Sub|Function|For|While|Select)", stripped, re.I):
        return True
    if re.match(r"^\s*For\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Next\s*$", stripped, re.I):
        return True
    if re.match(r"^\s*While\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Do\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Err\.", stripped, re.I):
        return True
    if re.match(r"^\s*CATIA\.", stripped, re.I):
        return True
    if re.match(r"^\s*Then\s*$", stripped, re.I):
        return True
    if re.match(r"^\s*\w+\s*=\s*.+\(", stripped):
        return True
    if re.match(r"^\s*\w+\.\w+\s*=", stripped):
        return True
    if re.match(r"^\s*public\s+", stripped, re.I):
        return True
    if re.match(r"^\s*private\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Select\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Case\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Sub\s+", stripped, re.I):
        return True
    if re.match(r"^\s*Function\s+", stripped, re.I):
        return True
    
    return False

def cleanup_file(filepath):
    """清理单个文件"""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except:
        return False
    
    original = content
    
    # 1. 分离 frontmatter
    frontmatter = ''
    body = content
    
    if content.startswith('---'):
        end_idx = content.find('\n---\n', 4)
        if end_idx != -1:
            frontmatter = content[:end_idx + 5]
            body = content[end_idx + 5:]
    
    # 2. 清理空行
    lines = body.split('\n')
    new_lines = []
    for line in lines:
        line = line.rstrip()
        new_lines.append(line)
    body = '\n'.join(new_lines)
    
    # 3. 合并连续代码块
    body = merge_code_blocks(body)
    
    # 4. 清理多余空行
    lines = body.split('\n')
    new_lines = []
    prev_empty = False
    for line in lines:
        is_empty = not line.strip()
        if is_empty:
            if not prev_empty:
                new_lines.append('')
                prev_empty = True
        else:
            new_lines.append(line)
            prev_empty = False
    body = '\n'.join(new_lines).strip() + '\n'
    
    content = frontmatter + body
    
    if content != original:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        return True
    return False

def merge_code_blocks(content):
    """合并连续的代码行并添加围栏"""
    lines = content.split('\n')
    result = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        
        # 检测代码行
        if is_code_line(stripped):
            # 开始收集代码块
            code_lines = []
            j = i
            
            # 收集连续代码行
            while j < len(lines):
                code_line = lines[j].strip()
                if is_code_line(code_line):
                    code_lines.append(lines[j])
                    j += 1
                elif code_line == '':
                    # 空行在代码中
                    code_lines.append(lines[j])
                    j += 1
                else:
                    break
            
            # 如果有足够的代码行，添加围栏
            if len(code_lines) >= 2:
                result.append('```vbscript')
                result.extend(code_lines)
                result.append('```')
                result.append('')
            else:
                # 代码行太少，不添加围栏
                result.extend(code_lines)
            
            i = j
        else:
            result.append(line)
            i += 1
    
    return '\n'.join(result)

def run():
    """运行清理"""
    base_dir = Path('CAAKnowledge/use-cases')
    if not base_dir.exists():
        print(f"目录不存在: {base_dir}")
        return
    
    print("=" * 60)
    print("CATIA CAA V5 Use-Case 文档清理 v2")
    print("=" * 60)
    
    fixed = 0
    total = 0
    
    for md_file in base_dir.rglob('*.md'):
        total += 1
        if cleanup_file(md_file):
            fixed += 1
    
    print(f"处理文件: {total}")
    print(f"修复文件: {fixed}")
    print("=" * 60)

if __name__ == '__main__':
    run()
