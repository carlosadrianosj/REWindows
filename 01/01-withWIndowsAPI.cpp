#include <windows.h>
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

    // Creates the file
    HANDLE hFile = CreateFile(downloadsPath.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::cerr << "It was not possible to create the 'link.txt' file in: " << downloadsPath << std::endl;
        return 1;
    }

    // Data to be written to the file
    const char* data = "www.google.com.br";
    DWORD bytesToWrite = (DWORD)strlen(data);
    DWORD bytesWritten;

    // Write to the file
    BOOL writeResult = WriteFile(hFile, data, bytesToWrite, &bytesWritten, NULL);
    if (!writeResult || bytesWritten != bytesToWrite) {
        std::cerr << "Failed to write to 'link.txt' file." << std::endl;
        CloseHandle(hFile);
        return 1;
    }

    // Close the file handle
    CloseHandle(hFile);
    std::cout << "File 'link.txt' created on: " << downloadsPath << std::endl;

    return 0;
}
