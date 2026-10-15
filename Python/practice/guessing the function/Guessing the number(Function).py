import random
from datetime import datetime
def average(numbers):
    total = 0
    for num in numbers:
        total += num
    return total/len(numbers)
def check_guess(secret, guess):
    if guess > secret:
        return "high"
    elif guess < secret:
        return "low"
    else:
        return "correct"
secret = random.randint(1, 100)
count = 0
while True:
    try:
        guess = int(input("请输入数字:"))
    except ValueError:
        print("请输入数字！")
        continue   
    if guess < 1 or guess > 100:
        print("请输入 1 到 100 之间的数字！")
        continue           
           
    count+=1

    result = check_guess(secret, guess)

    if result == "high":
        print("高了")
    elif result == "low":
        print("低了")
    else:
     break
print(f"猜对了，所用次数是{count}")
#======写入日志==========
now = datetime.now().strftime("%Y-%m-%d %H:%M")
with open("game_log.txt","a",encoding="utf-8") as f:
    
    f.write(f"{now},{secret},{count}\n")
#=======读取日志并统计=====
all_attempts = []  # 每一局猜测次数
try:
    with open("game_log.txt", "r", encoding="utf-8") as f:
        for line in f:
            if not line.strip():                   
                continue         # 跳过空行，防止解包失败
            parts = line.strip().split(",")
            if len(parts) != 3:
                continue
            date,answer,tries = parts
            tries = int(tries)
            all_attempts.append(tries)
            
except FileNotFoundError:
    pass
if all_attempts == []:
    print("暂无历史记录") 
else:
    best = min(all_attempts)     # 最少次数
    avg = average(all_attempts)  # 平均次数
    print(f"一共玩了{len(all_attempts)}局,最少{best}次猜中,平均{avg:.2f}次猜中")

    
        




