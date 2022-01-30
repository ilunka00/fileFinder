#include "pch.h"

#define MAX_THREAD 8



void TestClass::fileFind(std::string& name,std::string& path)
{
    std::thread threads[8];
    found = false;
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
            result = path;


            if (name==test) {
                found = true;
                threads_started = 0;
                resultPath = result + test;
                return;
            }

            std::string temp = path;
            path += test;
            path += "\\";            
            if (threads_started < MAX_THREAD) {
                threads[threads_started] = std::thread(&TestClass::fileFind, std::ref(name), std::ref(path));
                threads[threads_started].detach();
                threads_started++;
            }
            else {
                threads[0].join();
                threads[1].join();
                threads[2].join();
                threads[3].join();
                threads[4].join();
                threads[5].join();
                threads[6].join();
                threads[7].join();
                threads_started = 0;
                threads[threads_started] = std::thread(&TestClass::fileFind, std::ref(name), std::ref(path));
                threads[threads_started].detach();
                threads_started++;
            }
            
            
            path = temp;

        } while (FindNextFile(search_handle, &file));
        FindClose(search_handle);
        

    }
    return;
}

//std::string TestClass::fileFind(std::string name, std::string path)
//{
//    if (found) return;
//    std::string result = path;
//    result += "*";
//    WIN32_FIND_DATA file;
//
//    std::wstring widestr = std::wstring(result.begin(), result.end());
//    const wchar_t* wstrResult = widestr.c_str();
//
//    HANDLE search_handle = FindFirstFile(wstrResult, &file);
//    if (search_handle != INVALID_HANDLE_VALUE)
//    {
//        do
//        {
//            std::wstring ws(file.cFileName);
//            std::string test(ws.begin(), ws.end());
//
//            if (test == "." || test == "..") continue;
//
//            if (name == test) {
//                found = true;
//                return result + test;
//            }
//
//            std::string temp = path;
//            path += test;
//            path += "\\";
//
//            std::string tempResult = fileFind(name, path);
//
//            
//            if (tempResult.find(name) != -1) return tempResult;
//            path = temp;
//        } while (FindNextFile(search_handle, &file));
//        FindClose(search_handle);
//
//    }
//    return "";
//}

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