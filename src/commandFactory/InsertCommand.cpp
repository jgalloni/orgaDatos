//
// Created by Jorge Galloni on 9/21/16.
//

#include "InsertCommand.h"

InsertCommand::InsertCommand(Args args) {
    this->rawRegister = args.getModifiers();
    this->fileManager = FileManager::getFileManager(args.getOutFile());
}

void InsertCommand::execute() const {
    this->fileManager->openFile();
    this->fileManager->insert(this->rawRegister);
    this->fileManager->closeFile();
}
