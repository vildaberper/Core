#include "File\File.h"

#include "System\StringUtils.h"
#include "File\FileHelper.cpp"

std::vector<std::string> File::listDrives(){
	return filehelper::listDrives();
}

File::File(const std::string& path){
	path_ = path;
}

File::File(const File& file){
	path_ = file.path_;
}

File::File(){
	path_ = filehelper::workingDir();
}

bool File::operator ==(const File& file) const{
	return path() == file.path();
}

File File::operator +(const std::string& child) const{
	return File::child(child);
}

File& File::operator +=(const std::string& child){
	path_ = File::child(child).path();
	return *this;
}

bool File::operator <(const File& file) const{
	return compareLess(path(), file.path());
}
bool File::operator <=(const File& file) const{
	return compareLessOrEqual(path(), file.path());
}
bool File::operator >(const File& file) const{
	return compareGreater(path(), file.path());
}
bool File::operator >=(const File& file) const{
	return compareGreaterOrEqual(path(), file.path());
}

std::string File::relativeTo(const File& file) const{
	return filehelper::relativeTo(file.path(), path());
}

std::string File::path() const{
	return path_;
}

std::string File::name() const{
	if(path().length() > 2 && path().at(path().length() - 1) == filehelper::FILE_SEPARATOR && path().at(path().length() - 2) == ':'){
		return path().substr(0, path().find_last_of(':'));
	}

	size_t i = path().find_last_of(filehelper::FILE_SEPARATOR) + 1;

	if(i > path().length()) return path();
	return path().substr(i);
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
	return filehelper::size(path());
}

std::string File::sizeReadable() const{
	return filehelper::sizeReadable(size());
}

bool File::exists() const{
	return filehelper::exists(path());
}

bool File::hasParent() const{
	return filehelper::hasParent(path());
}

File File::parent() const{
	return File(filehelper::parent(path()));
}

File File::child(const std::string& child) const{
	return File(filehelper::child(path(), child));
}

bool File::create() const{
	return filehelper::create(path());
}

bool File::rename(const std::string& name) const{
	if(path()[path().length() - 1] == filehelper::FILE_SEPARATOR){
		return filehelper::move(path(), parent().path() + name);
	}
	return filehelper::move(path(), parent().path() + filehelper::FILE_SEPARATOR + name);
}

bool File::createHardLink(const File& file) const{
	return filehelper::createHardLink(path(), file.path());
}

bool File::move(const File& file) const{
	return filehelper::move(path(), file.path());
}

bool File::remove() const{
	if(isDirectory()){
		for(File f : listFiles()){
			f.remove();
		}
	}
	return filehelper::remove(path());
}

bool File::isFile() const{
	return filehelper::isFile(path());
}

bool File::isDirectory() const{
	return filehelper::isDirectory(path());
}

std::vector<File> File::listFiles() const{
	std::vector<std::string> paths = filehelper::listFiles(path());
	std::vector<File> files;

	for(const std::string& p : paths){
		File f = File(p);
		if(f.name()[0] != '$') files.push_back(f);
	}

	return files;
}

std::vector<File> File::findDeep(std::string extension) const{
	std::vector<File> files;
	for(const File& f : listFiles()){
		if(f.isDirectory())
			for(const File& r : f.findDeep(extension))
				files.push_back(r);
		else if(f.isFile() && endsWith(toLowercase(f.name()), "." + extension))
			files.push_back(f);
	}

	return files;
}

bool File::mkdir() const{
	return filehelper::mkdir(path());
}

bool File::mkdirs() const{
	return filehelper::mkdirs(path());
}

bool File::readTextFile(std::vector<std::string>& content) const{
	return filehelper::readTextFile(path(), content);
}

bool File::writeTextFile(const std::vector<std::string>& content) const{
	return parent().mkdirs() && filehelper::writeTextFile(path(), content);
}
