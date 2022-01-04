//
// Created by Nykyta Ostapliuk on 04.11.2021 AD.
//

#include "pbf-parser.h"

namespace zlib {
#include "zlib.h"
}

#include <istream>
#include <cmath>
#include <unordered_map>

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

long double haversine(long double lat1, long double lon1, long double lat2, long double lon2) {
    long double R = 6371e3;
    long double phi1 = lat1 * M_PI/180;
    long double phi2 = lat2 * M_PI/180;
    long double deltaPhi = (lat2-lat1) * M_PI/180;
    long double deltaLambda = (lon2-lon1) * M_PI/180;

    long double a = sin(deltaPhi/2) * sin(deltaPhi/2) +
                    cos(phi1) * cos(phi2) *
                    sin(deltaLambda/2) * sin(deltaLambda/2);
    long double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return R * c;
}

std::shared_ptr<Map> PBFFile::to_map() const {
    std::vector<long long> indices;
    std::unordered_map<long long, int> indicesMap;
    std::vector<VertexData> data;
    for (const auto& block : blocks) {
        for (auto group : block->get_primitive_groups()) {
            if (auto nodesGroup = std::dynamic_pointer_cast<NodesPrimitiveGroup>(group)) {
                for (const auto& node : nodesGroup->get_nodes()) {
                    indicesMap[node->get_id()] = indices.size();
                    indices.push_back(node->get_id());
                    data.emplace_back(std::make_pair(node->get_lat(), node->get_lon()));
                }
            }
        }
    }
    std::vector<std::vector<std::pair<int, EdgeWeight>>> adjacencyList;
    adjacencyList.reserve(indices.size());
    for (int i = 0; i < indices.size(); i++) adjacencyList.emplace_back();
    for (const auto& block : blocks) {
        for (auto group : block->get_primitive_groups()) {
            if (auto waysGroup = std::dynamic_pointer_cast<WaysPrimitiveGroup>(group)) {
                for (const auto& way : waysGroup->get_ways()) {
                    for (int i = 0; i < way->get_refs().size() - 1; i++) {
                        const auto& v1 = data[indicesMap[way->get_refs()[i]]];
                        const auto& v2 = data[indicesMap[way->get_refs()[i+1]]];
                        long double dist = haversine(
                                v1.get_geolocation().first, v1.get_geolocation().second,
                                v2.get_geolocation().first, v2.get_geolocation().second
                        );
                        adjacencyList[indicesMap[way->get_refs()[i]]].emplace_back(
                                indicesMap[way->get_refs()[i+1]],
                                dist
                        );
                        adjacencyList[indicesMap[way->get_refs()[i+1]]].emplace_back(
                                indicesMap[way->get_refs()[i]],
                                dist
                        );
                    }
                }
            }
        }
    }
    std::unordered_map<int, int> map;
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        // std::cout << i << "/" << data.size() << "\r" << std::flush; // uncommit for "amusing" output while you are waiting
        int neighbor_count = adjacencyList[i].size();
        if (neighbor_count == 0) {
            continue;
        } else if (neighbor_count == 2) {
            int neighbor1 = adjacencyList[i][0].first, neighbor2 = adjacencyList[i][1].first;
            long double dist1 = adjacencyList[i][0].second, dist2 = adjacencyList[i][1].second;
            auto list = adjacencyList[neighbor1];
            if (std::find_if(list.begin(), list.end(),[&](auto e) { return e.first == neighbor2; }) == list.end()) {
                adjacencyList[neighbor1].emplace_back(
                        neighbor2,
                        dist1 + dist2
                );
                adjacencyList[neighbor2].emplace_back(
                        neighbor1,
                        dist1 + dist2
                );
                continue;
            }
        }
        map[i] = count;
        count++;
    }
    auto vertexData = new VertexData[count];
    std::vector<std::vector<std::pair<int, EdgeWeight>>> newAdjacency;
    for (auto pair : map) {
        int i = pair.first, j = pair.second;
        // std::cout << j << " " << i << "\r" << std::flush;
        vertexData[j] = data[i];
        newAdjacency.emplace_back();
    }
    for (auto pair : map) {
        int i = pair.first, j = pair.second;
        std::vector<std::pair<int, EdgeWeight>> newAdjacencies;
        for (auto edge: adjacencyList[i]) {
            if (edge.first != 0 && map.find(edge.first) != map.end()) {
                // std::cout << edge.first << " " << map.at(edge.first) << "\r" << std::flush;
                newAdjacencies.emplace_back(map.at(edge.first), edge.second);
            }
        }
        newAdjacency[j] = newAdjacencies;
    }

    // std::cout << data.size() << " " << count << std::endl;
    return std::make_shared<Map>(
            count, vertexData,
            std::move(newAdjacency)
    );
}

