#ifndef UTIL_H
#define UTIL_H
namespace ALPW {
	int getLen(const char* str);
	int checkFileExists(const char* fileName);
	int patchExeFile(const char* fileName, char* hexString, int hexSize);
}

using ALPW::checkFileExists;
using ALPW::patchExeFile;
using ALPW::getLen;
#endif