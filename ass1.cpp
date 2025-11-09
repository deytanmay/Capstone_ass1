#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

namespace fs = std::filesystem;

std::vector<std::string> split(const std::string &line) {
    std::vector<std::string> tokens;
    std::string cur;
    bool inquote = false;
    for (char c : line) {
        if (c == '"') { inquote = !inquote; continue; }
        if (!inquote && std::isspace((unsigned char)c)) {
            if (!cur.empty()) { tokens.push_back(cur); cur.clear(); }
        } else cur.push_back(c);
    }
    if (!cur.empty()) tokens.push_back(cur);
    return tokens;
}

void showHelp() {
    std::cout <<
    "================= COMMANDS =================\n"
    " ls [path]         : List directory contents\n"
    " cd <dir>          : Change directory\n"
    " pwd               : Show current directory\n"
    " cp <src> <dst>    : Copy file\n"
    " mv <src> <dst>    : Move/Rename file\n"
    " rm [-r] <path>    : Delete file/dir (-r for recursive)\n"
    " mkdir <dir>       : Create directory\n"
    " search <pattern>  : Search filenames recursively\n"
    " chmod <mode> <f>  : Change permissions (Linux only)\n"
    " help              : Show this help\n"
    " exit              : Quit program\n"
    "============================================\n";
}

void listDir(const fs::path &p) {
    try {
        if (!fs::exists(p)) { std::cout << "Path does not exist.\n"; return; }
        for (auto &entry : fs::directory_iterator(p)) {
            std::string type = entry.is_directory() ? "DIR " : "FILE";
            uintmax_t size = 0;
            if (entry.is_regular_file()) {
                try { size = fs::file_size(entry.path()); } catch (...) { size = 0; }
            }
            auto ftime = fs::last_write_time(entry.path());
auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
    ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
);
std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

            char buf[20]; std::strftime(buf, sizeof(buf), "%F %T", std::localtime(&cftime));
            std::cout << std::setw(4) << type << " "
                      << std::setw(10) << size << " "
                      << buf << " "
                      << entry.path().filename().string() << "\n";
        }
    } catch (std::exception &e) { std::cerr << "ls error: " << e.what() << "\n"; }
}

bool copyFile(const fs::path &src, const fs::path &dst) {
    try {
        if (!fs::exists(src)) { std::cerr << "Source not found\n"; return false; }
        fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
        return true;
    } catch (std::exception &e) { std::cerr << "copy error: " << e.what() << "\n"; return false; }
}

bool moveFile(const fs::path &src, const fs::path &dst) {
    try { fs::rename(src, dst); return true; }
    catch (std::exception &e) { std::cerr << "move error: " << e.what() << "\n"; return false; }
}

bool removePath(const fs::path &p, bool recursive = false) {
    try {
        if (!fs::exists(p)) { std::cerr << "Path not found\n"; return false; }
        if (fs::is_directory(p) && recursive) fs::remove_all(p);
        else fs::remove(p);
        return true;
    } catch (std::exception &e) { std::cerr << "remove error: " << e.what() << "\n"; return false; }
}

void searchPattern(const fs::path &root, const std::string &pat) {
    try {
        for (auto &entry : fs::recursive_directory_iterator(root))
            if (entry.path().filename().string().find(pat) != std::string::npos)
                std::cout << entry.path().string() << "\n";
    } catch (std::exception &e) { std::cerr << "search error: " << e.what() << "\n"; }
}

int main() {
    fs::path cwd = fs::current_path();
    std::string line;
    showHelp();

    while (true) {
        std::cout << "\n" << cwd.string() << " > ";
        if (!std::getline(std::cin, line)) break;
        auto args = split(line);
        if (args.empty()) continue;
        std::string cmd = args[0];

        try {
            if (cmd == "exit") break;
            else if (cmd == "help") showHelp();
            else if (cmd == "pwd") std::cout << cwd << "\n";
            else if (cmd == "ls") {
    fs::path target = (args.size() > 1) ? fs::path(args[1]) : cwd;
    listDir(target);
}

            else if (cmd == "cd") {
                if (args.size() < 2) { std::cerr << "Usage: cd <dir>\n"; continue; }
                fs::path newp = fs::absolute(cwd / args[1]);
                if (fs::exists(newp) && fs::is_directory(newp)) cwd = fs::canonical(newp);
                else std::cerr << "cd: Directory not found\n";
            }
            else if (cmd == "cp") {
                if (args.size() < 3) { std::cerr << "Usage: cp <src> <dst>\n"; continue; }
                copyFile(args[1], args[2]);
            }
            else if (cmd == "mv") {
                if (args.size() < 3) { std::cerr << "Usage: mv <src> <dst>\n"; continue; }
                moveFile(args[1], args[2]);
            }
            else if (cmd == "rm") {
                bool rec = (args.size() > 2 && args[1] == "-r");
                std::string target = rec ? args[2] : args[1];
                removePath(target, rec);
            }
            else if (cmd == "mkdir") {
                if (args.size() < 2) { std::cerr << "Usage: mkdir <dir>\n"; continue; }
                fs::create_directory(args[1]);
            }
            else if (cmd == "search") {
                if (args.size() < 2) { std::cerr << "Usage: search <pattern>\n"; continue; }
                searchPattern(cwd, args[1]);
            }
            else if (cmd == "chmod") {
#ifdef _WIN32
                std::cout << "chmod not supported on native Windows. Run under WSL/Linux.\n";
#else
                if (args.size() < 3) { std::cerr << "Usage: chmod <mode> <file>\n"; continue; }
                int mode = std::stoi(args[1], nullptr, 8);
                if (::chmod(args[2].c_str(), mode) != 0) perror("chmod");
#endif
            }
            else std::cerr << "Unknown command. Type 'help' for list.\n";
        }
        catch (std::exception &e) { std::cerr << "Error: " << e.what() << "\n"; }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
