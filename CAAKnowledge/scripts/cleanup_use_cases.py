#!/usr/bin/env python3
"""
CATIA CAA V5 Use-Case 文档清理脚本
清理多余的空行、缩进、修复代码块等
"""
import re
from pathlib import Path

def cleanup_file(filepath):
    """清理单个文件"""
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except:
        return False
    
    original = content
    
    # 1. 分离 frontmatter 和正文
    frontmatter = ''
    body = content
    
    if content.startswith('---'):
        end_idx = content.find('\n---\n', 4)
        if end_idx != -1:
            frontmatter = content[:end_idx + 5]
            body = content[end_idx + 5:]
    
    # 2. 清理正文中的多余空行
    lines = body.split('\n')
    new_lines = []
    prev_empty = False
    
    for line in lines:
        # 清理缩进空格
        line = line.rstrip()
        
        # 检测空行
        is_empty = not line.strip()
        
        if is_empty:
            if not prev_empty:
                new_lines.append('')
                prev_empty = True
        else:
            new_lines.append(line)
            prev_empty = False
    
    body = '\n'.join(new_lines)
    
    # 3. 修复代码块（添加围栏）
    body = fix_code_blocks(body)
    
    # 4. 清理多余空行（再次）
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
    
    body = '\n'.join(new_lines)
    
    # 5. 清理文件结尾
    body = body.strip() + '\n'
    
    content = frontmatter + body
    
    if content != original:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        return True
    return False

def fix_code_blocks(content):
    """修复代码块 - 检测VBScript代码并添加围栏"""
    lines = content.split('\n')
    result = []
    in_code = False
    code_buffer = []
    code_start_idx = -1
    
    for i, line in enumerate(lines):
        stripped = line.strip()
        
        if not in_code:
            # 检测代码开始
            if looks_like_code(stripped) and not stripped.startswith('#'):
                # 检查是否需要开始代码块
                # 检查前后文是否有连续代码
                j = i - 1
                code_before = 0
                while j >= 0:
                    prev = lines[j].strip()
                    if looks_like_code(prev):
                        code_before += 1
                        j -= 1
                    else:
                        break
                
                if code_before >= 1 or (stripped.startswith("'") and len(stripped) > 5):
                    in_code = True
                    code_buffer = [line]
                    result.append('```vbscript')
                    continue
            
            result.append(line)
        else:
            # 在代码块内
            # 检测代码结束
            if looks_like_code(stripped) or stripped.startswith("'") or not stripped:
                code_buffer.append(line)
            else:
                # 代码结束
                if code_buffer:
                    result.extend(code_buffer)
                    result.append('```')
                    result.append('')
                in_code = False
                code_buffer = []
                result.append(line)
    
    # 处理未关闭的代码块
    if in_code and code_buffer:
        if any(looks_like_code(line.strip()) for line in code_buffer):
            result.append('```vbscript')
            result.extend(code_buffer)
            result.append('```')
    
    return '\n'.join(result)

def looks_like_code(line):
    """检测是否是代码行"""
    if not line:
        return False
    
    stripped = line.strip()
    
    # 跳过标题和特殊标记
    if stripped.startswith('#'):
        return False
    if stripped.startswith('**'):
        return False
    if stripped.startswith('>'):
        return False
    if stripped.startswith('!'):
        return False
    if stripped.startswith('- ['):
        return False
    if stripped.startswith('[') and ']' in stripped and not '.vbs' in stripped.lower():
        return False
    
    # VBScript特征
    if stripped.startswith("'"):
        return True
    if re.match(r"^\s*Set\s+\w+", stripped, re.I):
        return True
    if re.match(r"^\s*Dim\s+\w+", stripped, re.I):
        return True
    if re.match(r"^\s*If\s+", stripped, re.I):
        return True
    if re.match(r"^\s*End\s+If", stripped, re.I):
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
    if re.match(r"^\s*\w+\s*=\s*.+\(", stripped):
        return True
    if re.match(r"^\s*\w+\.\w+\s*=", stripped):
        return True
    if re.match(r"^\s*\(?\w+\s*\(", stripped):
        return True
    
    return False

def run():
    """运行清理"""
    base_dir = Path('CAAKnowledge/use-cases')
    if not base_dir.exists():
        print(f"目录不存在: {base_dir}")
        return
    
    print("=" * 60)
    print("CATIA CAA V5 Use-Case 文档清理")
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
