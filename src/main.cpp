#include <iostream>

#include "signatureMaker.h"

int main(int argc, const char * argv[]) {
    std::string resultMessage = "";
    
    std::cout << "Please enter filepath:";
    std::string filePath = "";
    std::getline(std::cin, filePath);

    if(filePath.empty()) {
        resultMessage = "filepath is empty\n";
        std::cout << resultMessage;
        return 0;
    }
    if(!fs::exists(filePath)) {
        resultMessage = "file doesn't exist\n";
        std::cout << resultMessage;
        return 0;
    }
    
    auto sMaker = new signatureMaker(filePath);
    sMaker->makeFileSignature(resultMessage);
    delete sMaker;
        
    std::cout << resultMessage;
    
    return 0;
}
