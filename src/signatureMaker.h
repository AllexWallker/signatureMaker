#pragma once
#include <fstream>
#include <unordered_map>
#include <vector>
#include <thread>
#include <memory>
#include <filesystem>

#ifdef __clang__
namespace fs = std::__fs::filesystem;
#else
namespace fs = std::filesystem;
#endif

class fileChunk {
public:
    fileChunk(std::string str);
    std::string getData();
private:
    std::string data;
};

class signatureMaker {
public:
    signatureMaker(std::string& aFilePath, size_t aChunkSize = 1000000);
    ~signatureMaker();
    void makeFileSignature(std::string& resultMessage);
private:
    void writeSignature(std::string& resultMessage);
    std::string initBuffer(size_t bufferSize);
    void initChunkSize();
    
    std::unordered_map<int, std::string> fileSignature;
    std::vector<std::unique_ptr<std::thread>> threads;
    size_t chunkSize;
    std::string filePath;
    std::string directoryPath;
    std::string fileName;
    size_t fileSize;
    size_t leftToRead;
};

