#ifndef HELLOTEXT_H
#define HELLOTEXT_H

// Dependencies:
#include <string>

// Interface:
inline std::wstring const& helloText()
{
	static std::wstring const value = L"O wondrous world!";
	return value;
}
# endif