import os
import sys
from dotenv import load_dotenv
from openai import OpenAI
from openai.types.chat import ChatCompletionMessageParam
from pathlib import Path
import json


def stream_reply(client,messages):
    stream = client.chat.completions.create(
        model="deepseek-flash",
        messages=messages,
        stream=True,
        stream_options={"include_usage": True},
    )
    full = ""
    last_usage = None
    thinking_started = False    #【思考过程】是否已经打印过
    answer_started = False      #【AI】是否已经打印过
    
    for chunk in stream:
        if chunk.usage:
            last_usage = chunk.usage
        if not chunk.choices:
            continue
        delta = chunk.choices[0].delta
        
        think = getattr(delta,"reasoning_content",None)
        if think:
            if not thinking_started:
                print("【思考过程】:",end="",flush=True)
                thinking_started = True
            print(think,end="",flush=True)
    
        if delta.content:
            if not answer_started:
                if thinking_started:
                    print()
                print("【AI】:",end="",flush=True)
                answer_started = True
            print(delta.content, end="", flush=True)
            full += delta.content
    print("\n") 
    if last_usage:
        print(f"  [用量 {last_usage.total_tokens} token]")
    return full

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
        messages: list[ChatCompletionMessageParam] = [{"role": "system", "content": "你是一名ai助手,请始终保持中文思考和回复"}]
else:
    messages: list[ChatCompletionMessageParam] = [{"role": "system", "content": "你是一名ai助手,请始终保持中文思考和回复"}]
try:
    while True:
        user_input = input("你：")
        if user_input == "退出":
            break

        messages.append({"role": "user", "content": user_input})
        try:
            reply = stream_reply(client,messages)
        except Exception as e:
            print(f"出错了：{e}")
            messages.pop()
            continue
        messages.append({"role": "assistant", "content": reply})   # 3. 记下 AI 说的
except (KeyboardInterrupt, EOFError):
    print("\n(收到退出信号)")
finally:                                        # ★ 不管上面发生什么，这里都会跑
    with open(HISTORY, "w", encoding="utf-8") as f:
        json.dump(messages, f, ensure_ascii=False, indent=2)
    print(f"对话已保存到 {HISTORY.name}")




