from pathlib import Path

BASE = Path(__file__).resolve().parent

def safe_divide(a, b):
    try:
        return a / b
    except (ZeroDivisionError, TypeError):
        return None

def read_first_line(path):
    try:

        with open(path, "r", encoding="utf-8-sig") as f:
            return f.readline().strip()
    except (FileNotFoundError, IsADirectoryError, TypeError, UnicodeDecodeError):
        return None



def test_():
    print(safe_divide(10, 2))                     # 期望 5.0
    print(safe_divide(10, 0))                     # 期望 None
    print(safe_divide("abc", 2))                  # 期望 None
    print(read_first_line(BASE / "game_log.txt"))     # 期望文件第一行
    print(read_first_line("根本没有这个.txt"))          # 期望 None


if __name__ == "__main__":
    test_()