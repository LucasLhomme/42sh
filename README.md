# 🐚 42sh — Complete Unix Shell in C

[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Makefile-orange.svg)](Makefile)
[![Module: B-PSU-200](https://img.shields.io/badge/Epitech-B--PSU--200-blue.svg)](https://www.epitech.eu/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Academic Year: 2024-2025](https://img.shields.io/badge/Academic%20Year-2024--2025%20(Tek1)-blueviolet.svg)](#)

> **42sh is the final capstone Unix System Programming project of Epitech's first year.** It is a full-featured POSIX-compliant command-line interpreter written in C from scratch, expanding upon Minishell 1 and Minishell 2.

---

## 🎯 Project Overview

The objective of **42sh** is to build a robust, production-grade Unix shell capable of parsing complex shell grammar, handling job control, managing environment state, orchestrating inter-process communications (IPC), and providing an ergonomic interactive line editor.

### Academic Context
- **Academic Year:** First Year / Tek1 (2024 – 2025)
- **Institution:** Epitech (European Institute of Information Technology)
- **Module:** B-PSU-200 — Unix System Programming
- **Language:** C (C99 / GNU99)
- **Rules:** Adherence to Epitech C Coding Style, zero memory leaks (`valgrind` clean).

---

## ✨ Features

### 1. Command Execution & Process Management
- **Binary Resolution:** Resolves commands from directories declared in the `PATH` environment variable.
- **Direct Execution:** Executes local binaries via relative (`./bin`) and absolute (`/usr/bin/bin`) paths.
- **Process Isolation:** Clean `fork()` and `execve()` execution, with parent wait routines (`waitpid`) inspecting exit status codes (`WIFEXITED`, `WEXITSTATUS`, `WIFSIGNALED`, `WTERMSIG`) and handling signals (e.g., `SIGSEGV` segmentation faults, `SIGFPE` floating-point exceptions).

### 2. Pipelines & Redirections
- **Multi-stage Pipelines:** Arbitrary pipeline chains (`cmd1 | cmd2 | cmd3 | ...`) using POSIX `pipe()` and `dup2()`.
- **File Redirections:**
  - Standard output overwrite: `cmd > file`
  - Standard output append: `cmd >> file`
  - Standard input redirect: `cmd < file`
  - Heredoc input: `cmd << delimiter`
- **Chained Redirections:** Support for mixed redirections (e.g., `cat < input.txt | grep "pattern" >> output.txt`).

### 3. Grammar & Command Separators
- **Sequential Execution:** Semicolon operator (`;`).
- **Conditional Logic:**
  - Logical AND (`&&`): executes subsequent command only if previous exited with status 0.
  - Logical OR (`||`): executes subsequent command only if previous exited with non-zero status.
- **Grouping & Parentheses:** Command priority grouping using parentheses `(cmd1 && cmd2) || cmd3`.

### 4. Built-in Commands
- `cd [dir | - | ~]`: Changes current directory, updating `PWD` and `OLDPWD`.
- `setenv [VAR [VALUE]]`: Sets or creates environment variables.
- `unsetenv VAR [VAR2 ...]`: Deletes environment variables.
- `env`: Displays the current environment table.
- `echo [-n] [args ...]`: Prints text to standard output, supporting escape sequences and variable expansion.
- `exit [status]`: Terminates shell session with an optional exit code.
- `which` / `where`: Locates executables in the system PATH.
- `alias` / `unalias`: Defines and manages command abbreviations.
- `history`: Lists executed command history.

### 5. Advanced Expansion & Globbing
- **Environment Variable Expansion:** Dynamic interpolation (`$VAR`, `$?` for last exit status, `$$` for PID).
- **Wildcard Globbing:** Filename pattern matching using `*`, `?`, and character sets `[...]`.
- **Tilde Expansion:** Resolves `~` to `$HOME`.

---

## 🏛️ Architecture

```text
42sh Architecture:
[User Input] 
     │
     ▼
[Lexer / Tokenizer]   ──► Splits raw line into tokens (WORDS, PIPES, REDIRS, LOGIC)
     │
     ▼
[Parser & AST Build]  ──► Constructs Abstract Syntax Tree obeying operator precedence (&&, ||, |, ;)
     │
     ▼
[AST Evaluator]       ──► Traverses AST nodes, forks processes, binds file descriptors via dup2
     │
     ▼
[Execution & Status]  ──► Reaps child processes (waitpid), maps signals, sets $? status
```

---

## 🛠️ Compilation & Installation

Built using standard GNU Make:

```bash
# Compile the shell binary
make

# Clean object files
make clean

# Full rebuild
make re
```

The resulting executable `42sh` is generated at the repository root.

---

## 💻 Usage Examples

### Interactive Shell
```bash
$ ./42sh
42sh> ls -la | grep "Makefile"
-rw-r--r-- 1 user user 1528 Nov 16 10:00 Makefile
42sh> echo "Status: $?"
Status: 0
```

### Pipeline & Conditional Operators
```bash
42sh> mkdir -p /tmp/test && cd /tmp/test && touch file.txt && ls -l file.txt
-rw-r--r-- 1 user user 0 Nov 16 10:01 file.txt
42sh> cat < file.txt || echo "File is empty or failed"
File is empty or failed
```

---

## 📜 License

Licensed under the **MIT License with mandatory attribution** to Lucas Lhomme (Crabe).
