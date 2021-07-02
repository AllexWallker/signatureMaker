#include <iostream>

#include "signatureMaker.h"

int main(int argc, const char * argv[]) {
    std::string resultMessage = "";
    
    std::cout << "Please enter filepath:";
    std::string filePath = "";
    std::getline(std::cin, filePath);

    try {
        std::unique_ptr<signatureMaker> sMaker(new signatureMaker(filePath));
        sMaker->makeFileSignature(resultMessage);
    }
    catch(fs::filesystem_error) {
        resultMessage = "The file isn't exist\n";
    }
    catch(std::ifstream::failure){
        resultMessage = "Exception opening/reading/closing file\n";
    }
    catch(std::out_of_range) {
        resultMessage = "Something went wrong with reading the result map\n";
    }
    std::cout << resultMessage;
    
    return 0;
}
