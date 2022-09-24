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
    void ReadFile(T Object, const char* fileName);
    void WriteFile(T Object, const char* fileName);
    FileManage();
    ~FileManage();

};

template<class  T>
void FileManage<T>::ReadFile(T Object, const char* fileName) {

    FILE* pFile = fopen(fileName, "rb");

    if (pFile == NULL) {
        return;
    }

    while (fread(&Object, sizeof(T), 1, pFile)) {
        Object.mostrar();
    }

    fclose(pFile);
}

template<class  T>
void FileManage<T>::WriteFile(T Object, const char* fileName) {

    FILE* pFile = fopen(fileName, "ab");

    if (pFile == NULL) {
        return;
    }

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
#endif