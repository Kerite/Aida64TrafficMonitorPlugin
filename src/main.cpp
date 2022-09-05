#include <iostream>
#include <string>
#include <regex>
#include <windows.h>
#include <tchar.h>

#pragma comment(lib, "user32.lib")

#include "traffic_monitor.h"
#include "aida64_plugin.h"

std::string shared_memory_name = std::string("AIDA64_SensorValues");

void replace_all(std::string &source, std::string const &to_replace, std::string const &replace_with);

int main() {
    HANDLE hAidaFile;
    LPCTSTR pBuffer;
    std::regex eId("<id>[a-zA-Z0-9-]*</id>");

    hAidaFile = OpenFileMapping(FILE_MAP_READ, FALSE, shared_memory_name.c_str());

    if (hAidaFile == nullptr) {
        _tprintf("Open Shared Memory failed");
        return 1;
    }

    pBuffer = (LPCTSTR) MapViewOfFile(hAidaFile, FILE_MAP_READ, 0, 0, 0);

    if (pBuffer == nullptr) {
        _tprintf("Read Shared Memory Failed");
        CloseHandle(hAidaFile);
        return 1;
    }

    std::string sResult = std::string(pBuffer);
    _tprintf("%s\n\n", sResult.c_str());
    replace_all(sResult, "</value>", "");
    replace_all(sResult, "<value>", "");
    replace_all(sResult, "<label>", "");
    replace_all(sResult, "</label>", ":");

    replace_all(sResult, "<temp>", "");
    replace_all(sResult, "</temp>", " Celsius\n");

    replace_all(sResult, "<fan>", "");
    replace_all(sResult, "</fan>", " RPM\n");

    replace_all(sResult, "<volt>", "");
    replace_all(sResult, "</volt>", " V\n");

    replace_all(sResult, "<pwr>", "");
    replace_all(sResult, "</pwr>", "\n");

    _tprintf("%s", std::regex_replace(sResult, eId, "").c_str());

    CloseHandle(hAidaFile);

    return 0;
}

void replace_all(std::string &source, std::string const &to_replace, std::string const &replace_with) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(source.size());

    while (true) {
        prevPos = pos;
        pos = source.find(to_replace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(source, prevPos, pos - prevPos);
        buf += replace_with;
        pos += to_replace.size();
    }

    buf.append(source, prevPos, source.size() - prevPos);
    source.swap(buf);
}
