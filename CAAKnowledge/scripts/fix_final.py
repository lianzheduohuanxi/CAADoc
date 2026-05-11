#!/usr/bin/env python3
"""
CATIA CAA V5 知识库最终修复脚本
正确修复路径、代码块和表格问题
"""
import re
import os
from pathlib import Path

def fix_use_case_docs():
    """修复Use-Case文档中的各种问题"""
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
            
            # 1. 修复 source_file 路径 - 统一使用正斜杠，保持.htm扩展名
            def fix_source_path(match):
                path = match.group(1)
                # 统一使用正斜杠
                path = path.replace('\\', '/')
                return f'source_file: "{path}"'
            
            content = re.sub(
                r'source_file:\s*"([^"]+)"',
                fix_source_path,
                content
            )
            
            # 2. 移除内容中错误的 ```vbscript``` 标签对（只有一个的情况）
            content = re.sub(r'```vbscript\s*```vbscript', '```vbscript', content)
            
            # 3. 清理多余的空行
            content = re.sub(r'\n{3,}', '\n\n', content)
            
            # 4. 清理单列空表格行
            lines = content.split('\n')
            new_lines = []
            prev_empty_table = False
            
            for line in lines:
                stripped = line.strip()
                
                # 检测空单列表格: | 或 |  |
                is_empty_table = re.match(r'^(\|\s*)+$', stripped)
                
                # 检测纯分隔符行
                is_separator = re.match(r'^\|?\s*[-=]+\s*\|', stripped)
                
                if is_separator and prev_empty_table:
                    # 跳过紧跟空表格的分隔符
                    prev_empty_table = False
                    continue
                
                if is_empty_table:
                    prev_empty_table = True
                    # 保留一个
                    new_lines.append(line)
                    continue
                else:
                    prev_empty_table = False
                
                new_lines.append(line)
            
            content = '\n'.join(new_lines)
            
            # 5. 修复VBScript代码块 - 更保守的方法
            content = fix_vbscript_blocks_conservative(content)
            
            if content != original:
                with open(md_file, 'w', encoding='utf-8') as f:
                    f.write(content)
                fixed_count += 1
                
        except Exception as e:
            print(f"Error processing {md_file}: {e}")
    
    print(f"修复了 {fixed_count} 个 Use-Case 文档")

def fix_vbscript_blocks_conservative(content):
    """更保守的VBScript代码块修复"""
    lines = content.split('\n')
    result = []
    in_code = False
    code_buffer = []
    
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        
        if not in_code:
            # 检测代码开始
            if (stripped.startswith("' ___") or
                re.match(r"^\s*' [-_=]{10,}", stripped) or
                (stripped.startswith("'") and len(stripped) > 3 and 
                 not stripped.startswith("##") and 
                 not stripped.startswith("# ") and
                 not stripped.startswith("'**") and
                 not stripped.startswith("'>"))):
                
                # 检查是否有连续代码
                j = i + 1
                code_lines = [stripped]
                while j < len(lines):
                    next_stripped = lines[j].strip()
                    if (next_stripped.startswith("'") or
                        re.match(r"^\s*(Set |Dim |CATIA\.|Err\.|If |For |While |Do |Select |Next |End |private|public|sub|function)", next_stripped, re.I) or
                        re.match(r'^\s*[a-zA-Z_]\w*\s*=', next_stripped)):
                        code_lines.append(next_stripped)
                        j += 1
                    else:
                        break
                
                # 如果有3行以上连续代码，开启代码块
                if len(code_lines) >= 3:
                    in_code = True
                    code_buffer = [line]
                    i += 1
                    continue
            
            result.append(line)
            i += 1
        else:
            # 在代码块内
            # 检测代码结束
            is_end = False
            
            # 空行后跟着非代码内容
            if stripped == '':
                if i + 1 < len(lines):
                    next_stripped = lines[i + 1].strip()
                    if (next_stripped.startswith('---') or
                        next_stripped.startswith('**') or
                        next_stripped.startswith('##') or
                        next_stripped.startswith('# ') or
                        next_stripped.startswith('####') or
                        next_stripped.startswith('>') or
                        (next_stripped and 
                         not next_stripped.startswith("'") and
                         not re.match(r"^\s*(Set |Dim |CATIA\.|Err\.|If |For |While |Do |Select |Next |End |private|public|sub|function)", next_stripped, re.I))):
                        is_end = True
            
            # 非空行但不是代码
            if not stripped and i > 0:
                pass  # 继续收集
            elif stripped and not (
                stripped.startswith("'") or
                re.match(r"^\s*(Set |Dim |CATIA\.|Err\.|If |For |While |Do |Select |Next |End |private|public)", stripped, re.I) or
                re.match(r"^\s*[a-zA-Z_]\w*\s*=", stripped) or
                re.match(r"^\s*\(", stripped) or
                stripped.startswith("' ---")
            ):
                is_end = True
            
            if is_end:
                # 输出代码块
                result.append('```vbscript')
                result.extend(code_buffer)
                result.append('```')
                result.append('')
                in_code = False
                code_buffer = []
                # 不递增i，让当前行被重新处理
                continue
            else:
                code_buffer.append(line)
                i += 1
    
    # 处理未关闭的代码块
    if in_code and code_buffer:
        result.append('```vbscript')
        result.extend(code_buffer)
        result.append('```')
    
    return '\n'.join(result)

def main():
    print("=" * 60)
    print("CATIA CAA V5 知识库最终修复")
    print("=" * 60)
    
    print("\n修复 Use-Case 文档...")
    fix_use_case_docs()
    
    print("\n" + "=" * 60)
    print("修复完成!")
    print("=" * 60)

if __name__ == '__main__':
    main()
