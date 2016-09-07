#include "argHandler.h"

Args * ArgHandler::parseArgs(int argc, char *argv[]){
	Args * args= new Args();
	for(int i=0 ; i < argc ; i++){
		switch(argv[i][1]){
			case 'i':
				i++;
				args->setInFile(argv[i]);
				break;
			case 'o':
				i++;
				args->setOutFile(argv[i]);
				break;
			case 'f':
				i++;
				if(std::strcmp(argv[i],"bloque")==0)
					args->setInType(FileType::bloque);
				else if(std::strcmp(argv[i],"registro")==0)
					args->setInType(FileType::registro);
				else
					std::cout<<"Tipo de archivo incorrecto \n";
				break;
			case 'p':
				i++;
				if(std::strcmp(argv[i],"bloque")==0)
					args->setOutType(FileType::bloque);
				else if(std::strcmp(argv[i],"registro")==0)
					args->setOutType(FileType::registro);
				else
					std::cout<<"Tipo de archivo incorrecto \n";
				break;

			//metodos sobre archivos
			case 's':
				args->setMethod(Methods::select);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'y':
				args->setMethod(Methods::proy);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'c':
				args->setMethod(Methods::prodCart);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'u':
				args->setMethod(Methods::uni);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'd':
				args->setMethod(Methods::dif);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 't':
				args->setMethod(Methods::intersec);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'n':
				args->setMethod(Methods::join);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'v':
				args->setMethod(Methods::div);
				i++;
				args->setModifiers(argv[i]);
				break;
			case 'g':
				args->setMethod(Methods::grup);
				i++;
				args->setModifiers(argv[i]);
				break;
			default:
				std::cout<<"Modo incorrecto de ejecucion, forma correcta:\n"<<
				"appname -<metodo> <modficador> -i <archivoEntrada> -o <archivoSalida> -f <tipoArchivoEntrada> -p <tipoArchivoSalida>\n"<<
				"Consulte appname help para mas informacion\n";
				throw std::exception();
		}
		return args;
	}

}