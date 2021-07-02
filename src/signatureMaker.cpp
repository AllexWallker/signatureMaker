#include <iostream>
#include <filesystem>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <functional>

#include "signatureMaker.h"

namespace fs = std::filesystem;

static std::mutex m;

using boost::uuids::detail::md5;

static void makeChunkHash(std::unordered_map<int, std::string>& signature, fileChunk* chunk, int index) {
    std::string result = "";
    md5 hash;
    md5::digest_type digest;
    hash.process_bytes(chunk->getData().data(), chunk->getData().size());
    hash.get_digest(digest);
    
    const auto charDigest = reinterpret_cast<const char *>(&digest);
    boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(result));
    
    std::lock_guard<std::mutex> lock(m);
    signature.insert({index, result});
    std::cout << "index " << index << std::endl;
    delete chunk;
}

fileChunk::fileChunk(std::string str): data(str) {}

std::string fileChunk::getData() {
    return data;
}

signatureMaker::signatureMaker(std::string& aFilePath, size_t aChunkSize): filePath(aFilePath), chunkSize(aChunkSize) {
    auto path = fs::path(aFilePath.c_str());
    directoryPath = path.parent_path();
    fileName = path.filename();
    fileSize = fs::file_size(path);
}

signatureMaker::~signatureMaker() {
    fileSignature.clear();
    threads.clear();
}

void signatureMaker::makeFileSignature(std::string& resultMessage) {
    std::ifstream fin;
    fin.open(filePath, std::ios::binary | std::ios::out);
    if(fin.is_open()) {
        if(chunkSize > fileSize) {
            chunkSize = fileSize;
        }
        //fix
        std::string buffer = initBuffer(chunkSize);
        int chunkIndex = 0;
        while(fin.read(&buffer[0], chunkSize)) {
            auto chunk = new fileChunk(buffer);
            std::unique_ptr<std::thread> ptr(new std::thread([this, chunk, chunkIndex]() {
                makeChunkHash(fileSignature, chunk, chunkIndex);
            }));
            threads.push_back(std::move(ptr));
            chunkIndex++;
            
            buffer = initBuffer(chunkSize);
        }
    }
    else {
        resultMessage = "unable to open file\n";
        fin.close();
        return;
    }
    fin.close();

    for(auto& thr : threads) {
        if(thr.get()) {
            thr->join();
        }
    }

    writeSignature(resultMessage);
}

void signatureMaker::writeSignature(std::string& resultMessage) {
    if(!fileSignature.empty()) {
        std::ofstream file(directoryPath + "/" + fileName + "_signature.txt");
        
        for(int i = 0; i < fileSignature.size(); i++) {
            file << "chunk " << i << " " << fileSignature.at(i) << std::endl;
        }
        file.close();
        resultMessage = "file was written successfuly, directory:" + directoryPath + "\n";
        
    }
    else {
        resultMessage = "unable to write file\n";
    }
}

std::string signatureMaker::initBuffer(size_t bufferSize) {
    std::string buffer(bufferSize, '\0');
    return buffer;
}
