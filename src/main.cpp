#include <iostream>
#include <vector>
#include <unordered_map>

#include "signatureMaker.h"

int main(int argc, const char * argv[]) {
    //TO DO add argv filepath;
    std::cout << "Please enter filepath:";
    std::string filePath = "";
    std::getline(std::cin, filePath);
    
    //setConfigs
    //size_t chunkSize;
    
    std::string resultMessage = "";
    auto sMaker = new signatureMaker(filePath);
    sMaker->makeFileSignature(resultMessage);
    delete sMaker;
        
    std::cout << resultMessage;
    
    return 0;
}
