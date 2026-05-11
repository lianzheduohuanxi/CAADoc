#!/usr/bin/env python3
"""
CATIA CAA V5 知识库修复脚本 v2
精确修复，不破坏 frontmatter
"""
import re
from pathlib import Path

class PreciseFixer:
    def __init__(self):
        self.stats = {
            'files_processed': 0,
            'files_fixed': 0,
        }
    
    def fix_file(self, filepath):
        """修复单个文件"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            return False
        
        original = content
        
        # 0. 先提取 frontmatter（不处理）
        frontmatter = ''
        body = content
        
        if content.startswith('---'):
            # 提取 frontmatter
            end_idx = content.find('\n---\n', 4)
            if end_idx != -1:
                frontmatter = content[:end_idx + 5]
                body = content[end_idx + 5:]
        
        # 1. 修复 body 部分
        body = self.fix_tables(body)
        body = self.fix_code_blocks(body)
        body = self.clean_empty_lines(body)
        
        content = frontmatter + body
        
        if content != original:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(content)
            self.stats['files_fixed'] += 1
            return True
        return False
    
    def fix_tables(self, content):
        """修复HTML表格残留"""
        lines = content.split('\n')
        result = []
        
        for i, line in enumerate(lines):
            stripped = line.strip()
            
            # 检测纯分隔符行 (|---|---|---|)
            if re.match(r'^\|?\s*[-=]+\s*(\|\s*[-=]+\s*)+$', stripped):
                # 检查前一行是否是空行
                if result and result[-1].strip() == '':
                    continue  # 跳过
                # 检查前一行是否是另一个分隔符
                if result and re.match(r'^\|?\s*[-=]+\s*(\|\s*[-=]+\s*)*$', result[-1].strip()):
                    continue  # 跳过连续的
                result.append(line)
                continue
            
            # 检测空单列表格行 |
            if stripped == '|':
                result.append(line)
                continue
            
            # 检测多列空单元格行 |  |  | 
            if re.match(r'^(\|\s*)+$', stripped) and stripped.count('|') > 1:
                # 检查前一行是否是空行
                if result and result[-1].strip() == '':
                    continue  # 跳过
                result.append(line)
                continue
            
            result.append(line)
        
        return '\n'.join(result)
    
    def fix_code_blocks(self, content):
        """修复代码块 - 只修复已有的标签，不插入新标签"""
        lines = content.split('\n')
        result = []
        in_code = False
        orphan_start = False
        
        for i, line in enumerate(lines):
            stripped = line.strip()
            
            # 检测 ```vbscript 标签
            if stripped == '```vbscript':
                if in_code:
                    # 重复的开始标签，跳过
                    continue
                if orphan_start:
                    # 前一个开始标签被跳过了，现在开始代码块
                    in_code = True
                    orphan_start = False
                    result.append(line)
                    continue
                # 检查前一行是否也是 ```vbscript
                if result and result[-1].strip() == '```vbscript':
                    continue  # 跳过连续的
                orphan_start = True
                continue
            
            # 检测 ``` 结束标签
            if stripped == '```':
                if in_code:
                    in_code = False
                    orphan_start = False
                    result.append(line)
                    continue
                else:
                    # 孤立的结束标签，跳过
                    continue
            
            # 如果前面有未处理的开始标签
            if orphan_start and not in_code:
                # 检查这一行是否是VBScript代码
                if self.looks_like_vbscript(stripped):
                    # 开始代码块
                    in_code = True
                    orphan_start = False
                    result.append('```vbscript')
                    result.append(line)
                    continue
                else:
                    # 不是代码，跳过开始标签
                    orphan_start = False
            
            result.append(line)
        
        return '\n'.join(result)
    
    def looks_like_vbscript(self, line):
        """检测是否是VBScript代码行"""
        if not line or not line.strip():
            return False
        
        stripped = line.strip()
        
        # 跳过标题和标签
        if stripped.startswith('#') or stripped.startswith('**') or stripped.startswith('>'):
            return False
        
        # VBScript特征
        patterns = [
            r"^\s*'",           # 注释
            r"^\s*Set\s+\w+",   # Set语句
            r"^\s*Dim\s+\w+",   # Dim
            r"^\s*If\s+",       # If
            r"^\s*End\s+If",   # End If
            r"^\s*For\s+",     # For
            r"^\s*Next\s*$",   # Next
            r"^\s*Err\.",      # Err
            r"^\s*CATIA\.",    # CATIA
            r"^\s*\w+\s*=\s*.+\.",  # 赋值
            r"^\s*\w+\(",       # 方法调用
        ]
        
        for p in patterns:
            if re.match(p, stripped, re.I):
                return True
        return False
    
    def clean_empty_lines(self, content):
        """清理多余空行"""
        lines = content.split('\n')
        result = []
        prev_empty = False
        
        for line in lines:
            if line.strip() == '':
                if not prev_empty:
                    result.append('')
                    prev_empty = True
            else:
                result.append(line)
                prev_empty = False
        
        # 清理文件开头和结尾
        while result and result[0] == '':
            result.pop(0)
        while result and result[-1] == '':
            result.pop()
        result.append('')
        
        return '\n'.join(result)
    
    def run(self, base_dir):
        base_path = Path(base_dir)
        print("=" * 60)
        print("CATIA CAA V5 知识库精确修复 v2")
        print("=" * 60)
        
        for md_file in base_path.rglob('*.md'):
            self.stats['files_processed'] += 1
            self.fix_file(md_file)
        
        print(f"处理文件: {self.stats['files_processed']}")
        print(f"修复文件: {self.stats['files_fixed']}")
        print("=" * 60)

if __name__ == '__main__':
    fixer = PreciseFixer()
    fixer.run('CAAKnowledge/use-cases')
