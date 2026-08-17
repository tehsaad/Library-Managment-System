#pragma once
class Authorizer
{


	bool isValid(int id);

	bool isValidMenuChoice(int Choice, int min, int max);

	bool isValidPassword(const char* password);

	bool isValidContact(const char* contact);

	int toInt(const char* text);

	int strLength(const char* text);


};

