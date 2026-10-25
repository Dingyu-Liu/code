import os
import shutil
from pathlib import Path

FOLDER = Path.home() / "Desktop" / "folder_test"


def get_extension(filename):
    parts = filename.rsplit(".", 1)
    if len(parts) < 2:
        return None          
    return parts[1].lower()


def scan_folder(folder):
    counts = {}
    total = 0

    for item in folder.iterdir():
        if not item.is_file():
            continue       
        else:
            total += 1

        ext = get_extension(item.name)
        if ext is None:
            continue         

        counts[ext] = counts.get(ext, 0) + 1

    return counts, total

def sort_key(pair):
    ext, count = pair
    return (-count, ext)


def print_counts(counts, total):
    for ext, count in sorted(counts.items(), key=sort_key):
        print(f"{'.' + ext:<8}: {count} 个")

    print(f"共 {total} 个文件")


def main():
    folder = FOLDER

    if not folder.exists():
        print(f"文件夹不存在：{folder}")
        return

    print(f"扫描文件夹：{folder}")
    print("-" * 20)

    counts, total = scan_folder(folder)
    print_counts(counts, total)

if __name__ == "__main__":
    main()
