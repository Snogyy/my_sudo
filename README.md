# 🔐 my_sudo - Recreating the sudo command 👥

![Language](https://img.shields.io/badge/language-C-blue)

## 🎯 About the Project
Welcome to **my_sudo**, a project aimed at **recreating the sudo command** in C. This implementation was developed in duo and allows users to execute commands with elevated privileges and supports additional options.

## 🚀 Features
   • Execute commands as another user (default: root).  
   • Support for `-s`, `-u`, and `-g` options.  
   • Secure privilege escalation handling.  
   • Error handling

## 🛠️ Installation & Compilation

### 1️⃣ Install Required Dependencies
```bash
sudo apt-get update
sudo apt-get install build-essential
```

### 2️⃣ Clone & Compile
```bash
git clone https://github.com/Snogyy/my_sudo.git
cd my_sudo
make
./my_sudo -u user -g group command
```

## 🔗 Links
[Linux sudo Documentation](https://man7.org/linux/man-pages/man8/sudo.8.html)

---

Epitech students, beware of -42 !

