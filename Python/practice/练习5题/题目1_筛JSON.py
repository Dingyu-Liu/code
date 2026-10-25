import json
from pathlib import Path
DATA = Path(__file__).resolve().parent / "students.json"

try:
    with open(DATA, "r", encoding="utf-8") as f:
        users = json.load(f)
except FileNotFoundError:
    print(f"找不到文件:{DATA}")
    raise SystemExit(1)
except json.JSONDecodeError as e:
    print(f"JSON格式错误:{e}")
    raise SystemExit(1)

print(f"读进来 {len(users)} 条记录")
result = []
for user in users:
    if user["score"]>= 60:
        result.append({
            "name":user["name"],
            "score":user["score"],
        })

print(f"筛选后剩 {len(result)} 条")
print(result)
OUT = Path(__file__).resolve().parent/"passed.json"
with open(OUT,"w",encoding="utf-8")as f:
    json.dump(result,f,ensure_ascii=False,indent=2)
print(f"已写入{OUT.name}")




