//
// Created by Nykyta Ostapliuk on 04.11.2021 AD.
//

#include "pbf-parser.h"
namespace zlib {
#include "zlib.h"
}

#include <istream>
using namespace XOptimizer::PBFParser;
using namespace zlib;

PBFParser::PBFParser(std::shared_ptr<std::istream> inputStream) : inputStream(std::move(inputStream)) {}

std::shared_ptr<std::istream> PBFParser::getInputStream() const {
    return inputStream;
}

std::shared_ptr<PBFFile> PBFParser::parse() {
    /*std::vector<OSMPBF::BlobHeader> headers;
    std::vector<OSMPBF::Blob> blobs;
    char* buffer = (char*)malloc(32 * 1024 * 1024);
    for (int k = 0; inputStream->good(); k++) {
        int size = 0;
        for (int i = 0; i < 4; i++) {
            char byte;
            inputStream->read(&byte, 1);
            size |= byte << 8 * (3 - i);
        }
        if (!*inputStream) break;

        inputStream->read(buffer, size);
        headers.emplace_back();
        headers[k].ParseFromArray(buffer, size);

        size = headers[k].datasize();
        inputStream->read(buffer, size);
        blobs.emplace_back();
        blobs[k].ParseFromArray(buffer, size);
    }
    std::vector<void*> rawBlobs;
    for (const auto& blob: blobs) {
        if (blob.has_raw()) {
            rawBlobs.push_back((void*)blob.raw().c_str());
        } else if (blob.has_zlib_data()) {
            XOPTIMIZER_PBF_PARSER_ASSERT(blob.has_raw_size())
            z_stream z;
            z.next_in = (unsigned char*) blob.zlib_data().c_str();
            z.avail_in = blob.zlib_data().size();
            z.next_out = (unsigned char*) buffer;
            z.avail_out = blob.raw_size();

            z.zalloc = Z_NULL;
            z.zfree = Z_NULL;
            z.opaque = Z_NULL;

            XOPTIMIZER_PBF_PARSER_ASSERT(inflateInit(&z) == Z_OK)
            XOPTIMIZER_PBF_PARSER_ASSERT(inflate(&z, Z_FINISH) == Z_STREAM_END)
            XOPTIMIZER_PBF_PARSER_ASSERT(inflateEnd(&z) == Z_OK)
            void* copy = std::malloc(blob.raw_size());
            std::memcpy(copy, buffer, blob.raw_size());
            rawBlobs.push_back(copy);
        }
    }*/
    return {};
}

