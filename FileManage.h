#ifndef FILEMANAGE_H
#define FILEMANAGE_H

#pragma once
#include <iostream>

template<class  T>
class FileManage
{
private:
    T* _Object;
public:
    void ReadFile(const char* fileName);
    void WriteFile(const char* fileName);
    int getCantidad(const char* fileName);
    T* getVector(const char* fileName);
    int getIndex(const char* cod, const char* fileName);
	T getObjectByID(const char* cod, const char* fileName);
    FileManage();
    ~FileManage();

};

template<class  T>
void FileManage<T>::ReadFile(const char* fileName) {

    FILE* pFile = fopen(fileName, "rb");

    if (pFile == NULL) {
        return;
    }

	T Object;

    while (fread(&Object, sizeof(T), 1, pFile)) {
        Object.mostrar();
    }

    fclose(pFile);
}

template<class  T>
void FileManage<T>::WriteFile(const char* fileName) {

    FILE* pFile = fopen(fileName, "ab");

    if (pFile == NULL) {
        return;
    }

	T Object;

    fwrite(Object, sizeof(T), 1, pFile);

    fclose(pFile);
}

template<class  T>
FileManage<T>::FileManage()
{
    this->_Object = new T();
}

template<class  T>
FileManage<T>::~FileManage()
{
	delete this->_Object;
}

template<class  T>
int FileManage<T>::getCantidad(const char* fileName) 
{
    int cantidad = 0;
    FILE* pFile = fopen(fileName, "rb");
    fseek(pFile, 0, SEEK_END);
    cantidad = ftell(pFile) / sizeof(T);
	fclose(pFile);
    return cantidad;
}

template<class T>
T* FileManage<T>::getVector(const char* fileName)
{
    int cantRregistros = this->getCantidad(fileName);
	
    T* object = new T[cantRregistros];
	
    FILE* pFile = fopen(fileName, "rb");

    if (pFile == NULL) {
        return object;
    }

    for (int i = 0; i < cantRregistros; i++)
    {
		fread(&object[i], sizeof(T), 1, pFile);
    }
	
	fclose(pFile);

	return object;
}

template<class T>
int FileManage<T>::getIndex(const char* cod, const char* fileName)
{
    FILE* pFile = fopen(fileName, "rb");
	
	if (pFile == NULL) {
		return -1;
	}

	T object;
	int i = 0;
	while (fread(&object, sizeof(T), 1, pFile)) {
		if (strcmp(object.getCodigo(), cod) == 0) {
			fclose(pFile);
			return i;
		}
		i++;
	}
	fclose(pFile);
	return -1;
}

template<class T>
T FileManage<T>::getObjectByID(const char* cod, const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb");

	T object;
	
	if (pFile == NULL) {
		return object;
	}

	int index = this->getIndex(cod, fileName);
	
	if (index == -1) {
		return object;
	}
	
	fseek(pFile, index * sizeof(T), SEEK_SET);
	
	fread(&object, sizeof(T), 1, pFile);

	fclose(pFile);
	
	return object;
}

#endif