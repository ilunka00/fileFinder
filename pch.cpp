#include "pch.h"

std::string TestClass::fileFind(std::string name)
{
    std::string result = "C:\\";
    WIN32_FIND_DATA file;
    HANDLE search_handle = FindFirstFile(L"C:\\*", &file);
    if (search_handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            result = "C:\\";

            std::wstring ws(file.cFileName);
            std::string test(ws.begin(), ws.end());

            if (test == "."||test=="..") continue;

            if (name==test) {
                return result + test;
            }

            std::string temp = result;
            result += test;
            result += "\\";
            
            std::string tempResult = fileFind(name, result);
            if (tempResult.find(name) != -1) return tempResult;

            result = temp;

        } while (FindNextFile(search_handle, &file));
        FindClose(search_handle);
        

    }
    return "";
}

std::string TestClass::fileFind(std::string name, std::string path)
{
    std::string result = path;
    result += "*";
    WIN32_FIND_DATA file;

    std::wstring widestr = std::wstring(result.begin(), result.end());
    const wchar_t* wstrResult = widestr.c_str();

    HANDLE search_handle = FindFirstFile(wstrResult, &file);
    if (search_handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            std::wstring ws(file.cFileName);
            std::string test(ws.begin(), ws.end());

            if (test == "." || test == "..") continue;

            if (name == test) {
                return result + test;
            }

            std::string temp = path;
            path += test;
            path += "\\";

            std::string tempResult = fileFind(name, path);

            
            if (tempResult.find(name) != -1) return tempResult;
            path = temp;
        } while (FindNextFile(search_handle, &file));
        FindClose(search_handle);

    }
    return "";
}

void TestClass::testing() {
    WIN32_FIND_DATA file;
    HANDLE search_handle = FindFirstFile(L"C:\\ProgramData\\*", &file);
    if (search_handle)
    {
        do
        {
            std::wcout << file.cFileName << std::endl;
        } while (FindNextFile(search_handle, &file));
        CloseHandle(search_handle);

    }
}