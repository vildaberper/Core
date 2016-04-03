#include <sys/stat.h>
#include <Windows.h>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

#include "dirent.h"

namespace filehelper{
	static const char FILE_SEPARATOR = '\\';

	static const std::vector<std::string> FILE_SIZES = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

	// Converts bytes into human readable form.
	static std::string sizeReadable(const std::streampos& size){
		double s = double(size);
		size_t i = 0;

		for(; i < FILE_SIZES.size() - 1 && s > 1024; s /= 1024, i++);

		return (std::to_string(s) + FILE_SIZES[i]);
	}

	// Lists all logical drives.
	static std::vector<std::string> listDrives(){
		DWORD test = GetLogicalDrives();
		std::vector<std::string> drives;

		for(char i = 'A'; i <= 'Z'; i++){
			if((test & (1 << (i - 'A')))){
				drives.push_back(std::string(1, i) + ':' + FILE_SEPARATOR);
			}
		}

		return drives;
	}

	// Lists all files in a directory.
	static std::vector<std::string> listFiles(const std::string& path){
		DIR *dir;
		struct dirent *ent;
		std::vector<std::string> files;

		if((dir = opendir(path.data())) != nullptr){
			while((ent = readdir(dir)) != nullptr){
				if(ent->d_name[0] == '.' && ((ent->d_name[1] == 0) || (ent->d_name[1] == '.' && ent->d_name[2] == 0))){
					continue;
				}

				if(path[path.length() - 1] == FILE_SEPARATOR){
					files.push_back(path + ent->d_name);
				}
				else{
					files.push_back(path + FILE_SEPARATOR + ent->d_name);
				}
			}
			closedir(dir);
			delete ent;
		}

		return files;
	}

	// Test wheather the path is a file.
	static bool isFile(const std::string& path) {
		struct stat s;

		return stat(path.data(), &s) == 0 && (s.st_mode & S_IFREG) != 0;
	}

	// Test wheather the path is a directory.
	static bool isDirectory(const std::string& path) {
		struct stat s;

		return stat(path.data(), &s) == 0 && (s.st_mode & S_IFDIR) != 0;
	}

	// File or directory size in bytes.
	static std::streampos size(const std::string& path){
		std::streampos size_ = 0;

		if(isDirectory(path)){
			for(std::string child : listFiles(path)){
				size_ += size(child);
			}
			return size_;
		}

		std::ifstream file(path, std::ios_base::binary);

		file.seekg(0, std::ios_base::end);
		size_ = file.tellg();
		file.close();

		return size_;
	}

	// File has parent (C:\parent = true, C:\ = false).
	static bool hasParent(const std::string& path){
		return path[path.length() - 1] != FILE_SEPARATOR;
	}

	// Parent of path (C:\parent\path)
	static std::string parent(const std::string& path){
		std::string p = path.substr(0, path.find_last_of(FILE_SEPARATOR));

		if(path.find_first_of(FILE_SEPARATOR) == path.find_last_of(FILE_SEPARATOR)){
			p += FILE_SEPARATOR;
		}

		return p;
	}

	// Child of path (C:\path\child).
	static std::string child(const std::string& path, const std::string& child){
		if(path[path.length() - 1] == FILE_SEPARATOR){
			return path + child;
		}

		return path + FILE_SEPARATOR + child;
	}

	// Check if file exists.
	static bool exists(const std::string& filename){
		if(isDirectory(filename)){
			return true;
		}

		std::ifstream file(filename);

		bool good = file.good();

		file.close();

		return good;
	}

	// Create file.
	static bool create(const std::string& path){
		if(exists(path)){
			return false;
		}

		std::ofstream out(path);
		out.close();

		return isFile(path);
	}

	// Remove file.
	static bool remove(const std::string& path){
		if(isDirectory(path)){
			return _rmdir(path.data()) == 0;
		}
		else{
			return std::remove(path.data()) == 0;
		}
	}

	// Move file.
	static bool move(const std::string& path, const std::string& newPath){
		return std::rename(path.data(), newPath.data()) == 0;
	}

	// Current working directory.
	static std::string workingDir(){
		char dir[MAX_PATH];

		return parent(std::string(dir, GetModuleFileName(nullptr, dir, MAX_PATH)));
	}

	// Create directory.
	static bool mkdir(const std::string& path){
		return _mkdir(path.data()) == 0;
	}

	// Create directory and all parent directories.
	static bool mkdirs(const std::string& path){
		if(!hasParent(path) || isDirectory(path)){
			return true;
		}

		return mkdirs(parent(path)) && mkdir(path);
	}

	// Returns a vector<string> with lines read from file.
	static std::vector<std::string> readTextFile(const std::string& filename){
		std::vector<std::string> content;

		std::string line;
		std::ifstream file(filename);

		if(file.is_open()){
			while(std::getline(file, line)){
				content.push_back(line);
			}
			file.close();
		}

		return content;
	}

	// Write a file with lines vector<string>.
	static bool writeTextFile(const std::string& filename, const std::vector<std::string>& content){
		std::ofstream ofs;

		ofs.open(filename.data(), std::ios_base::out | std::ios_base::trunc);
		if(ofs.is_open()){
			for(std::string line : content){
				ofs << line << '\n';
			}
			ofs.close();
		}
		else{
			return false;
		}

		return true;
	}
}
