text = input("请输入文本：")
words = text.split()
count ={}
values=[]
for word in words:
    count[word]=count.get(word,0)+1
print("全部出现的单词和字数为：")
print(count)

for key,value in count.items():
    
    values.append((value,key))
values.sort(reverse=True)
print("出现次数前十名的单词及其次数：")
for value,key in values[:10]:
    print(key,"出现",value,"次")