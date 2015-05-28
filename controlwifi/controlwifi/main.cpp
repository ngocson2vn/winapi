#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	const TCHAR* logFile = L"C:\\Users\\son\\tmp\\wifi.log";
	HANDLE hLog;
	TCHAR* dataBuffer = NULL;
	DWORD dwBytesToWrite = 0;
	DWORD dwBytesWritten = 0;
	SYSTEMTIME st;
	TCHAR dateAndTime[1024];

	dataBuffer = L"== START RESTART Wi-Fi ==\r\n";
	dwBytesToWrite = (DWORD) lstrlenW(dataBuffer) * sizeof(wchar_t);

	hLog = CreateFile(logFile,  // name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_ALWAYS,          // always create new file
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL);

	WriteFile(
		hLog,            // open file handle
		dataBuffer,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);           // no overlapped structure

	GetLocalTime(&st); // Alternatively use GetSystemTime for the UTC version of the time
	wsprintf(dateAndTime, L"%d/%d/%d %d:%d:%d\r\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
	
	dwBytesToWrite = (DWORD)lstrlenW(dateAndTime) * sizeof(wchar_t);

	WriteFile(
		hLog,            // open file handle
		dateAndTime,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);           // no overlapped structure

	WinExec("netsh interface set interface \"Wi-Fi\" admin=disable", SW_HIDE);
	Sleep(5000);
	WinExec("netsh interface set interface \"Wi-Fi\" admin=enable", SW_HIDE);

	dataBuffer = L"== END RESTART Wi-Fi ==\r\n";
	dwBytesToWrite = (DWORD)lstrlenW(dataBuffer) * sizeof(wchar_t);

	WriteFile(
		hLog,            // open file handle
		dataBuffer,      // start of data to write
		dwBytesToWrite,  // number of bytes to write
		&dwBytesWritten, // number of bytes that were written
		NULL);           // no overlapped structure

	CloseHandle(hLog);

	return 0;
}