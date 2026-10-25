import json 
records = [
    {"answer":57,"tries":6},
    {"answer":12,"tries":3}
] 

with open("game_log.json","w",encoding="utf-8")as f:
    json.dump(records,f,ensure_ascii=False)
with open("game_log.json","r",encoding="utf-8")as f:
    read=json.load(f)
    print(read)