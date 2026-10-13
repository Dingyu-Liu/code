import random
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





