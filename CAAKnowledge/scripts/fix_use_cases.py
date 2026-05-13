#!/usr/bin/env python3
"""P1: 修复 use-case 文档 — frontmatter、代码块去碎片、内容去重。"""

import os
import re
import sys

USE_CASES_DIR = "/workspace/CAAKnowledge/use-cases"


def fix_frontmatter(content):
    """Fix YAML frontmatter that has ```vbscript leaked into it."""
    if not content.startswith('---\n```vbscript'):
        return content

    # Extract the real frontmatter fields from the corrupted block
    lines = content.split('\n')
    end_idx = -1
    for i in range(1, min(len(lines), 30)):
        if lines[i].strip() == '---':
            end_idx = i
            break

    if end_idx < 0:
        return content

    fm_lines = lines[1:end_idx]

    # Extract fields
    title = ""
    category = ""
    module = ""
    tags = ""
    source_file = ""
    converted = ""

    for line in fm_lines:
        line = line.strip()
        if line.startswith('```'):
            continue
        m = re.match(r'title:\s*"?(.+?)"?$', line)
        if m:
            title = m.group(1).strip().strip('"')
            continue
        m = re.match(r'category:\s*"?(.+?)"?$', line)
        if m:
            category = m.group(1).strip().strip('"')
            continue
        m = re.match(r'module:\s*"?(.+?)"?$', line)
        if m:
            module = m.group(1).strip().strip('"')
            continue
        m = re.match(r'tags:\s*"?(.+?)"?$', line)
        if m:
            tags = m.group(1).strip().strip('"')
            continue
        m = re.match(r'source_file:\s*"?(.+?)"?$', line)
        if m:
            source_file = m.group(1).strip().strip('"')
            continue
        m = re.match(r'converted:\s*"?(.+?)"?$', line)
        if m:
            converted = m.group(1).strip().strip('"')
            continue

    # Fix source_file extension
    if source_file.endswith('.htmmd'):
        source_file = source_file.replace('.htmmd', '.htm')
    if source_file.endswith('.htmlmd'):
        source_file = source_file.replace('.htmlmd', '.html')

    # Rebuild proper frontmatter
    new_fm = "---\n"
    if title:
        new_fm += f'title: "{title}"\n'
    if category:
        new_fm += f'category: "{category}"\n'
    if module:
        new_fm += f'module: "{module}"\n'
    if tags:
        new_fm += f'tags: "{tags}"\n'
    if source_file:
        new_fm += f'source_file: "{source_file}"\n'
    if converted:
        new_fm += f'converted: "{converted}"\n'
    new_fm += "---\n"

    # Body starts after the old ---
    body = '\n'.join(lines[end_idx + 1:])
    return new_fm + body


def defragment_code_blocks(content):
    """Merge fragmented code blocks and fix language tags."""
    lines = content.split('\n')
    result = []
    i = 0

    while i < len(lines):
        line = lines[i]

        # Skip stray ```vbscript that starts a line but isn't a real fence
        if line.strip() == '```vbscript':
            # Check if this is inside what should be C++ code
            look_ahead = []
            j = i + 1
            while j < min(len(lines), i + 10):
                la = lines[j].strip()
                if la in ('```', '```vbscript', '```cpp'):
                    break
                if la:
                    look_ahead.append(la)
                j += 1

            # Heuristic: if surrounding lines look like C++, use ```cpp instead
            is_cpp = any(
                kw in ' '.join(look_ahead)
                for kw in ['HRESULT', 'virtual', 'class', '#include', 'CAT', '::']
            )
            if is_cpp:
                result.append('```cpp')
            else:
                result.append(line)
            i += 1
            continue

        result.append(line)
        i += 1

    return '\n'.join(result)


def deduplicate_content(content):
    """Remove consecutive duplicate paragraphs."""
    lines = content.split('\n')
    result = []
    prev_nonempty = ""

    for line in lines:
        stripped = line.strip()
        if stripped and stripped == prev_nonempty and len(stripped) > 20:
            continue
        result.append(line)
        if stripped:
            prev_nonempty = stripped

    return '\n'.join(result)


def fix_code_fence_pairs(content):
    """Ensure ``` fence pairs are balanced."""
    lines = content.split('\n')
    fences = []
    for i, line in enumerate(lines):
        stripped = line.strip()
        if stripped.startswith('```'):
            fences.append((i, stripped))

    # Check if we have an odd number
    if len(fences) % 2 != 0:
        # Find unclosed fence and add closing
        # Simple approach: if last fence is opener, close it
        # Actually, let's just check if fence count is odd and add closing at end
        open_count = sum(1 for _, f in fences if len(f) > 3)  # ```lang opens
        close_count = sum(1 for _, f in fences if f == '```')  # ``` closes

        if open_count > close_count:
            lines.append('```')

    return '\n'.join(lines)


def process_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except Exception:
        return

    original = content

    content = fix_frontmatter(content)
    content = defragment_code_blocks(content)
    content = deduplicate_content(content)
    content = fix_code_fence_pairs(content)

    if content != original:
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        return True
    return False


def main():
    stats = {"total": 0, "fixed": 0, "errors": 0}

    for root, dirs, files in os.walk(USE_CASES_DIR):
        for fname in files:
            if not fname.endswith('.md'):
                continue
            fpath = os.path.join(root, fname)
            stats["total"] += 1
            try:
                if process_file(fpath):
                    stats["fixed"] += 1
            except Exception as e:
                stats["errors"] += 1
                if stats["errors"] <= 5:
                    print(f"  Error: {fpath}: {e}")

    print(f"Total files: {stats['total']}")
    print(f"Files fixed: {stats['fixed']}")
    print(f"Errors: {stats['errors']}")


if __name__ == "__main__":
    main()