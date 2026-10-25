import random
secret=random.randint(1,100)
def check_guess(guess):
    
    if secret > guess:
        return "low"
    elif secret < guess:
        return "high"
    else:
        return "correct"


while True:
 num =int(input("请输入数字:"))
 result=check_guess(num)
 if result =="low":
        print("猜低了")
        
 elif result =="high":
        print("猜高了")
        
 else:
        break
print("猜对了")