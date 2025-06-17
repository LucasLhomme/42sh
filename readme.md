# 🐚 42sh — Unix Shell

## 📘 Description

**42sh** is the direct continuation of the **Minishell 1** and **Minishell 2** projects.  
This shell offers a complete command-line interface, inspired by `tcsh`, with an extended set of features:

- Built-in commands (`cd`, `echo`, `env`, etc.)
- Advanced redirections and operators (`|`, `&&`, `||`, `;`, `>`, `<`, `>>`, backticks)
- Command history management with arrow navigation
- Keyboard interaction support (`Ctrl` shortcuts)
- System binary detection (`which`, `where`)
- Advanced environment variable management

Developed as part of the **B-PSU-200** module at **Epitech**, this project is coded in C.

---

## 🚀 Main Features

### 🔹 Built-in Commands
- `cd`, `echo`, `exit`, `env`, `setenv`, `unsetenv`  
  ➜ Implemented in `src/command/builtin/`

### 🔹 Redirections & Operators
- Supports `>`, `<`, `>>`, `|`, `;`, `&&`, `||`, backticks  
  ➜ Implemented in `src/shell/redirection/`

### 🔹 History
- Navigate through previous commands, print or clear history  
  ➜ See `src/command/builtin/history/`

### 🔹 Environment Variables
- Manage, create, delete, and modify environment variables  
  ➜ See `src/env/` and `src/command/builtin/env/`

### 🔹 Execution
- Command parsing, forking, and error handling  
  ➜ See `src/execute_command.c`, `my_where.c`, `my_which.c`

### 🔹 Keyboard Shortcuts
- Interactive support for `Ctrl+A`, `Ctrl+E`, `Ctrl+K`, `Ctrl+L`, `Ctrl+U`, `Ctrl+W`  
  ➜ Implemented in `src/shell/`

---

## 🛠️ Compilation

```bash
make

## 📚 Documentation

# Generate documentation with Doxygen
doxygen doxygen.conf
```


## 👨‍💻 Contributors

- [Joseph Birck](https://github.com/jobirck)
- [Jawed Lahrouri](https://github.com/jawedlahrouri)
- [Grégoire Fageot](https://github.com/graigware)
- [Lucas Lhomme](https://github.com/LucasLhomme)
- [Théophille Riffé](https://github.com/inkurey-22)
