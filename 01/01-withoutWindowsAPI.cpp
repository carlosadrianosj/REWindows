#include <windows.h>
#include <fstream>
#include <iostream>

int main() {
    // Buffer to store the user profile path
    char userProfilePath[MAX_PATH];
    DWORD size = GetEnvironmentVariable("USERPROFILE", userProfilePath, MAX_PATH);

    if (size == 0) {
		std::cerr << "Error retrieving user profile path." << std::endl;
		return 1;
    }

    // Builds the path to the Downloads folder and sets the file name as link.txt
	std::string downloadsPath = std::string(userProfilePath) + "\\Downloads\\link.txt";

    // Creates and writes to the file
    std::ofstream file(downloadsPath);
    if (file.is_open()) {
		file << "www.google.com.br";
		file.close();
		std::cout << "file 'link.txt' created on: " << downloadsPath << std::endl;
	} else {
		std::cerr << "It was not possible to create the 'link.txt' file in: " << downloadsPath << std::endl;
		return 1;
	}

    return 0;
}
