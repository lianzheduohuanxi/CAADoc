# -*- coding: utf-8 -*-
"""
修复 Markdown 文件中的失效链接
针对 Linux 路径环境优化
"""

import re
import json
from pathlib import Path
from collections import defaultdict

def analyze_and_fix_links():
    root = Path('/workspace/CAAKnowledge')
    md_files = list(root.rglob('*.md'))

    CATIA_CORE = {'CATBaseUnknown', 'CATIInterface', 'CATIObject', 'CATDispatch', 'CATIAlias', 'CATInit'}

    stats = {
        'total': 0,
        'fixed': 0,
        'broken': 0,
        'skipped': 0
    }

    link_fixes = defaultdict(list)

    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            original = content

            link_pattern = re.compile(r'\[([^\]]+)\]\(([^)]+)\)')

            def fix_link(match):
                stats['total'] += 1
                link_text = match.group(1)
                link_url = match.group(2)

                if link_url.startswith(('http', '#', 'mailto:')):
                    stats['skipped'] += 1
                    return match.group(0)

                if any(core in link_url for core in CATIA_CORE):
                    stats['skipped'] += 1
                    return match.group(0)

                parts = link_url.split('/')
                resolved_path = md_file.parent

                for part in parts:
                    if part == '..':
                        resolved_path = resolved_path.parent
                    elif part and part != '.':
                        resolved_path = resolved_path / part

                resolved_path = Path(str(resolved_path).split('#')[0].split('?')[0])

                exists = resolved_path.exists()
                if not exists:
                    for ext in ['.md', '.htm', '.html']:
                        if resolved_path.with_suffix(ext).exists():
                            exists = True
                            break

                if not exists:
                    stats['broken'] += 1
                    link_fixes[link_url].append(str(md_file.relative_to(root)))
                    return match.group(0)
                else:
                    stats['fixed'] += 1
                    return match.group(0)

            content = link_pattern.sub(fix_link, content)

        except Exception as e:
            pass

    return stats, link_fixes

def fix_common_patterns():
    """修复常见的链接模式问题"""
    root = Path('/workspace/CAAKnowledge')
    md_files = list(root.rglob('*.md'))

    fix_patterns = [
        (r'\.htm(["\)\]])', r'.md\1'),
        (r'\.HTM(["\)\]])', r'.md\1'),
    ]

    total_fixed = 0

    for md_file in md_files:
        try:
            content = md_file.read_text(encoding='utf-8')
            original = content

            for pattern, replacement in fix_patterns:
                content = re.sub(pattern, replacement, content)

            if content != original:
                fixed_count = len(re.findall(r'\.md["\)\]]', content))
                md_file.write_text(content, encoding='utf-8')
                total_fixed += fixed_count
                print(f"  Fixed .htm→.md: {md_file.relative_to(root)} ({fixed_count} links)")

        except Exception as e:
            print(f"  Error: {md_file}: {e}")

    return total_fixed

if __name__ == '__main__':
    print("=" * 60)
    print("Link Analysis & Fix")
    print("=" * 60)

    print("\n1. Analyzing broken links...")
    stats, link_fixes = analyze_and_fix_links()

    print(f"\n  Total links: {stats['total']}")
    print(f"  Fixed: {stats['fixed']}")
    print(f"  Broken: {stats['broken']}")
    print(f"  Skipped: {stats['skipped']}")

    if link_fixes:
        print(f"\n  Most common broken links:")
        for link, files in sorted(link_fixes.items(), key=lambda x: -len(x[1]))[:10]:
            print(f"    {link} ({len(files)} files)")

    print("\n2. Fixing common patterns (.htm→.md)...")
    fixed = fix_common_patterns()
    print(f"\n  Total fixes: {fixed}")
