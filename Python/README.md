# Python

## 目录怎么用

```
Python/
├── .venv/        公共虚拟环境（已装 numpy/pandas/matplotlib/requests/Pillow/openpyxl/python-docx）
├── practice/     日常练习、小脚本 —— 单文件的东西都丢这里
├── projects/     完整项目 —— 每个项目一个子文件夹，各自带自己的 .venv
└── README.md     本文件
```

### 快速判断：该放哪？

| 情况 | 放哪 |
|---|---|
| 跟着教程敲的小例子、课后练手 | `practice/` 直接放 |
| 一个 `.py` 文件就能跑完的脚本 | `practice/` 直接放 |
| 作业 / 课设 / 有多个文件互相 import | `projects/项目名/`，并单独建 venv |
| 需要装这个项目专属的库 | `projects/项目名/`，并单独建 venv |

### 什么时候该给项目单独建 venv？

只要出现下面任意一条，就别用公共的 `.venv` 了：

- 要装公共环境里没有的库（比如 pygame、flask、django）
- 需要特定版本的库（比如某个教程要求 numpy 1.x，而公共环境是 2.x）
- 是交出去的作业，希望环境干净可复现

建法：

```powershell
cd C:\Users\29407\Desktop\code\Python\projects
py -3.13 -m venv 项目名\.venv
项目名\.venv\Scripts\python.exe -m pip install 需要的库
```

然后在 VS Code 里 `Ctrl+Shift+P` → `Python: Select Interpreter` → 选那个项目自己的 `.venv`。

---

## ⚠️ 两条硬规矩

**1. 不要移动、改名或删除 `.venv`。**

虚拟环境内部写死了绝对路径（`pyvenv.cfg` 和 `Scripts\activate` 里都是
`C:\Users\29407\Desktop\code\Python\.venv`）。一旦挪动，它就废了，pip 和
`activate` 全部失效，只能删掉重建。

同理：**不要移动 `Python` 这个文件夹本身**，否则 `.venv` 同样失效。

**2. 用 VS Code 时建议打开 `code` 这一层，而不是 `Python` 这一层。**

`code\.vscode\settings.json` 里配了 C 和 Python 的编译器/解释器。
在 `Python\.vscode\` 里我也放了一份同样的解释器配置做保险，
但打开 `code` 这层能一次拿到全部配置（C 的 F6、Python 的 F5 都可用）。

---

## 环境信息

| 项目 | 值 |
|---|---|
| Python | 3.13.16 |
| 公共 venv | `.venv`（207 MB） |
| 已装库 | numpy 2.5.4、pandas 3.0.6、matplotlib 3.11.2、requests 2.34.2、Pillow 12.3.0、openpyxl 3.1.5、python-docx 1.2.0 |
| pip 镜像 | 清华主源 + 阿里备用 |
| 编码 | `PYTHONUTF8=1`，中文和 emoji 都正常 |

### 常用命令

```powershell
# 看看装了哪些库
.venv\Scripts\python.exe -m pip list

# 往公共环境加一个库
.venv\Scripts\python.exe -m pip install 包名

# 跑一个脚本（不用激活）
.venv\Scripts\python.exe practice\hello.py
```

VS Code 里更简单：打开 `.py` 文件按 `F5`。

---

## 命名约定

- 文件名用**英文小写 + 下划线**：`hello.py`、`score_analysis.py`
  （Python 能用中文文件名，但英文更通用，也避免极少数老工具出问题）
- 项目文件夹用**英文小写 + 连字符**：`student-manager`、`sports-meet`
- 每个 `.py` 文件顶部写一行注释说明它是干嘛的
