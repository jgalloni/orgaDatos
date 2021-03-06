#include "argHandler.h"

Args * ArgHandler::parseArgs(int argc,const char *argv[]){

	if(argc<2) {
		std::cout<<std::endl<<"No se envio ningun parametro, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	std::string command = std::string(argv[1]);
	if(!command.compare("crear")) {
		return ArgHandler::createArgFiller(argc,argv);
	}else if(!command.compare("insertar")){
		return ArgHandler::insertArgFiller(argc,argv);
	} else if(!command.compare("borrar")){
		return ArgHandler::deleteArgFiller(argc,argv);
	} else if(!command.compare("seleccionar")){
        return ArgHandler::selectArgFiller(argc,argv);
    } else if(!command.compare("unir")){
        return ArgHandler::unionArgFiller(argc,argv);
    }else if(!command.compare("producto")){
        return ArgHandler::multiplyArgFiller(argc,argv);
    }else if(!command.compare("proyectar")){
        return ArgHandler::proyectArgFiller(argc,argv);
    }else if(!command.compare("csv")){
		return ArgHandler::csvArgFiller(argc,argv);
	}

}

Args * ArgHandler::createArgFiller(int argc,const char *argv[]){
	Args * args= new Args();
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

Args * ArgHandler::insertArgFiller(int argc,const char *argv[]){
	Args * args= new Args();
	if(argc!=4){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::insert);
	std::cout<<"Metodo: insertar registro"<<std::endl;
	args->setOutFile(argv[2]);
	std::cout<<"Nombre archivo: "<<args->getOutFile()<<std::endl;
	args->setModifiers(argv[3]);
	std::cout<<"Registro a insertar de los registros: "<<args->getModifiers()<<std::endl;
	return args;
}

Args *ArgHandler::deleteArgFiller(int argc, const char **argv) {
	Args * args= new Args();
	if(argc!=4){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::deleteReg);
	std::cout<<"Metodo: borrar registro"<<std::endl;
	args->setOutFile(argv[2]);
	std::cout<<"Nombre archivo: "<<args->getOutFile()<<std::endl;
	args->setModifiers(argv[3]);
	std::cout<<"Registro a borrar"<<args->getModifiers()<<std::endl;
	return args;
}

Args *ArgHandler::selectArgFiller(int argc, const char **argv) {
    Args * args= new Args();
    if(argc!=7){
        std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
        throw std::exception();
    }
    args->setMethod(Methods::select);
    std::cout<<"Metodo: Seleccionar"<<std::endl;
    args->setInFile(argv[2]);
    std::cout<<"Nombre archivo de entrada: "<<args->getInFile()<<std::endl;
    args->setOutFile(argv[3]);
    std::cout<<"Nombre archivo de salida: "<<args->getOutFile()<<std::endl;
    args->setModifiers(argv[4]);
	std::cout<<"campo: "<<args->getModifiers()<<std::endl;
	args->setModifiers2(argv[5]);
    std::cout<<"condicion: "<<args->getModifiers2()<<std::endl;
	args->setModifiers3(argv[6]);
    std::cout<<"valor: "<<args->getModifiers3()<<std::endl;
    return args;
}

Args *ArgHandler::proyectArgFiller(int argc, const char **argv) {
	Args * args= new Args();
	if(argc!=5){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::proy);
	std::cout<<"Metodo: Proyectar"<<std::endl;
	args->setInFile(argv[2]);
	std::cout<<"Nombre archivo de entrada: "<<args->getInFile()<<std::endl;
	args->setOutFile(argv[3]);
	std::cout<<"Nombre archivo de salida: "<<args->getOutFile()<<std::endl;
	args->setModifiers(argv[4]);
	std::cout<<"campos: "<<args->getModifiers()<<std::endl;
	return args;
}

Args *ArgHandler::unionArgFiller(int argc, const char **argv) {
	Args * args= new Args();
	if(argc!=5){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::uni);
	std::cout<<"Metodo: Proyectar"<<std::endl;
	args->setInFile(argv[2]);
	std::cout<<"Nombre archivo de entrada1: "<<args->getInFile()<<std::endl;
	args->setModifiers(argv[3]);
	std::cout<<"Nombre archivo de entrada2: "<<args->getModifiers()<<std::endl;
	args->setOutFile(argv[4]);
	std::cout<<"Nombre archivo de salida: "<<args->getOutFile()<<std::endl;
	return args;
}

Args *ArgHandler::multiplyArgFiller(int argc, const char **argv) {
    Args * args= new Args();
    if(argc!=5){
        std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
        throw std::exception();
    }
    args->setMethod(Methods::prodCart);
    std::cout<<"Metodo: Producto cartesiano"<<std::endl;
    args->setInFile(argv[2]);
    std::cout<<"Nombre archivo de entrada1: "<<args->getInFile()<<std::endl;
    args->setModifiers(argv[3]);
    std::cout<<"Nombre archivo de entrada2: "<<args->getModifiers()<<std::endl;
    args->setOutFile(argv[4]);
    std::cout<<"Nombre archivo de salida: "<<args->getOutFile()<<std::endl;
    return args;
}

Args *ArgHandler::csvArgFiller(int argc, const char **argv) {
	Args * args= new Args();
	if(argc!=4){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::csv);
	std::cout<<"Metodo: Producto cartesiano"<<std::endl;
	args->setInFile(argv[2]);
	std::cout<<"Nombre archivo de entrada: "<<args->getInFile()<<std::endl;
	args->setOutFile(argv[3]);
	std::cout<<"Nombre archivo de salida: "<<args->getOutFile()<<std::endl;
	return args;
}
