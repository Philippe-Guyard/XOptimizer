//
// Created by Nykyta Ostapliuk on 04.11.2021 AD.
//

#include "pbf-parser.h"
#include <istream>
using namespace XOptimizer::PBFParser;

PBFParser::PBFParser(std::shared_ptr<std::istream> inputStream) : inputStream(std::move(inputStream)) {}

std::shared_ptr<std::istream> PBFParser::getInputStream() const {
    return inputStream;
}
