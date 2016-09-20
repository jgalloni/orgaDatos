#include <iostream>
#include <fstream>
#include <cstring>

bool fileExist(std::string& name){
    std::ifstream f(name.c_str());
    bool ret=f.good();
    f.close();
    return ret;
}

int main(int argc, char const *argv[])
{
    std::string * registros;
    std::string * archivo;

    for(int i=1;i<argc;i++){
        if(!std::strcmp(argv[i],"-f")){
            i++;
            archivo = new std::string(argv[i]);
        }
        else if(!std::strcmp(argv[i],"-r")){
            i++;
            registros = new std::string(argv[i]);
        }
        else{
            std::cout<<"Argumentos erroneos"<<std::endl;
            return -1;
        }
    }
    std::cout<<"Insertando: "<<*registros<<" en "<<*archivo<<std::endl;
    std::ofstream fout;
    if(!fileExist(*archivo)){
        std::cout<<"No existe el archivo: "<<*archivo<<", se creara"<<std::endl;
        fout.open(*archivo,std::ios::binary|std::ios::out);
        if(!fout.is_open()){
            std::cout<<"Error al crear el archivo: "<<*archivo<<std::endl;
            return -1;
        }
        char buffer[512];
        for(int i=0;i<512;i++){
            buffer[i]=0;
        }
        std::cout<<"Se creo el archivo"<<*archivo<<std::endl;
        fout.write(buffer,512*sizeof(char));
        fout.write(buffer,512*sizeof(char));
    }
    else{
        fout.open(*archivo,std::ios::binary|std::ios::out);
        std::cout<<"Se abrio el archivo"<<*archivo<<std::endl;
    }
    fout.close();
    return 0;
}

