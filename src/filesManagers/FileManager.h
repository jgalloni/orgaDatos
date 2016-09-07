//
// Created by coco on 06/09/16.
//

#ifndef ORGADATOS_FILEMANAGER_H
#define ORGADATOS_FILEMANAGER_H


class FileManager {
public:
    void createFile(int blockSize,char * name);
    //CRUD de registros
    void removeRegister();
    void updateRegister();
    void deleteRegister();
    void addRegister();

    void getRegister(int id);//TODO:cambiar por un tipo mas generico
};


#endif //ORGADATOS_FILEMANAGER_H
