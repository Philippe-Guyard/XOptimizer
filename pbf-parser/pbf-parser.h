//
// Created by Nykyta Ostapliuk on 04.11.2021 AD.
//

#ifndef XOPTIMIZER_PBF_PARSER_H
#define XOPTIMIZER_PBF_PARSER_H

#define XOPTIMIZER_PBF_PARSER_DEBUG
#ifdef XOPTIMIZER_PBF_PARSER_DEBUG
#define XOPTIMIZER_PBF_PARSER_ASSERT(x) if (!(x)) throw std::runtime_error(#x "is not true");
#else
#define XOPTIMIZER_PBF_PARSER_ASSERT(x)
#endif

#include <memory>
#include <string>
#include <exception>
#include <cstdint>
#include <optional>
#include <vector>
#include "generated/fileformat.pb.h"
#include "generated/osmformat.pb.h"

namespace XOptimizer::PBFParser {
    class PBFParser {
        std::shared_ptr<std::istream> inputStream;
    public:
        explicit PBFParser(std::shared_ptr<std::istream> inputStream);
        [[nodiscard]] std::shared_ptr<std::istream> getInputStream() const;
    };
}

#endif //XOPTIMIZER_PBF_PARSER_H
