import requests
import json

session = requests.Session()
session.trust_env = False  

r = session.get("https://api.github.com/users/Dingyu-Liu")
print(r.status_code)

data = r.json()
print(data["login"])
print(data["public_repos"])
print(data["followers"])
print(data["created_at"])

print(json.dumps(data, ensure_ascii=False, indent=2))