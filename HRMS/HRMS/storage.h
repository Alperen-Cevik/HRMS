#pragma once
#include <fstream>
#include <string>

#include "serializeable.h"
#include "nodelist.h"

template <typename T>
class DiskStorage
{
public:
	DiskStorage(const std::string& fileName) : fileName(fileName) {
		loadFromDatabase();
	}

	~DiskStorage() {
		saveToDatabase();
	}

	void saveToDatabase() {
		std::ofstream file(fileName, std::ios::binary);
		if (file.is_open()) {
			size_t elemCount = nodeList.size();
			file.write((char*)&elemCount, sizeof(size_t));
			
			for (size_t i = 0; i < elemCount; i++) {
				size_t size;
				char* data = nodeList[i].serialize(size);

				file.write((char*)&size, sizeof(size_t));
				file.write(data, size);
			}
		}
		else {
			printf("Failed to open the file to write.");
		}
	}
	
	void loadFromDatabase() {
		std::ifstream file(fileName, std::ios::binary);
		if (file.is_open()) {
			size_t elemCount;
			file.read((char*) &elemCount, sizeof(size_t));

			for (size_t i = 0; i < elemCount; i++) {
				size_t size;
				file.read((char*)&size, sizeof(size_t));
				
				char* data = new char[size];
				file.read(data, size);
				
				nodeList.push(T());
				nodeList[i].deserialize(data);

				delete[] data;
			}
		}
	}

	NodeList<T> nodeList;

private:
	std::string fileName;
};

