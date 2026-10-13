text = input("请输入文本：")
count ={}
values=[]
for ch in text:
    count[ch]=count.get(ch,0)+1
print("全部出现的汉字和字数为：")
print(count)

for key,value in count.items():
    
    values.append((value,key))
values.sort(reverse=True)
print("出现次数前十名的汉字及其次数：")
for value,key in values[:10]:
    print(key,"出现",value,"次")