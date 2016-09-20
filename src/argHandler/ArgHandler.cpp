#include "argHandler.h"

Args * ArgHandler::parseArgs(int argc,const char *argv[]){
	Args * args= new Args();
	if(argc<2) {
		std::cout<<std::endl<<"No se envio ningun parametro, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	std::string command = std::string(argv[1]);
	if(!command.compare("crear")) {
        if(argc!=7 && argc!=6){
            std::cout<<"Cantidad de parametros para crear archivo incorrecta, consulte el manual de la app"<<std::endl;
            throw std::exception();
        }
		args->setMethod(Methods::create);
		std::cout<<"Metodo: crear archivo"<<std::endl;
		args->setOutFile(argv[2]);
		std::cout<<"Nombre archivo: "<<args->getOutFile()<<std::endl;
		if(!strcmp(argv[3],"b")) {
			args->setOutType(FileType::bloque);
			std::cout<<"Tipo archivo: bloque"<<std::endl;
			args->setBlockSize(argv[4]);
			std::cout<<"Tamaño del bloque: "<<args->getBlockSize()<<std::endl;
			args->setModifiers(argv[5]);
			std::cout<<"Nombre de los registros: "<<args->getModifiers()<<std::endl;
			args->setModifiers2(argv[6]);
			std::cout<<"Tipo y tamaño de los registros: "<<args->getModifiers2()<<std::endl;
		}
		else if (!strcmp(argv[3],"r")) {
			args->setOutType(FileType::registro);
			std::cout<<"Tipo archivo: registro"<<std::endl;
			args->setModifiers(argv[4]);
			std::cout<<"Nombre de los registros: "<<args->getModifiers()<<std::endl;
			args->setModifiers2(argv[5]);
			std::cout<<"Tipo y tamaño de los registros: "<<args->getModifiers2()<<std::endl;
		}
		else {
			std::cout << "Error al detectar el tipo de archivo"<<std::endl;
			throw std::exception();
		}
		return args;
	}
//	for(int i=0 ; i < argc ; i++){
//		switch(argv[i][1]){
//			case 'i':
//				i++;
//				args->setInFile(argv[i]);
//				break;
//			case 'o':
//				i++;
//				args->setOutFile(argv[i]);
//				break;
//			case 'f':
//				i++;
//				if(std::strcmp(argv[i],"bloque")==0)
//					args->setInType(FileType::bloque);
//				else if(std::strcmp(argv[i],"registro")==0)
//					args->setInType(FileType::registro);
//				else
//					std::cout<<"Tipo de archivo incorrecto \n";
//				break;
//			case 'p':
//				i++;
//				if(std::strcmp(argv[i],"bloque")==0)
//					args->setOutType(FileType::bloque);
//				else if(std::strcmp(argv[i],"registro")==0)
//					args->setOutType(FileType::registro);
//				else
//					std::cout<<"Tipo de archivo incorrecto \n";
//				break;
//
//			//metodos sobre archivos
//			case 's':
//				args->setMethod(Methods::select);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'y':
//				args->setMethod(Methods::proy);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'c':
//				args->setMethod(Methods::prodCart);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'u':
//				args->setMethod(Methods::uni);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'd':
//				args->setMethod(Methods::dif);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 't':
//				args->setMethod(Methods::intersec);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'n':
//				args->setMethod(Methods::join);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'v':
//				args->setMethod(Methods::div);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			case 'g':
//				args->setMethod(Methods::grup);
//				i++;
//				args->setModifiers(argv[i]);
//				break;
//			default:
//				std::cout<<"Modo incorrecto de ejecucion, forma correcta:\n"<<
//				"appname -<metodo> <modficador> -i <archivoEntrada> -o <archivoSalida> -f <tipoArchivoEntrada> -p <tipoArchivoSalida>\n"<<
//				"Consulte appname help para mas informacion\n";
//				throw std::exception();
//		}
//		return args;
//	}

}