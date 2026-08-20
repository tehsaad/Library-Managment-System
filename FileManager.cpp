#include "FileManager.h"
#include <iostream>
#include  <filesystem>
#include  <fstream>

using namespace std;
namespace fs = std::filesystem;


bool FileManager::fileExists()
{
    string data[5] = {"Books.csv", "Users.csv", "Loans.csv", "Transactions.csv", "Logs.csv"};

    fs::path folder = "data";

	if (!fs::exists(folder)) {           //Folder         
		fs::create_directory(folder); cout << "Folder 'data' created." << endl;
    }

	for (string e : data) {              //Files                  
        fs::path filepath = folder / e;

        if (!fs::exists(filepath)) {
			ofstream file(filepath);cout << e << " created." << endl;  
        }
    return true;
}

