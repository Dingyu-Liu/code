
import requests

session = requests.Session()
session.trust_env = False  

URL = "https://api.github.com/users/Dingyu-Liu"

try:
    resp = session.get(URL, timeout=10)
    print(f"状态码：{resp.status_code}")

    if resp.status_code != 200:
        print(f"请求失败，返回：{resp.text[:200]}")
        raise SystemExit(1)

except requests.exceptions.Timeout:
    print("请求超时了，检查网络")
    raise SystemExit(1)
except requests.exceptions.RequestException as e:
    print(f"请求出错：{e}")
    raise SystemExit(1)


data = resp.json()

name = data["login"]
repos = data["public_repos"]
followers = data["followers"]
created = data["created_at"]

print(f"用户名   : {name}")
print(f"仓库数   : {repos}")
print(f"粉丝数   : {followers}")
print(f"注册时间 : {created}")


print("\n--- 公开仓库列表 ---")
repos_resp = session.get(f"https://api.github.com/users/{name}/repos", timeout=10)

if repos_resp.status_code == 200:
    repo_list = repos_resp.json()
    for repo in repo_list:
        repo_name = repo.get("name", "?")
        lang = repo.get("language") or "无"
        print(f"  {repo_name:<30} 语言={lang}")
else:
    print(f"  取仓库列表失败：{repos_resp.status_code}")