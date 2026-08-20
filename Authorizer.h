#pragma once
class Authorizer
{


	bool isValid(int id);

	bool strEqual(const char* str1, const char* str2);

	bool strEqualIC(const char* str1, const char* str2);

	int toInt(const char* text);

	int strLength(const char* text);


};

