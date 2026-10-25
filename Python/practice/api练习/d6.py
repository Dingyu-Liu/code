import os
import sys
from dotenv import load_dotenv
from openai import OpenAI
from openai.types.chat import ChatCompletionMessageParam
from pathlib import Path
import json
from pathlib import Path

ENV = Path(__file__).resolve().parent / ".env"
load_dotenv(ENV)          # 明确告诉它去哪找

key = os.environ.get("DEEPSEEK_API_KEY")
if not key:
    raise SystemExit("没找到 DEEPSEEK_API_KEY,检查一下 .env 文件")
client = OpenAI(
    api_key=key,
    base_url="https://api.deepseek.com",
)

HISTORY = Path(__file__).resolve().parent / "chat_history.json"

# 启动时：如果有历史，读回来
if HISTORY.exists():
    try:
        with open(HISTORY, "r", encoding="utf-8") as f:
            messages = json.load(f)
    except Exception:
        messages: list[ChatCompletionMessageParam] = [{"role": "system", "content": "你是一名ai助手"}]
else:
    messages: list[ChatCompletionMessageParam] = [{"role": "system", "content": "你是一名ai助手"}]
try:
    while True:
        user_input = input("你：")
        if user_input == "退出":
            break

        messages.append({"role": "user", "content": user_input})   # 1. 记下用户说的
        try:
            resp = client.chat.completions.create(
                model="deepseek-flash",
                messages= messages ,                                      # 2. 整段历史发过去
            )
        except Exception as e:
            messages.pop()
            print(f"出错了：{e}")
            continue 
        msg = resp.choices[0].message
        thinking = getattr(msg, "reasoning_content", None)
        reply = resp.choices[0].message.content or ""
        print("【思考过程】:",thinking)
        print("AI:", reply)

        messages.append({"role": "assistant", "content": reply})   # 3. 记下 AI 说的
except (KeyboardInterrupt, EOFError):
    print("\n(收到退出信号)")
finally:                                        # ★ 不管上面发生什么，这里都会跑
    with open(HISTORY, "w", encoding="utf-8") as f:
        json.dump(messages, f, ensure_ascii=False, indent=2)
    print(f"对话已保存到 {HISTORY.name}")




