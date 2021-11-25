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
    char* buffer = new char[32 * 1024 * 1024];
    std::shared_ptr<BBox> bbox;
    std::vector<std::string> required_features, optional_features;
    std::optional<std::string> writing_program, source;
    std::vector<std::shared_ptr<PrimitiveBlock>> blocks;
    for (int k = 0; inputStream->good(); k++) {
        int headerSize = 0;
        for (int i = 0; i < 4; i++) {
            char byte;
            inputStream->read(&byte, 1);
            headerSize |= byte << 8 * (3 - i);
        }
        if (!*inputStream) break;

        inputStream->read(buffer, headerSize);
        OSMPBF::BlobHeader blobHeader;
        blobHeader.ParseFromArray(buffer, headerSize);

        int blobSize = blobHeader.datasize();
        inputStream->read(buffer, blobSize);
        OSMPBF::Blob blob;
        blob.ParseFromArray(buffer, blobSize);
        int bufferSize = blob.raw_size();

        if (blob.has_raw()) {
            memcpy(buffer, blob.raw().c_str(), bufferSize);
        } else if (blob.has_zlib_data()) {
            XOPTIMIZER_PBF_PARSER_ASSERT(blob.has_raw_size())
            z_stream z;
            z.next_in = (unsigned char*) blob.zlib_data().c_str();
            z.avail_in = blob.zlib_data().size();
            z.next_out = (unsigned char*) buffer;
            z.avail_out = bufferSize;

            z.zalloc = Z_NULL;
            z.zfree = Z_NULL;
            z.opaque = Z_NULL;

            XOPTIMIZER_PBF_PARSER_ASSERT(inflateInit(&z) == Z_OK)
            XOPTIMIZER_PBF_PARSER_ASSERT(inflate(&z, Z_FINISH) == Z_STREAM_END)
            XOPTIMIZER_PBF_PARSER_ASSERT(inflateEnd(&z) == Z_OK)
        }

        if (blobHeader.type() == "OSMHeader") {
            OSMPBF::HeaderBlock block;
            block.ParseFromArray(buffer, bufferSize);
            if (block.has_bbox()) {
                const OSMPBF::HeaderBBox& headerBBox = block.bbox();
                bbox = std::make_shared<BBox>(
                        (long double)(headerBBox.left()) / 1000000000,
                        (long double)(headerBBox.bottom()) / 1000000000,
                        (long double)(headerBBox.right()) / 1000000000,
                        (long double)(headerBBox.top()) / 1000000000
                );
            }
            for (int i = 0; i < block.required_features_size(); i++) {
                required_features.emplace_back(block.required_features(i));
            }
            for (int i = 0; i < block.optional_features_size(); i++) {
                required_features.emplace_back(block.optional_features(i));
            }
            if (block.has_writingprogram()) writing_program = block.writingprogram();
            if (block.has_source()) source = block.source();
        } else if (blobHeader.type() == "OSMData") {
            OSMPBF::PrimitiveBlock pbfPrimitiveBlock;
            pbfPrimitiveBlock.ParseFromArray(buffer, bufferSize);
            int granularity = pbfPrimitiveBlock.granularity();
            long double latOffset = (long double)(0.000000001) * pbfPrimitiveBlock.lat_offset();
            long double lonOffset = (long double)(0.000000001) * pbfPrimitiveBlock.lon_offset();
            int dateGranularity = pbfPrimitiveBlock.date_granularity();
            std::vector<std::string> stringTable;
            stringTable.reserve(pbfPrimitiveBlock.stringtable().s_size());
            for (int i = 0; i < pbfPrimitiveBlock.stringtable().s_size(); i++) {
                stringTable.emplace_back(pbfPrimitiveBlock.stringtable().s(i));
            }
            std::vector<std::shared_ptr<PrimitiveGroup>> primitiveGroups;
            for (int i = 0; i < pbfPrimitiveBlock.primitivegroup_size(); i++) {
                const OSMPBF::PrimitiveGroup& pbfPrimitiveGroup = pbfPrimitiveBlock.primitivegroup(i);
                if (pbfPrimitiveGroup.nodes_size() > 0) {
                    std::vector<std::shared_ptr<Node>> nodes;
                    for (int i = 0; i < pbfPrimitiveGroup.nodes_size(); i++) {
                        const OSMPBF::Node& pbfNode = pbfPrimitiveGroup.nodes(i);
                        long long id = pbfNode.id();
                        long double lat = latOffset + (long double)(0.000000001) * granularity * pbfNode.lat();
                        long double lon = lonOffset + (long double)(0.000000001) * granularity * pbfNode.lon();
                        std::vector<std::pair<std::string, std::string>> keyVals;
                        keyVals.reserve(pbfNode.keys_size());
                        for (int i = 0; i < pbfNode.keys_size(); i++) {
                            keyVals.emplace_back(stringTable[pbfNode.keys(i)], stringTable[pbfNode.vals(i)]);
                        }
                        nodes.emplace_back(std::make_shared<Node>(id, keyVals, lat, lon));
                    }
                    primitiveGroups.emplace_back(std::make_shared<NodesPrimitiveGroup>(nodes));
                } else if (pbfPrimitiveGroup.ways_size() > 0) {
                    std::vector<std::shared_ptr<Way>> ways;
                    for (int i = 0; i < pbfPrimitiveGroup.ways_size(); i++) {
                        const OSMPBF::Way& pbfWay = pbfPrimitiveGroup.ways(i);
                        long long id = pbfWay.id();
                        std::vector<std::pair<std::string, std::string>> keyVals;
                        keyVals.reserve(pbfWay.keys_size());
                        for (int i = 0; i < pbfWay.keys_size(); i++) {
                            keyVals.emplace_back(stringTable[pbfWay.keys(i)], stringTable[pbfWay.vals(i)]);
                        }
                        std::vector<long long> refs;
                        refs.reserve(pbfWay.refs_size());
                        long long prev = 0;
                        for (int i = 0; i < pbfWay.refs_size(); prev = pbfWay.refs(i), i++) {
                            refs.push_back(pbfWay.refs(i) + prev);
                        }
                        ways.emplace_back(std::make_shared<Way>(id, keyVals, refs));
                    }
                    primitiveGroups.emplace_back(std::make_shared<WaysPrimitiveGroup>(ways));
                } else if (pbfPrimitiveGroup.has_dense()) {
                    const OSMPBF::DenseNodes& denseNodes = pbfPrimitiveGroup.dense();
                    std::vector<std::shared_ptr<Node>> nodes;
                    long long prevId = 0, prevLat = 0, prevLon = 0;
                    int keyValsPtr = 0;
                    for (int i = 0; i < denseNodes.id_size(); i++) {
                        long long id = prevId = denseNodes.id(i) + prevId;
                        long double lat = latOffset + (long double)(0.000000001) * granularity * (prevLat = (denseNodes.lat(i) + prevLat));
                        long double lon = lonOffset + (long double)(0.000000001) * granularity * (prevLon = (denseNodes.lon(i) + prevLon));
                        std::vector<std::pair<std::string, std::string>> keyVals;
                        while (keyValsPtr < denseNodes.keys_vals_size() && denseNodes.keys_vals(keyValsPtr) != 0) {
                            int key = denseNodes.keys_vals(keyValsPtr);
                            keyValsPtr++;
                            int val = denseNodes.keys_vals(keyValsPtr);
                            keyValsPtr++;
                            keyVals.emplace_back(stringTable[key], stringTable[val]);
                        }
                        if (keyValsPtr < denseNodes.keys_vals_size()) keyValsPtr++;
                        nodes.emplace_back(std::make_shared<Node>(id, keyVals, lat, lon));
                    }
                    primitiveGroups.emplace_back(std::make_shared<NodesPrimitiveGroup>(nodes));
                }
            }
            blocks.emplace_back(std::make_shared<PrimitiveBlock>(stringTable, granularity, latOffset, lonOffset, dateGranularity, primitiveGroups));
        }
    }
    return std::make_shared<PBFFile>(bbox, required_features, optional_features, writing_program, source, blocks);
}

