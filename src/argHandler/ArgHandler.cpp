#include "argHandler.h"

Args ArgHandler::parseArgs(int argc, char const *argv[]){
	Args args= new Args();
	for(size_t i=0 ; i < argc ; i++){
		switch(argv[i][1]){

			case 'i':
				i++;
				args.setInFile(argv[i]);
				break;
			case 'o':
				i++;
				args.setOutFile(argv[i]);
				break;
			case 'f':
				i++;
				args.setInTipe(argv[i]);
				break;
			case 'p':
				i++;
				args.setOutTipe(argv[i]);
				break;

			//metodos sobre archivos
			case 's':
				args.setMethod(Methods.select);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'y':
				args.setMethod(Methods.proy);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'c':
				args.setMethod(Methods.prodCart);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'u':
				args.setMethod(Methods.unions);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'd':
				args.setMethod(Methods.dif);
				i++;
				args.setModifier(argv[i]);
				break;
			case 't':
				args.setMethod(Methods.intersec);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'n':
				args.setMethod(Methods.join);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'v':
				args.setMethod(Methods.div);
				i++;
				args.setModifier(argv[i]);
				break;
			case 'g':
				args.setMethod(Methods.grup]);
				i++;
				args.setModifier(argv[i]);
				break;
			default:
				std::cout<<"Modo incorrecto de ejecucion, forma correcta:
				appname -<metodo> <modficador> -i <archivoEntrada> -o <archivoSalida> -f <tipoArchivoEntrada> -p <tipoArchivoSalida>
				Consulte appname help para mas informacion";
				throw std::exception();
		}
		return args;
	}

}