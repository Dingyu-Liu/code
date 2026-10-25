
import random


class GuessGame:
    def __init__(self):
        self.secret = random.randint(1, 100)   # 秘密藏在这里，外面看不见
        self.tries = 0                          # 记录猜了几次

    def check(self, guess):
        self.tries += 1                         # 每猜一次就加 1

        if guess > self.secret:
            return "high"
        elif guess < self.secret:
            return "low"
        else:
            return "correct"


# ---------------------------------------------------------------
# 测试
# ---------------------------------------------------------------
def test_():
    print("--- 测试①：tries 能正确计数 ---")
    game = GuessGame()
    result = game.check(50)
    print(result)
    print(game.tries)          # 1

    print()
    print("--- 测试②：两个对象互不干扰 ---")
    g1 = GuessGame()
    g2 = GuessGame()
    print(g1.secret, g2.secret)    # 两个不同的数字
    g1.check(50)
    print(g1.tries, g2.tries)      # 1 0  ← 互不影响！


# ---------------------------------------------------------------
# 命令行玩一局（直接运行这个文件时执行）
# ---------------------------------------------------------------
def play():
    game = GuessGame()
    print("猜一个 1 到 100 的数字：")

    while True:
        try:
            guess = int(input("请输入数字:"))
        except ValueError:
            print("请输入数字！")
            continue

        result = game.check(guess)

        if result == "high":
            print("高了")
        elif result == "low":
            print("低了")
        else:
            print(f"猜对了，所用次数是{game.tries}")
            break


if __name__ == "__main__":
    test_()
