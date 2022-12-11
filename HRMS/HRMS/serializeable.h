#pragma once

#include <string>

class Serializeable {
public:
	virtual char* serialize(size_t& size) = 0;
	virtual void deserialize(char* data) = 0;

	template <typename T>
	static T readPrimitive(char*& data) {
		T tmp = *((T*)data);
		data += sizeof(T);
		return tmp;
	}

	template <typename T>
	static void writePrimitive(char*& out, const T& data) {
		*static_cast<T*>(out) = data;
		out += sizeof(T);
	}

	static std::string readString(char*& data) {
		size_t size = *((size_t*)data);
		data += sizeof(size_t);
		
		std::string tmp(data, size);
		data += size;

		return tmp;
	}

	static void writeString(char*& out, const std::string& str) {
		*((size_t*)out) = str.size();
		out += sizeof(size_t);
		memcpy(out, str.data(), str.size());
		out += str.size();
	}
};