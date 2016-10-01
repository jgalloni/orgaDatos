//
// Created by Jorge Galloni on 9/30/16.
//


#include <iostream>
#include <fstream>
#include "CSVCommand.h"

CSVCommand::CSVCommand(Args args) {
    this->fileManager = FileManager::getFileManager(args.getInFile());
    this->outfile= new std::ofstream(args.getOutFile());
}

void CSVCommand::execute() const {
    this->fileManager->openFile();
    std::string out=this->fileManager->getHeader()->toCSV();
    *(this->outfile)<<out<<std::endl;
    std::cout<<out<<std::endl;
    while(!this->fileManager->end()){
        std::vector<Register> regs= this->fileManager->getNext();
        for (int i = 0; i < regs.size(); ++i) {
            out=regs[i].toCSV();
            *(this->outfile)<<out<<std::endl;
            std::cout<<out<<std::endl;
        }
    }
    this->fileManager->closeFile();
    this->outfile->close();
}
