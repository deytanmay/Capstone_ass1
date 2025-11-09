🗂️ File Explorer Application

Course: Linux Operating System (Assignment 1)
Student: Tanmay Dey
Branch: Electronics and Communication Engineering (ECE)
Institution: CTTC Bhubaneswar

📘 Project Overview

This project is a console-based File Explorer Application written in C++17.
It allows users to interact with the file system through a set of simple commands, similar to a Linux terminal file manager.

The application can list, create, copy, move, delete, search, and navigate files and directories.
It is designed to run on both Linux and Windows 11 (via WSL or MinGW/MSYS2).

🎯 Objective

To develop a console-based file explorer in C++ that interfaces with the Linux (or Windows) operating system to manage files and directories using basic system calls and std::filesystem.

🧩 Features Implemented
Feature	Description
List Directory (ls)	Displays files and directories in the current or specified path.
Change Directory (cd)	Navigate between directories.
Show Path (pwd)	Displays the current working directory.
Create Directory (mkdir)	Creates a new folder.
Copy File (cp)	Copies a file from one location to another.
Move / Rename (mv)	Moves or renames a file or directory.
Delete (rm, rm -r)	Removes files or directories (recursive supported).
Search (search)	Recursively searches for files containing a pattern.
Change Permissions (chmod)	Changes file permissions (Linux only).
Help (help)	Displays the list of available commands.
Exit (exit)	Exits the program.
🛠️ Tools & Technologies

Language: C++17

Compiler: g++ (GNU C++ Compiler)

Libraries: <filesystem>, <iostream>, <iomanip>, <sstream>

Platforms: Linux (Ubuntu / WSL), Windows 11 (MSYS2 / MinGW)

⚙️ Installation & Setup
🔹 Option 1: On Linux / WSL (Recommended)

Open terminal

Install g++

sudo apt update
sudo apt install g++


Clone or create project folder

mkdir file-explorer && cd file-explorer


Add source file
Save your main.cpp (provided code) in this folder.

Compile

g++ -std=c++17 -O2 -Wall -o file_explorer main.cpp


Run

./file_explorer

🔹 Option 2: On Windows (MSYS2 / MinGW)

Install MSYS2 from https://www.msys2.org

Open “MSYS2 MinGW 64-bit” terminal

Install g++

pacman -Syu
pacman -S mingw-w64-x86_64-gcc


Compile

g++ -std=c++17 -O2 -Wall -o file_explorer.exe main.cpp


Run

./file_explorer.exe

💻 Usage Instructions

When you start the program, a prompt will appear showing the current working directory.

🧠 Available Commands
Command	Description	Example
ls	List files and folders	ls, ls /home/tanmay
pwd	Show current directory	pwd
cd <dir>	Change directory	cd Documents
mkdir <dir>	Create new directory	mkdir newfolder
cp <src> <dst>	Copy file	cp file.txt backup.txt
mv <src> <dst>	Move / rename file	mv a.txt b.txt
rm <file>	Delete file	rm old.txt
rm -r <dir>	Delete folder recursively	rm -r folder
search <pattern>	Search for a file name	search report
chmod <mode> <file>	Change permissions (Linux only)	chmod 755 script.sh
help	Display all commands	help
exit	Quit the program	exit

🧭 Learning Outcomes

Practical understanding of Linux file system operations using C++.

Experience with std::filesystem library.

Understanding of file I/O, directory traversal, permissions, and error handling.

Hands-on practice in building command-line interfaces.

🚀 Future Enhancements

Add colored output (like Linux ls).

Implement directory tree view.

Add file preview (show first few lines of a text file).

Integrate ncurses-based UI for arrow-key navigation.

👨‍💻 Author

Name: Tanmay Dey
Branch: Electronics and Communication Engineering
Institute: Central Tool Room & Training Centre (CTTC), Bhubaneswar
Year: 2025

🏁 Conclusion

This File Explorer Application demonstrates fundamental Linux OS and C++ concepts such as file handling, directory management, and system-level operations.
It bridges theoretical learning with real-world system programming skills.
