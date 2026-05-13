# -*- coding: utf-8 -*-
"""
提取QI路径上下文 - P1-2
"""

import re
import sys
from pathlib import Path
import json

sys.stdout.reconfigure(encoding='utf-8')

def extract_qi_context(cpp_content, filename):
    """从C++文件提取QI调用上下文"""
    qi_contexts = []
    
    # QI调用模式
    qi_pattern = re.compile(
        r'(.{0,100})'  # 前100字符上下文
        r'(QueryInterface\s*\([^)]+\))'  # QI调用
        r'(.{0,100})',  # 后100字符上下文
        re.DOTALL
    )
    
    # 错误处理模式
    error_pattern = re.compile(r'(if\s*\(\s*FAILED\s*\([^)]+\))')
    
    lines = cpp_content.split('\n')
    
    for i, line in enumerate(lines):
        if 'QueryInterface' in line and 'IID_' in line:
            context = {
                'file': filename,
                'line': i + 1,
                'code': line.strip(),
                'prev_lines': '\n'.join(lines[max(0, i-3):i]),
                'next_lines': '\n'.join(lines[i+1:min(len(lines), i+3)])
            }
            qi_contexts.append(context)
    
    return qi_contexts

def build_qi_context_index():
    """构建QI上下文索引"""
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    
    # 读取现有QI路径
    qi_index_file = root_dir / 'quick-refs' / 'qi-paths' / 'index.md'
    
    qi_data = []
    
    if qi_index_file.exists():
        content = qi_index_file.read_text(encoding='utf-8')
        
        # 提取现有QI路径并添加上下文标记
        qi_pattern = re.compile(r'\|\s*`([^`]+)`\s*\|\s*`([^`]+)`\s*\|')
        
        for match in qi_pattern.finditer(content):
            source_iface = match.group(1)
            target_iface = match.group(2)
            
            qi_data.append({
                'source': source_iface,
                'target': target_iface,
                'context': 'N/A - Requires source code analysis'
            })
    
    return qi_data

def main():
    print("P1-2: QI Path Context Extraction")
    print("=" * 50)
    
    qi_data = build_qi_context_index()
    
    # 保存结果
    output_file = Path(r'C:\Luxshare\CAADoc\CAAKnowledge\quick-refs\qi-paths\context-index.json')
    output_file.parent.mkdir(parents=True, exist_ok=True)
    
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump({
            'total_paths': len(qi_data),
            'paths': qi_data
        }, f, indent=2, ensure_ascii=False)
    
    print(f"[OK] QI context index created: {len(qi_data)} paths")
    print(f"Output: {output_file}")

if __name__ == '__main__':
    main()