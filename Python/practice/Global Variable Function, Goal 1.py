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
    guess = int(input("输入猜测数字:"))
    count+=1
    result = check_guess(secret, guess)

    if result == "high":
     print("高了")
    elif result == "low":
     print("低了")
    else:
     break
print(f"猜对了，所用次数是{count}")




