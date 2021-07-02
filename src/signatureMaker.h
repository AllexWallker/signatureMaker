#pragma once
#include <fstream>
#include <unordered_map>
#include <future>
#include <vector>
#include <thread>
#include <memory>


class fileChunk {
public:
    fileChunk(std::string str);
    std::string getData();
private:
    std::string data;
};

//1048576
class signatureMaker {
public:
    signatureMaker(std::string& aFilePath, size_t aChunkSize = 1000000);
    ~signatureMaker();
    void makeFileSignature(std::string& resultMessage);
private:
    void writeSignature(std::string& resultMessage);
    std::string initBuffer(size_t bufferSize);
    
    std::unordered_map<int, std::string> fileSignature;
    std::vector<std::unique_ptr<std::thread>> threads;
    size_t chunkSize;
    std::string filePath;
    std::string directoryPath;
    std::string fileName;
    size_t fileSize;
};

