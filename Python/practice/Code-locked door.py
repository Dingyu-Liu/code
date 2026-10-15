try:
    with open("password.txt","r",encoding="utf-8") as f:
        password = f.read().strip()
except FileNotFoundError:
    print("密码文件不正确")
else:
    if password == "":
        print("密码为空")
    else:
        user_input =int(input("请输入密码"))
        if user_input ==password:
            print("密码正确")
        else:
            print("密码错误")

  
