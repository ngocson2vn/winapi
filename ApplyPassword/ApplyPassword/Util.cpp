#include "stdafx.h"

namespace ALPW {

	int offset[] = {0x0035A444, 0x0035A53C, 0x0035A5D6, 0x0035A646};
	//int offset[] = {0x0035A444, 0x0035A53C, 0x0035A5D6, 0x0035A646, 0x0035AD09, 0x0035B3D5, 0x0035DF61, 0x0035E4B1};

	int getLen(const char* str) {
		int len = 0;
		while (1) {
			if (*str != '\0') {
				len++;
				str++;
			} else {
				return len;
			}
		}
	}

	char* getGidHome(const char* fileName) {
		int len = getLen(fileName) - 7 + 1;
		char* home = new char[len];
		for (int i = 0; i < len - 1; i++) {
			home[i] = fileName[i];
		}
		home[len - 1] = '\0';

		return home;
	}

	int checkFileExists(const char* fileName) {
		FILE* fileHandle = NULL;
		errno_t en = fopen_s(&fileHandle, fileName, "rb");
		if (!en) {
			fclose(fileHandle);
			return 1;
		} else {
			return 0;
		}
	}

	int patchExeFile(const char* fileName, char* hostName, int hostSize) {
		FILE* fileHandleRead = NULL;
		FILE* fileHandleWrite = NULL;
		FILE* fileHandlePatch = NULL;

		int bakLen = getLen(fileName) + 5;
		char* bakFileName = (char*)malloc(bakLen);
		sprintf_s(bakFileName, bakLen, "%s.bak", fileName);

		int patchLen = getLen(fileName) + 7;
		char* patchFileName = (char*)malloc(patchLen);
		sprintf_s(patchFileName, patchLen, "%s.patch", fileName);

		errno_t enr = fopen_s(&fileHandleRead, fileName, "rb");
		errno_t enw = fopen_s(&fileHandleWrite, bakFileName, "wb");

		int fileSize = 0;

		if (!enr && !enw) {
			// get file size
			fseek(fileHandleRead, 0, SEEK_END);
			fileSize = ftell(fileHandleRead);
			fseek(fileHandleRead, 0, SEEK_SET);

			// create buffer
			unsigned char* buf = (unsigned char*)malloc(fileSize);

			// read to EOF
			fread(buf, sizeof(unsigned char), fileSize, fileHandleRead);
			fclose(fileHandleRead);
			
			// backup file
			fwrite(buf, sizeof(char), fileSize, fileHandleWrite);
			fclose(fileHandleWrite);

			//unsigned char b1 = buf[offset[0]];
			//unsigned char b2 = buf[offset[0] + 1];
			//unsigned char b3 = buf[offset[0] + 2];
			//sprintf_s(hexString, hexSize, "0x%02hhX %02hhX %02hhX", b1, b2, b3);
			
			/* ============================================= */
			// patch 1
			buf[offset[0]] = 0xE9;
			buf[offset[0] + 1] = 0xED;
			buf[offset[0] + 2] = 0x00;

			// patch 2
			buf[offset[1]] = 0xE9;
			buf[offset[1] + 1] = 0x8D;
			buf[offset[1] + 2] = 0x00;

			// patch 3
			buf[offset[2]] = 0xEB;

			// patch 4
			buf[offset[3]] = 0xEB;

			//// patch 5
			//buf[offset[4] + 1] = 0x00;

			//// patch 6
			//buf[offset[5] + 1] = 0x00;

			//// patch 7
			//buf[offset[6] + 1] = 0x00;

			//// patch 8
			//buf[offset[7] + 1] = 0x00;
			/* ============================================= */

			if (DeleteFileA(fileName)) {
				errno_t en = fopen_s(&fileHandlePatch, fileName, "wb");
				if (!en) {
					fwrite(buf, sizeof(char), fileSize, fileHandlePatch);
					fclose(fileHandlePatch);
				} else {
					return 0;
				}
			} else {
				return 0;
			}
		} else {
			return 0;
		}

		// write password to <GiD_HOME>\scripts\TemporalVariables

		// get gid home gid.exe
		char *gidHome = getGidHome(fileName);
		char *tempVar = "scripts\\TemporalVariables";
		int passLen = getLen(gidHome) + getLen(tempVar) + 1;
		char *passwordFile = new char[passLen];
		sprintf_s(passwordFile, passLen, "%s%s", gidHome, tempVar);

		// build data string
		char* pass = " jr2mjngu2sm8vcnfy1xv7f92bg   # V8 Registration data: Aug 28 2014; Expiration data: Jan  1 2090.";
		int dataLen = getLen(pass) + hostSize + 2;
		char* data = new char[dataLen];
		sprintf_s(data, dataLen, "%s%s\n", hostName, pass);

		// write data
		errno_t en = fopen_s(&fileHandleWrite, passwordFile, "a+");
		if (!en) {
			fputs(data, fileHandleWrite);
			fclose(fileHandleWrite);
		} else {
			return 0;
		}

		return 1;
	}
}