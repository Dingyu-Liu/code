a = 1
while a <= 9:
    for b in range(1, a+1):
        print(f"{b}*{a}={b*a}",end="\t")
    print()
    a=a+1
