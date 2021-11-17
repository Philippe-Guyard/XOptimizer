//
// Created by Nykyta Ostapliuk on 04.11.2021 AD.
//

#ifndef XOPTIMIZER_PBF_PARSER_H
#define XOPTIMIZER_PBF_PARSER_H

#define XOPTIMIZER_PBF_PARSER_DEBUG
#ifdef XOPTIMIZER_PBF_PARSER_DEBUG
#define XOPTIMIZER_PBF_PARSER_ASSERT(x) if (!(x)) throw std::runtime_error(#x " is not true");
#else
#define XOPTIMIZER_PBF_PARSER_ASSERT(x)
#endif

#include <memory>
#include <string>
#include <exception>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>
#include "generated/fileformat.pb.h"
#include "generated/osmformat.pb.h"

namespace XOptimizer::PBFParser {
    class BBox {
        long double left, bottom, right, top;
    public:
        BBox(long double left, long double bottom, long double right, long double top)
        : left(left), bottom(bottom), right(right), top(top) {}

        [[nodiscard]] long double get_left() const {
            return left;
        }

        [[nodiscard]] long double get_bottom() const {
            return bottom;
        }

        [[nodiscard]] long double get_right() const {
            return right;
        }

        [[nodiscard]] long double get_top() const {
            return top;
        }
    };
    class PrimitiveGroup {};
    class Node {
        long long id;
        std::vector<std::pair<std::string, std::string>> key_vals;
        long double lat, lon;
    public:
        Node(long long int id, std::vector<std::pair<std::string, std::string>> keyVals, long double lat,
             long double lon) : id(id), key_vals(std::move(keyVals)), lat(lat), lon(lon) {}

        [[nodiscard]] long long int get_id() const {
            return id;
        }

        [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &get_key_vals() const {
            return key_vals;
        }

        [[nodiscard]] long double get_lat() const {
            return lat;
        }

        [[nodiscard]] long double get_lon() const {
            return lon;
        }
    };
    class NodesPrimitiveGroup: public PrimitiveGroup {
        std::vector<std::shared_ptr<Node>> nodes;
    public:
        explicit NodesPrimitiveGroup(std::vector<std::shared_ptr<Node>> nodes) : nodes(std::move(nodes)) {}

        [[nodiscard]] const std::vector<std::shared_ptr<Node>> &get_nodes() const {
            return nodes;
        }
    };
    class Way {
        long long id;
        std::vector<std::pair<std::string, std::string>> key_vals;
        std::vector<long long> refs;
    public:
        Way(long long int id, std::vector<std::pair<std::string, std::string>> keyVals,
            std::vector<long long int> refs) : id(id), key_vals(std::move(keyVals)), refs(std::move(refs)) {}

        [[nodiscard]] long long int get_id() const {
            return id;
        }

        [[nodiscard]] const std::vector<std::pair<std::string, std::string>> &get_key_vals() const {
            return key_vals;
        }

        [[nodiscard]] const std::vector<long long int> &get_refs() const {
            return refs;
        }
    };
    class WaysPrimitiveGroup: public PrimitiveGroup {
        std::vector<std::shared_ptr<Way>> ways;
    public:
        explicit WaysPrimitiveGroup(std::vector<std::shared_ptr<Way>> ways) : ways(std::move(ways)) {}

        [[nodiscard]] const std::vector<std::shared_ptr<Way>> &get_ways() const {
            return ways;
        }
    };
    class PrimitiveBlock {
        std::vector<std::string> string_table;
        int granularity;
        long double lat_offset, lon_offset;
        int date_granularity;
    public:
        PrimitiveBlock(std::vector<std::string> stringTable, int granularity, long double latOffset,
                       long double lonOffset, int dateGranularity)
                       : string_table(std::move(stringTable)),
                         granularity(granularity), lat_offset(latOffset),
                         lon_offset(lonOffset),
                         date_granularity(dateGranularity) {}

        [[nodiscard]] const std::vector<std::string> &get_string_table() const {
            return string_table;
        }

        [[nodiscard]] int get_granularity() const {
            return granularity;
        }

        [[nodiscard]] long double get_lat_offset() const {
            return lat_offset;
        }

        [[nodiscard]] long double get_lon_offset() const {
            return lon_offset;
        }

        [[nodiscard]] int get_date_granularity() const {
            return date_granularity;
        }
    };
    class PBFFile {
        std::shared_ptr<BBox> bbox;
        std::vector<std::string> required_features, optional_features;
        std::optional<std::string> writing_program, source;
        std::vector<std::shared_ptr<PrimitiveBlock>> blocks;
        PBFFile() = default;
    public:
        PBFFile(std::shared_ptr<BBox> bbox, std::vector<std::string> requiredFeatures,
                std::vector<std::string> optionalFeatures, std::optional<std::string> writingProgram,
                std::optional<std::string> source, std::vector<std::shared_ptr<PrimitiveBlock>> blocks)
                : bbox(std::move(bbox)),
                required_features(std::move(requiredFeatures)),
                optional_features(std::move(optionalFeatures)),
                writing_program(std::move(writingProgram)),
                source(std::move(source)),
                blocks(std::move(blocks)) {}

        [[nodiscard]] const std::shared_ptr<BBox> &get_bbox() const {
            return bbox;
        }

        [[nodiscard]] const std::vector<std::string> &get_required_features() const {
            return required_features;
        }

        [[nodiscard]] const std::vector<std::string> &get_optional_features() const {
            return optional_features;
        }

        [[nodiscard]] const std::optional<std::string> &get_writing_program() const {
            return writing_program;
        }

        [[nodiscard]] const std::optional<std::string> &get_source() const {
            return source;
        }

        [[nodiscard]] const std::vector<std::shared_ptr<PrimitiveBlock>> &get_blocks() const {
            return blocks;
        }
    };

    class PBFParser {
        std::shared_ptr<std::istream> inputStream;
    public:
        explicit PBFParser(std::shared_ptr<std::istream> inputStream);
        [[nodiscard]] std::shared_ptr<std::istream> getInputStream() const;
        std::shared_ptr<PBFFile> parse();
    };
}

#endif //XOPTIMIZER_PBF_PARSER_H
