#pragma once
#include <string>

#include "serializeable.h"

class User : public Serializeable {
public:

	std::string username;
	std::string password;
	std::string emailAddress;
	char permissions;

	char* serialize(size_t& size) override {
		size = 0;

		size += sizeof(size_t);
		size += username.size();		
		
		size += sizeof(size_t);
		size += password.size();

		size += sizeof(size_t);
		size += emailAddress.size();

		size += sizeof(char);

		// what if size is 0?

		char* data = new char[size];
		char* p = data;

		writeString(p, username);
		writeString(p, password);
		writeString(p, emailAddress);
		writePrimitive(p, permissions);

		return data;
	}

	void deserialize(char* data) override {
		username = readString(data);
		password = readString(data);
		emailAddress = readString(data);
		permissions = readPrimitive<char>(data);
	}
};