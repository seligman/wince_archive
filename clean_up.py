#!/usr/bin/env python3

from collections import deque, defaultdict
import os, re

BAD_FILES = [
    '.*\\.aps$',
    '.*\\.cab$',
    '.*\\.cachefile',
    '.*\\.db$',
    '.*\\.exe$',
    '.*\\.ncb$',
    '.*\\.obj$',
    '.*\\.pch$',
    '.*\\.pdb$',
    '.*\\.scr$',
    '.*\\.sdf$',
    '.*\\.suo$',
    '.*\\.tmp$',
    '.*\\.user$',
    '.*\\.vbw$',
    '.*\\.pyc$',
    '.*\\.bak$',
    '.*\\.plg$',
    '.*\\.vcl$',
    '.*/MSSCCPRJ.SCC$',
    '.*cache\\.dat',
    '.*\\.signature.p7s$',
]
BAD_DIRS = [
    '/[^/]*Dbg[^/]*$',
    '/[^/]*Debug[^/]*$',
    '/[^/]*Pocket PC 2003 \\(ARMV4\\)[^/]*$',
    '/[^/]*Rel[^/]*$',
    '/[^/]*Smartphone 2003 \\(ARMV4\\)[^/]*$',
    '/[^/]*Windows Mobile 5\\.0 Pocket PC SDK \\(ARMV4I\\)[^/]*$',
    '/[^/]*Windows Mobile 6 Professional SDK \\(ARMV4I\\)[^/]*$',
    '/Bin$',
    '/.idea$',
    '/.vscode$',
    '/Box 2D/Box2D$',
    '/Box 2D/Library$',
    '/ClientBin$',
    '/Obj$',
    '/ipch$',
    '/.vs$',
]

def enum_files(include_dirs=False):
    dirs = deque(["."])
    while len(dirs) > 0:
        cur_dir = dirs.popleft()
        files = 0
        if os.path.isdir(cur_dir):
            for cur in sorted(os.listdir(cur_dir)):
                if cur not in {".git"}:
                    files += 1
                    cur = os.path.join(cur_dir, cur)
                    if os.path.isdir(cur):
                        dirs.append(cur)
                    elif os.path.isfile(cur):
                        if include_dirs:
                            yield True, cur, 0
                        else:
                            yield cur
            if include_dirs:
                yield False, cur_dir, files

def find_compiled():
    issues = defaultdict(int)

    for is_file, cur, contents in enum_files(include_dirs=True):
        key = "/".join(cur.split(os.path.sep))

        is_bad = False
        if is_file:
            for re_test in BAD_FILES:
                if re.search(re_test, key, re.IGNORECASE) is not None:
                    is_bad = True
                    break
        else:
            if contents == 0:
                is_bad = True
            else:
                for re_test in BAD_DIRS:
                    if re.search(re_test, key, re.IGNORECASE) is not None:
                        is_bad = True
                        break

        if is_bad:
            issues["Bad files"] += 1
            if is_file:
                print(f'del "{cur}"')
            else:
                print(f'rmdir "{cur}"')
        
        if not os.access(cur, os.W_OK):
            issues["Readonly files"] += 1
            print(f'attrib -r "{cur}"')

    if len(issues) == 0:
        print("@rem No issues found.")
    else:
        for issue, count in issues.items():
            print(f"@rem {issue}: {count:,}")

def main():
    find_compiled()

if __name__ == "__main__":
    main()
