#pragma once
#include <filesystem>

namespace fs = std::filesystem;

class FileManager
{

public:
    bool fileExists();


    //  void createFile(const char* filename);
	// No Need Create, Automaticaly Created when Checking File Existence, if not exists.



};