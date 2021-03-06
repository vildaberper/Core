#pragma once

#include <string>
#include <vector>

/*
	File is a simple implementation of a file API in c++.
	All functions behave the similarly or same as the Java equivalent.

	Oracles official API was used as a reference for what functionality had to be implemented:
	https://docs.oracle.com/javase/7/docs/api/java/io/File.html

	Some new features have been added such as file reading and moving.
*/

class File{

private:

	std::string path_;

public:

	// Lists all logical drives.
	static std::vector<std::string> listDrives();

	File(const std::string& path);

	File(const File& file);

	File();

	// Tests this abstract pathname for equality with the given object.
	bool operator ==(const File& file) const;

	// Returns the file denoted by this abstract pathname.
	File operator +(const std::string& child) const;

	// Appends the file denoted by this abstract pathname.
	File& operator +=(const std::string& child);

	bool operator <(const File& file) const;
	bool operator <=(const File& file) const;
	bool operator >(const File& file) const;
	bool operator >=(const File& file) const;

	// Returns a path to parameter file relative to this file.
	std::string relativeTo(const File& file) const;

	// Converts this abstract pathname into a pathname string.
	std::string path() const;

	// Returns the name of the file or directory denoted by this abstract pathname.
	std::string name() const;

	// Returns the name - without extension, if any - of the file or directory denoted by this abstract pathname.
	std::string nameNoExtension() const;

	// Returns the extension, if any, of the file or directory denoted by this abstract pathname.
	std::string extension() const;

	// Returns the length of the file denoted by this abstract pathname.
	std::streampos size() const;

	// Returns the length of the file in human readable form denoted by this abstract pathname.
	std::string sizeReadable() const;

	// Tests whether the file or directory denoted by this abstract pathname exists.
	bool exists() const;

	// Tests whether the file or directory denoted by this abstract pathname has a parent.
	bool hasParent() const;

	// Returns the abstract pathname of this abstract pathname's parent, or the same file if this pathname does not name a parent directory.
	File parent() const;

	// Returns the file denoted by this abstract pathname.
	File child(const std::string& child) const;

	// Creates a new, empty file named by this abstract pathname if and only if a file with this name does not yet exist.
	bool create() const;

	// Renames the file denoted by this abstract pathname.
	bool rename(const std::string& name) const;

	// Creates a hard link to this file denoted by the abstract pathname.
	bool createHardLink(const File& file) const;

	// Moves the file denoted by this abstract pathname.
	bool move(const File& file) const;

	// Deletes the file or directory denoted by this abstract pathname.
	bool remove() const;

	// Tests whether the file denoted by this abstract pathname is a normal file.
	bool isFile() const;

	// Tests whether the file denoted by this abstract pathname is a directory.
	bool isDirectory() const;

	// Returns a vector of abstract pathnames denoting the files in the directory denoted by this abstract pathname.
	std::vector<File> listFiles() const;

	// Returns a vector of abstract pathnames which matches the given extension.
	std::vector<File> findDeep(std::string extension) const;

	// Creates the directory named by this abstract pathname.
	bool mkdir() const;

	// Creates the directory named by this abstract pathname, including any necessary but nonexistent parent directories.
	bool mkdirs() const;

	// Returns a vector representing the lines of content in this file.
	bool readTextFile(std::vector<std::string>& content) const;

	// Writes the vector representing content to this file.
	bool writeTextFile(const std::vector<std::string>& content) const;

};
