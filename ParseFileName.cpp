#include <Windows.h>

#include <string>
#include <codecvt>

using namespace std;

#include "ParseFileName.h"

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
