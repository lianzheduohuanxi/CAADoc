# -*- coding: utf-8 -*-
"""
修复代码块围栏 - 为VBScript代码添加```vbscript标记
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

# VBScript特征关键词
VBSCRIPT_KEYWORDS = [
    'CATIA.',
    'Set ',
    'Dim ',
    '.Add(',
    'Err.Raise',
    'MsgBox',
    'CreateObject',
    'GetObject',
    'On Error',
    'End Sub',
    'End Function',
    'Sub ',
    'Function ',
]

def is_vbscript_context(line):
    """检测行是否包含VBScript特征"""
    return any(kw in line for kw in VBSCRIPT_KEYWORDS)

def detect_and_wrap_code(content):
    """检测并包裹VBScript代码块"""
    lines = content.split('\n')
    result = []
    in_vbscript = False
    brace_count = 0
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # 检测代码开始
        if not in_vbscript and is_vbscript_context(line):
            # 向前查找代码开始
            start_idx = i
            while start_idx > 0:
                prev_line = lines[start_idx - 1].strip()
                if prev_line and not prev_line.startswith('#') and not prev_line.startswith('//'):
                    break
                start_idx -= 1
            
            # 确认是代码区域
            code_lines = lines[start_idx:i+1]
            code_preview = '\n'.join(code_lines)
            if any(is_vbscript_context(l) for l in code_lines):
                # 添加围栏开始
                result.append('```vbscript')
                in_vbscript = True
        
        # 处理代码块内
        if in_vbscript:
            result.append(line)
            
            # 检测代码结束 - 常见的VBScript块结束标志
            stripped = line.strip()
            
            # 遇到空行后跟非代码行，可能是结束
            if not stripped:
                # 检查后面几行是否都是空或非代码
                j = i + 1
                non_code_count = 0
                while j < len(lines) and j < i + 5:
                    next_line = lines[j].strip()
                    if not next_line:
                        j += 1
                        continue
                    if next_line.startswith('#') or next_line.startswith('//') or not is_vbscript_context(next_line):
                        non_code_count += 1
                    else:
                        break
                    j += 1
                
                # 如果连续3行非代码，关闭代码块
                if non_code_count >= 3:
                    result.append('```')
                    in_vbscript = False
                    continue
            elif stripped.startswith('Sub ') or stripped.startswith('Function '):
                # 统计函数结束
                brace_count += 1
            elif stripped == 'End Sub' or stripped == 'End Function':
                brace_count -= 1
                if brace_count == 0 and i + 1 < len(lines):
                    next_stripped = lines[i + 1].strip()
                    if next_stripped and not is_vbscript_context(next_stripped):
                        result.append('```')
                        in_vbscript = False
            
            # 遇到段落标题或列表，可能结束
            elif stripped.startswith('#') or (stripped and not stripped.startswith(' ') and not stripped.startswith('\t')):
                if not is_vbscript_context(stripped):
                    result.append('```')
                    in_vbscript = False
        else:
            result.append(line)
        
        i += 1
    
    # 如果仍在代码块中，关闭它
    if in_vbscript:
        result.append('```')
    
    return '\n'.join(result)

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    modified_count = 0
    total_fences_added = 0
    
    print(f"Starting code fence fix in {total_files} Markdown files...")
    
    for md_file in md_files:
        original = md_file.read_text(encoding='utf-8')
        
        # 检查是否已有vbscript标记
        has_vbscript = '```vbscript' in original or '```vbs' in original
        
        fixed = detect_and_wrap_code(original)
        
        if fixed != original:
            # 统计新增的围栏
            original_fences = len(re.findall(r'```vbscript', original))
            fixed_fences = len(re.findall(r'```vbscript', fixed))
            fences_added = fixed_fences - original_fences
            
            md_file.write_text(fixed, encoding='utf-8')
            total_fences_added += fences_added
            modified_count += 1
            
            if has_vbscript or fences_added > 0:
                print(f"  Fixed: {md_file.relative_to(root_dir)} (+{fences_added} fences)")
    
    print(f"[OK] Code fence fix completed!")
    print(f"   - Modified: {modified_count}/{total_files}")
    print(f"   - Total vbscript fences added: {total_fences_added}")

if __name__ == '__main__':
    main()