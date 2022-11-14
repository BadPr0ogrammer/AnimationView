#include <string>
#include "ParseFileName.h"

#ifdef _WINDOWS
#include <Windows.h>
#include <codecvt>

string WCharToUtf8(wstring& wstr)
{
	wstring_convert<codecvt_utf8<wchar_t>> converter;
	string ret = converter.to_bytes(wstr);
	return ret;
}

wstring MByteToWChar(const char* mb)
{
	wchar_t wBuf[300];
	MultiByteToWideChar(CP_ACP, 0, mb, -1, wBuf, 300);
	wstring wstr(wBuf);
	return wstr;
}

string parseDirName(const char* mbFullFname)
{
	wstring wFullFname = MByteToWChar(mbFullFname);
	wstring wDir = wFullFname.erase(wFullFname.rfind('/'));
	string sDir = WCharToUtf8(wDir);
	return sDir;
}
#else

std::string parseDirName(const char* mbFullFname)
{
    std::string wFullFname = mbFullFname;
    std::string wDir = wFullFname.erase(wFullFname.rfind('/'));
    return wDir;
}
#endif
