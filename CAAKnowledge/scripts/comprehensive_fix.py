#!/usr/bin/env python3
"""
CATIA CAA V5 知识库综合修复脚本
一次性修复所有已知问题：
1. HTML表格残留
2. 无效代码围栏配对
3. 图片路径
4. 多余空行
"""
import re
from pathlib import Path

class ComprehensiveFixer:
    def __init__(self):
        self.stats = {
            'files_processed': 0,
            'files_fixed': 0,
            'tables_fixed': 0,
            'code_blocks_fixed': 0,
            'images_fixed': 0,
            'empty_lines_fixed': 0
        }
    
    def fix_file(self, filepath):
        """修复单个文件的所有问题"""
        try:
            with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            return False
        
        original = content
        
        # 1. 修复表格
        content = self.fix_tables(content)
        
        # 2. 修复代码块
        content = self.fix_code_blocks(content)
        
        # 3. 修复图片路径
        content = self.fix_images(content, filepath)
        
        # 4. 清理多余空行
        content = self.clean_empty_lines(content)
        
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
        i = 0
        
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()
            
            # 检测纯分隔符行 (|---|---|---|)
            if re.match(r'^\|?\s*[-=]+\s*(\|\s*[-=]+\s*)+$', stripped):
                # 检查前一行是否是空行或另一个分隔符
                if result and (re.match(r'^(\|\s*)+$', result[-1].strip()) or 
                               re.match(r'^\|?\s*[-=]+\s*(\|\s*[-=]+\s*)+$', result[-1].strip())):
                    i += 1
                    continue
                result.append(line)
                i += 1
                self.stats['tables_fixed'] += 1
                continue
            
            # 检测空单列表格行 | 或 |  |
            if re.match(r'^(\|\s*)+$', stripped) and stripped == '|':
                # 保留一个
                result.append(line)
                i += 1
                continue
            
            # 检测多列空单元格 |  |  |  |
            if re.match(r'^(\|\s*)+$', stripped) and stripped.count('|') > 1:
                # 检查前一行
                if result:
                    prev = result[-1].strip()
                    # 如果前一行是空行或另一个空单元格行，跳过
                    if prev == '' or re.match(r'^(\|\s*)+$', prev):
                        i += 1
                        continue
                result.append(line)
                i += 1
                continue
            
            result.append(line)
            i += 1
        
        return '\n'.join(result)
    
    def fix_code_blocks(self, content):
        """修复代码块围栏 - 非常保守的策略"""
        lines = content.split('\n')
        result = []
        i = 0
        in_code = False
        code_buffer = []
        code_start_idx = -1
        
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()
            
            if not in_code:
                # 检测代码开始
                if stripped.startswith('```vbscript'):
                    # 检查前一行是否也是 ```vbscript
                    if result and result[-1].strip() == '```vbscript':
                        # 跳过这个开始标签
                        i += 1
                        continue
                    in_code = True
                    code_start_idx = len(result)
                    code_buffer = []
                    result.append(line)
                    i += 1
                    continue
                
                # 检测行首缩进的VBScript代码（连续多行）
                if self.looks_like_vbscript(stripped):
                    # 检查前面几行
                    look_back = max(0, i - 5)
                    has_vbscript_lines = False
                    vbscript_count = 0
                    for j in range(look_back, i + 3):
                        if j < len(lines) and self.looks_like_vbscript(lines[j].strip()):
                            vbscript_count += 1
                    
                    if vbscript_count >= 3:
                        # 开始收集代码
                        in_code = True
                        code_start_idx = len(result)
                        code_buffer = []
                        result.append('```vbscript')
                        # 回溯添加前面的代码行
                        for j in range(look_back, i):
                            prev_line = lines[j].strip()
                            if self.looks_like_vbscript(prev_line):
                                result.append(prev_line)
                        result.append(line)
                        i += 1
                        continue
                    else:
                        result.append(line)
                        i += 1
                        continue
                
                result.append(line)
                i += 1
            else:
                # 在代码块内
                if stripped == '```vbscript' or stripped == '```':
                    # 检查是否应该结束
                    # 如果下一行不是代码，开始新行
                    if i + 1 < len(lines):
                        next_stripped = lines[i + 1].strip()
                        if not self.looks_like_vbscript(next_stripped) and next_stripped:
                            in_code = False
                            result.append(line)
                            result.append('```')
                            i += 2
                            self.stats['code_blocks_fixed'] += 1
                            continue
                
                # 空行处理
                if stripped == '':
                    # 检查上下文
                    if i + 1 < len(lines):
                        next_stripped = lines[i + 1].strip()
                        if not self.looks_like_vbscript(next_stripped) and next_stripped:
                            # 代码块结束
                            result.append(line)
                            result.append('```')
                            result.append('')
                            in_code = False
                            i += 1
                            self.stats['code_blocks_fixed'] += 1
                            continue
                
                # 非代码行
                if not self.looks_like_vbscript(stripped) and stripped and not stripped.startswith("'"):
                    # 代码块结束
                    result.append('```')
                    result.append('')
                    in_code = False
                    self.stats['code_blocks_fixed'] += 1
                    # 不递增i，重新处理这行
                    continue
                
                result.append(line)
                i += 1
        
        # 处理未关闭的代码块
        if in_code and code_buffer:
            result.append('```')
        
        return '\n'.join(result)
    
    def looks_like_vbscript(self, line):
        """检测是否是VBScript代码行"""
        if not line:
            return False
        
        # 跳过标签
        if line.startswith('```') or line.startswith('#') or line.startswith('**'):
            return False
        
        # VBScript特征
        vbscript_patterns = [
            r"^\s*'",           # 注释行
            r"^\s*Set\s+\w+",   # Set语句
            r"^\s*Dim\s+\w+",   # Dim语句
            r"^\s*If\s+",       # If语句
            r"^\s*End\s+If",   # End If
            r"^\s*For\s+",     # For循环
            r"^\s*Next\s*$",   # Next
            r"^\s*While\s+",   # While循环
            r"^\s*Do\s+",      # Do循环
            r"^\s*Select\s+",   # Select
            r"^\s*Case\s+",    # Case
            r"^\s*Function\s+",# Function
            r"^\s*Sub\s+",     # Sub
            r"^\s*End\s+(Sub|Function|If)", # 结束
            r"^\s*Err\.",      # Err对象
            r"^\s*CATIA\.",    # CATIA对象
            r"^\s*\w+\s*=\s*", # 赋值
            r"^\s*\w+\(",       # 方法调用
            r"^\s*\(?\w+",     # 表达式开始
        ]
        
        for pattern in vbscript_patterns:
            if re.match(pattern, line, re.IGNORECASE):
                return True
        
        return False
    
    def fix_images(self, content, filepath):
        """修复图片路径"""
        # 标准化 ../ 路径
        content = content.replace('..\\', '../')
        
        # 检测是否有 ../CAAScrBase/images/ 这样的路径
        if '../CAAScrBase/images/' in content:
            self.stats['images_fixed'] += 1
        
        return content
    
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
        
        # 清理文件开头和结尾的多余空行
        while result and result[0] == '':
            result.pop(0)
        while result and result[-1] == '':
            result.pop()
        result.append('')
        
        return '\n'.join(result)
    
    def run(self, base_dir):
        """运行修复"""
        base_path = Path(base_dir)
        print("=" * 60)
        print("CATIA CAA V5 知识库综合修复")
        print("=" * 60)
        
        for md_file in base_path.rglob('*.md'):
            self.stats['files_processed'] += 1
            self.fix_file(md_file)
        
        print(f"处理文件: {self.stats['files_processed']}")
        print(f"修复文件: {self.stats['files_fixed']}")
        print(f"修复表格: {self.stats['tables_fixed']}")
        print(f"修复代码块: {self.stats['code_blocks_fixed']}")
        print(f"修复图片路径: {self.stats['images_fixed']}")
        print("=" * 60)

if __name__ == '__main__':
    fixer = ComprehensiveFixer()
    fixer.run('CAAKnowledge/use-cases')
