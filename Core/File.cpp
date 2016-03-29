#include "File.h"

#include "FileHelper.h"

std::vector<std::string> File::listDrives(){
	return file::listDrives();
}

File::File(const std::string& path){
	path_ = path;
}

File::File(){
	path_ = file::workingDir();
}

std::string File::path() const{
	return path_;
}

std::string File::name() const{
	if(path().length() > 2 && path().at(path().length() - 1) == file::FILE_SEPARATOR && path().at(path().length() - 2) == ':'){
		return path().substr(0, path().find_last_of(':'));
	}

	return path().substr(path().find_last_of(file::FILE_SEPARATOR) + 1);
}

std::string File::nameNoExtension() const{
	std::string name = File::name();
	size_t last = name.find_last_of('.');

	return name.substr(0, last == std::string::npos ? name.length() : last);
}

std::string File::extension() const{
	std::string name = File::name();
	size_t last = name.find_last_of('.');

	return last == std::string::npos ? "" : name.substr(last + 1);
}

std::streampos File::size() const{
	return file::size(path());
}

std::string File::sizeReadable() const{
	return file::sizeReadable(size());
}

bool File::exists() const{
	return file::exists(path());
}

bool File::hasParent() const{
	return file::hasParent(path());
}

File File::parent() const{
	return File(file::parent(path()));
}

File File::child(const std::string& child) const{
	return File(file::child(path(), child));
}

bool File::create() const{
	return file::create(path());
}

bool File::rename(const std::string& name) const{
	if(path()[path().length() - 1] == file::FILE_SEPARATOR){
		return file::move(path(), parent().path() + name);
	}
	return file::move(path(), parent().path() + file::FILE_SEPARATOR + name);
}

bool File::move(const File& file) const{
	return file::move(path(), file.path());
}

bool File::remove() const{
	if(isDirectory()){
		for(File f : listFiles()){
			f.remove();
		}
	}
	return file::remove(path());
}

bool File::isFile() const{
	return file::isFile(path());
}

bool File::isDirectory() const{
	return file::isDirectory(path());
}

std::vector<std::string> File::listFiles() const{
	return file::listFiles(path());
}

bool File::mkdir() const{
	return file::mkdir(path());
}

bool File::mkdirs() const{
	return file::mkdirs(path());
}

std::vector<std::string> File::readTextFile() const{
	return file::readTextFile(path());
}

bool File::writeTextFile(const std::vector<std::string>& content) const{
	return parent().mkdirs() && file::writeTextFile(path(), content);
}
