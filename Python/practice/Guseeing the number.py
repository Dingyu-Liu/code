import random
random1 = 50
print("Enter a number in 1~100:")
count = 0
while True:
    number = int(input("Enter a number:"))
    count = count + 1
    
    if random1 < number:
        print("you guessed too high")
       
    elif random1 > number:
        print("you guessed too low")
        
    else:
      break

print(f"you guessed the right number in {count} tries!congratulation")


