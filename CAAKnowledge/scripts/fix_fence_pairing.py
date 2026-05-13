# -*- coding: utf-8 -*-
"""
修复代码围栏配对问题 - 修复孤立的```标签
"""

import re
import sys
from pathlib import Path

sys.stdout.reconfigure(encoding='utf-8')

def fix_fence_pairing(content):
    """修复代码围栏配对问题"""
    lines = content.split('\n')
    result = []
    in_fence = False
    fence_type = ''
    
    for i, line in enumerate(lines):
        # 检测围栏开始
        fence_match = re.match(r'^```(\w*)$', line.strip())
        
        if fence_match:
            if not in_fence:
                # 开始新代码块
                in_fence = True
                fence_type = fence_match.group(1) or ''
                result.append(line)
            else:
                # 结束当前代码块
                in_fence = False
                fence_type = ''
                result.append(line)
        else:
            result.append(line)
    
    # 如果仍在代码块中，添加结束围栏
    if in_fence:
        result.append('```')
    
    return '\n'.join(result)

def main():
    root_dir = Path(r'C:\Luxshare\CAADoc\CAAKnowledge')
    md_files = list(root_dir.rglob('*.md'))
    
    total_files = len(md_files)
    fixed_count = 0
    
    print(f"Starting to fix fence pairing in {total_files} files...")
    
    for md_file in md_files:
        content = md_file.read_text(encoding='utf-8')
        
        # 检查是否有配对问题
        open_fences = len(re.findall(r'^```(\w*)$', content, re.MULTILINE))
        
        if open_fences % 2 != 0:
            fixed = fix_fence_pairing(content)
            if fixed != content:
                md_file.write_text(fixed, encoding='utf-8')
                fixed_count += 1
                print(f"  Fixed: {md_file.relative_to(root_dir)}")
    
    print(f"[OK] Fence pairing fix completed!")
    print(f"   - Fixed: {fixed_count}/{total_files}")

if __name__ == '__main__':
    main()