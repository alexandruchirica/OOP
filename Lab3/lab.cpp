#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <string>

void trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

bool endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

class FileMonitor {
private:
    std::string monitoredPath;
    std::map<std::string, time_t> fileTimestamps;

    time_t getFileModificationTime(const std::string& filePath) {
        struct stat fileInfo;
        if (stat(filePath.c_str(), &fileInfo) != 0) {
            return 0; 
        }
        return fileInfo.st_mtime;
    }

    bool isRegularFile(const std::string& filePath) {
        struct stat fileInfo;
        if (stat(filePath.c_str(), &fileInfo) != 0) {
            return false; 
        }
        return S_ISREG(fileInfo.st_mode);
    }

public:
    FileMonitor(const std::string& path) : monitoredPath(path) {
        if (DIR* dir = opendir(monitoredPath.c_str())) {
            closedir(dir); 
            loadInitialTimestamps();
        } else {
            std::cerr << "Error: Path does not exist.\n";
            exit(1);
        }
    }

    void loadInitialTimestamps() {
        fileTimestamps.clear();
        if (DIR* dir = opendir(monitoredPath.c_str())) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                std::string filename = entry->d_name;
                std::string fullPath = monitoredPath + "/" + filename;

                if (isRegularFile(fullPath)) {
                    fileTimestamps[filename] = getFileModificationTime(fullPath);
                }
            }
            closedir(dir);
        }
    }

    void commit() {
        loadInitialTimestamps();
        std::cout << "Snapshot updated successfully.\n";
    }

    void info(const std::string& filename) {
        std::string fullPath = monitoredPath + "/" + filename;

        struct stat fileInfo;
        if (stat(fullPath.c_str(), &fileInfo) != 0) {
            std::cerr << "Error: File does not exist.\n";
            return;
        }

        std::cout << "File: " << filename << "\n";
        std::cout << "Size: " << fileInfo.st_size << " bytes\n";
        std::cout << "Last modified: " << std::put_time(std::localtime(&fileInfo.st_mtime), "%Y-%m-%d %H:%M:%S") << "\n";

        if (endsWith(filename, ".txt")) {
            std::ifstream file(fullPath);
            int lines = 0, words = 0, chars = 0;
            std::string line;

            while (std::getline(file, line)) {
                lines++;
                words += std::count_if(line.begin(), line.end(), [](char c) { return std::isspace(c); }) + 1;
                chars += line.length();
            }

            std::cout << "Lines: " << lines << "\n";
            std::cout << "Words: " << words << "\n";
            std::cout << "Characters: " << chars << "\n";
        }
    }

    void status() {
        if (DIR* dir = opendir(monitoredPath.c_str())) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                std::string filename = entry->d_name;
                std::string fullPath = monitoredPath + "/" + filename;

                if (isRegularFile(fullPath)) {
                    time_t currentTime = getFileModificationTime(fullPath);

                    if (fileTimestamps.find(filename) == fileTimestamps.end()) {
                        std::cout << filename << ": New file\n";
                    } else if (fileTimestamps[filename] != currentTime) {
                        std::cout << filename << ": Changed\n";
                    } else {
                        std::cout << filename << ": No changes\n";
                    }
                }
            }
            closedir(dir);
        }
    }
};

int main() {
    std::string folderPath = "MonitoredFolder";
    FileMonitor monitor(folderPath);

    std::cout << "File Monitoring System Initialized.\n";
    std::cout << "Commands:\n";
    std::cout << "1. commit - Update the snapshot\n";
    std::cout << "2. info <filename> - Show file information\n";
    std::cout << "3. status - Show changed files\n";
    std::cout << "4. exit - Quit the program\n";

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        trim(command);

        if (command == "commit") {
            monitor.commit();
        } else if (command.find("info") == 0) { 
            std::string filename = command.substr(5);
            trim(filename);
            if (!filename.empty()) {
                monitor.info(filename);
            } else {
                std::cerr << "Error: No filename provided.\n";
            }
        } else if (command == "status") {
            monitor.status();
        } else if (command == "exit") {
            break;
        } else {
            std::cerr << "Invalid command. Try again.\n";
        }
    }

    return 0;
}