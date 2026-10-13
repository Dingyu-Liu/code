# code — 编程代码总目录

原路径 `Desktop\编程`，2026-10-12 整理并改名为 `code`。

---

## ⚠️ 最重要的一条规则：路径里不要出现中文

**这个目录名必须保持英文 `code`，里面所有目录和源文件也都要用英文名。**

原因：系统 ANSI 代码页是 **936 (GBK)**，GCC 把 `-o` 参数交给链接器 `ld.exe` 时，
路径里的中文会变成乱码，导致编译失败：

```
ld.exe: cannot open output file C:\...\C����\��ϰ\output\texe.exe: No such file or directory
collect2.exe: error: ld returned 1 exit status
```

实测结论：

| 情况 | 结果 |
|---|---|
| 英文路径 + 绝对输出路径 | ✅ 正常 |
| 中文路径 + **相对**输出路径（`cd` 进去后 `gcc x.c -o x.exe`） | ✅ 正常 |
| 中文路径 + **绝对**输出路径（VS Code 任务、cmake、make） | ❌ 报错 |

VS Code 的编译任务传的是绝对路径，所以**在中文目录里按 F6 一定会失败**。

另外注意：编译产物的名字取自**源文件名**。所以 `运动会成绩管理系统.c`
如果直接编译，产物就是中文名，同样会失败——需要先改成英文名。

---

## 目录结构

```
code/
├── README.md              本文件
├── C/                     C 语言
│   ├── practice/          日常练习、小实验
│   └── projects/          成规模的完整项目
├── C++/                   C++
│   └── homework/          课后习题、作业
├── Python/                Python 脚本与项目
│   ├── .venv/             公共虚拟环境（别动它，见下）
│   ├── practice/          日常练习、小脚本
│   └── projects/          完整项目，每个自带 .venv
├── MCU/                   单片机（Keil / STM32 等）
├── coursework/            课程设计、大作业
│   └── sports-meet/       运动会成绩管理系统（别人发的作业，2023）
└── _archive/              暂时不确定去留的东西
```

### 当前内容

| 路径 | 内容 |
|---|---|
| `C/practice/texe.c` | hello world 起步练习 |
| `C++/homework/C++课后习题解答.docx` | C++ 课后习题（第 7、9、11… 题源码 + 运行截图） |
| `Python/practice/hello.py` | 环境自检脚本（也能当 hello world 用） |
| `coursework/sports-meet/` | 运动会成绩管理系统：源码 + 已编译 exe + `system.txt` 数据文件 |

> Python 部分怎么组织、什么时候该单独建 venv，见
> [`Python/README.md`](Python/README.md)。**`Python/.venv` 不能移动或改名**，
> 它内部写死了绝对路径。

> `coursework/sports-meet/` 里的文件保留了原来的**中文文件名**（因为那是别人
> 交来的原始作业，改名可能影响提交）。如果要重新编译它，先把 `.c` 改成英文名，
> 例如 `sports-meet.c`；注意程序内部把数据文件名硬编码为 `system.txt`，这个不能改。

---

## 开发环境

| 项目 | 值 |
|---|---|
| 编译器 | GCC 16.2.0 (MinGW-w64 x86_64-ucrt-posix-seh) |
| 调试器 | GDB 18.1 |
| 构建工具 | mingw32-make、cmake |
| 安装位置 | `C:\Users\29407\AppData\Local\Programs\mingw64\bin` |
| PATH | 已加入用户级 PATH |

### Python

| 项目 | 值 |
|---|---|
| 主版本 | **Python 3.13.16**（`C:\Users\29407\AppData\Local\Programs\Python\Python313`） |
| 旧版本 | Python 3.8.10（Microsoft Store 版，保留作参考） |
| 版本切换 | 用 `py` 启动器：`py -3.13` / `py -3.8`，`python` 默认指向 3.13 |
| 虚拟环境 | `code\Python\.venv`（VS Code 已默认指向它） |
| 已装库 | numpy 2.5.4、pandas 3.0.6、matplotlib 3.11.2、requests 2.34.2、Pillow 12.3.0、openpyxl 3.1.5、python-docx 1.2.0 |
| pip 镜像 | 清华为主源、阿里为备用（配置在 `%APPDATA%\pip\pip.ini`） |
| 编码 | 已设 `PYTHONUTF8=1`，默认 UTF-8，中文和 emoji 都不会再报 `UnicodeEncodeError` |

> **为什么要有虚拟环境**：库装在 `.venv` 里，不会污染全局 Python。
> 在 VS Code 里打开 `code` 目录会自动启用它；用命令行则先激活：
>
> ```powershell
> cd C:\Users\29407\Desktop\code\Python
> .\.venv\Scripts\Activate.ps1
> python your_script.py
> ```
>
> 如果不想每次都激活，也可以直接用完整路径：
> `code\Python\.venv\Scripts\python.exe your_script.py`

---

## 怎么运行代码

用 VS Code 打开 `code` 这个目录，然后打开任意 `.c` / `.cpp` 文件：

| 快捷键 | 作用 |
|---|---|
| `F6` | 编译并运行（产物在该文件同级的 `output\` 目录） |
| `F5` | 用 GDB 调试 |
| `F8` | 在外部终端运行 |
| `F7` | 自定义参数编译并运行 |

命令行方式：

```powershell
cd C:\Users\29407\Desktop\code\C\practice
gcc -Wall -Wextra -g3 texe.c -o texe.exe
.\texe.exe
```

Python 文件直接在 VS Code 里按 `F5` 运行（会自动用 `code\Python\.venv`），
或在已激活虚拟环境的终端里 `python 文件名.py`。

---

## 新建项目的约定

1. 进对应语言目录，例如 C 语言项目放 `C/projects/`
2. 项目目录用**英文小写 + 连字符**，例如 `student-manager`、`snake-game`
3. 源文件也用英文名，例如 `main.c`、`student.c`
4. 在项目目录里按 F6 即可，产物自动进 `output/`
5. Python 项目如果要用到别的库，建议在项目里单独建虚拟环境：
   `py -3.13 -m venv .venv`，别往全局 Python 里装

---

## 整理记录

- 整理前完整备份：`C:\Users\29407\Documents\deepseek-harness\default-workspace\编程-整理前备份-20261012-165410.zip`
- 删除项：`Untitled-1.c`、`Untitled-2.c`（0 字节）、`十九点.c`（内容仅为文件名）、
  `IDLE (Python 3.8).lnk`（快捷方式已失效）、与解压文件夹完全重复的 `运动会成绩管理系统 (1).zip`
- VS Code 配置备份：`%APPDATA%\Code\User\settings.json.bak-20261012-164411`
- 2026-10-12 追加：安装 Python 3.13.16、建 `Python\.venv` 并装常用库、
  设 `PYTHONUTF8=1`、配 pip 国内镜像、清理重复的 Pylance 2024.3.2
