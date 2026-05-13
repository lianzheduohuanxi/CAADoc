# -*- coding: utf-8 -*-
"""
增强空接口说明 - 为无方法说明的接口添加继承链和TIE信息
"""

import re
import sys
from pathlib import Path
import json

sys.stdout.reconfigure(encoding='utf-8')

def extract_base_class(content):
    """从接口文档提取基类"""
    # 查找继承关系
    patterns = [
        r'继承自\s+\*\*([A-Za-z0-9]+)\*\*',
        r'extends\s+([A-Za-z0-9]+)',
        r'inherits\s+([A-Za-z0-9]+)',
        r'→\s+([A-Za-z0-9]+)\s*$',
    ]
    
    for pattern in patterns:
        match = re.search(pattern, content, re.MULTILINE)
        if match:
            return match.group(1)
    
    # 查找方法表前的接口名
    interface_match = re.search(r'interface\s+([A-Z][A-Za-z0-9]+)', content)
    if interface_match:
        return interface_match.group(1)
    
    return None

def extract_interface_name(md_path):
    """从文件路径提取接口名"""
    return md_path.stem

def build_enhancement(interface_name, base_class, tie_info):
    """构建增强内容"""
    base_link = f"[{base_class}](../api-reference/interfaces/{base_class}.md)" if base_class else "CATBaseUnknown"
    
    tie_section = ""
    if tie_info:
        tie_section = f"""
**TIE绑定**: 
- 源文件: `{tie_info.get('source_file', '未知')}`
- 实现类: `{tie_info.get('implementation_class', '未知')}`
"""
    
    enhancement = f"""

---

## Interface Overview

This interface inherits from **{base_class}**. 

**Base Interface**: {base_link}{tie_section}

**Inherited Methods**: Please refer to the base interface documentation above.
"""
    return enhancement

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    interfaces_dir = root_dir / 'api-reference' / 'interfaces'
    
    # 加载TIE信息
    tie_data = {}
    tie_file = root_dir / 'quick-refs' / 'tie-index.md'
    if tie_file.exists():
        content = tie_file.read_text(encoding='utf-8')
        # 解析TIE信息 (简化)
        for line in content.split('\n'):
            if '→' in line or '| ' in line:
                parts = re.split(r'[→|]', line)
                if len(parts) >= 2:
                    iface = parts[0].strip().replace('`', '')
                    tie_data[iface] = {'source_file': parts[-1].strip().replace('`', '')}
    
    md_files = list(interfaces_dir.glob('*.md'))
    total_files = len(md_files)
    enhanced_count = 0
    
    print(f"Starting to enhance empty interfaces in {total_files} files...")
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        interface_name = extract_interface_name(md_file)
        
        # 检查是否为空接口(无方法表)
        has_methods = bool(re.search(r'\|\s*(Name|Return|Type|参数|描述|Description)\s*\|', content, re.IGNORECASE))
        
        if not has_methods:
            # 提取基类
            base_class = extract_base_class(content)
            
            # 获取TIE信息
            tie_info = tie_data.get(interface_name, {})
            
            # 构建增强内容
            enhancement = build_enhancement(interface_name, base_class, tie_info)
            
            # 添加到文档末尾
            fixed = content + enhancement
            md_file.write_text(fixed, encoding='utf-8')
            enhanced_count += 1
            print(f"  Enhanced: {interface_name}")
    
    print(f"[OK] Interface enhancement completed!")
    print(f"   - Enhanced: {enhanced_count}/{total_files}")

if __name__ == '__main__':
    main()