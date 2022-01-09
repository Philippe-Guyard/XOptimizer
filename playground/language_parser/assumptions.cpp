//
// Created by Nykyta Ostapliuk on 18.10.2021 AD.
//

#include "assumptions.h"
#include <string>
#include <sstream>
#include <limits>
#include <cmath>
#include <utility>
#include <iostream>
using namespace XOptimizer::Assumptions;

std::shared_ptr<Assumption>
XOptimizer::Assumptions::RegionAssumption::intersect(std::shared_ptr<Assumption> other) const {
    if (isEmpty()) return std::shared_ptr<RegionAssumption>((RegionAssumption*)this);
    if (other->isEmpty()) return other;
    if (auto regionAssumption = std::dynamic_pointer_cast<RegionAssumption>(other)) {
        return opsHelper(regionAssumption, [](double lim1, bool strict1, double lim2, bool strict2, bool, bool max) {
            double lim; bool strict;
            if (lim1 == lim2) {
                lim = lim1;
                strict = strict1 || strict2;
            } else {
                lim = max ? (lim1 > lim2 ? lim2 : lim1) : (lim1 > lim2 ? lim1 : lim2);
                strict = lim == lim1 ? strict1 : strict2;
            }
            return std::make_tuple(lim, strict);
        });
    } else return other->intersect(std::shared_ptr<RegionAssumption>((RegionAssumption*)this));
}

bool RegionAssumption::isEmpty() const {
    if (x_min > x_max) return true;
    if (x_min == x_max) return x_min_strict || x_max_strict;
    if (y_min > y_max) return true;
    if (y_min == y_max) return y_min_strict || y_max_strict;
    return false;
}

bool RegionAssumption::operator==(std::shared_ptr<Assumption> other) const {
    if (isEmpty()) {
        return other->isEmpty();
    }
    if (other->isEmpty()) return false;
    if (auto regionAssumption = std::dynamic_pointer_cast<RegionAssumption>(other)) {
        return (
                x_min == regionAssumption->x_min &&
                x_max == regionAssumption->x_max &&
                y_min == regionAssumption->y_min &&
                y_max == regionAssumption->y_max &&
                x_min_strict == regionAssumption->x_min_strict &&
                x_max_strict == regionAssumption->x_max_strict &&
                y_min_strict == regionAssumption->y_min_strict &&
                y_max_strict == regionAssumption->y_max_strict
        );
    } else return other->operator==(std::shared_ptr<RegionAssumption>((RegionAssumption*)this));
}

std::shared_ptr<Assumption> RegionAssumption::add(std::shared_ptr<Assumption> other) const {
    if (isEmpty()) return std::shared_ptr<RegionAssumption>((RegionAssumption*)this);
    if (other->isEmpty()) return other;
    if (auto regionAssumption = std::dynamic_pointer_cast<RegionAssumption>(other)) {
        return opsHelper(regionAssumption, [](double lim1, bool strict1, double lim2, bool strict2, bool, bool) {
            return std::make_tuple(lim1 + lim2, strict1 || strict2);
        });
    } else return other->add(std::shared_ptr<RegionAssumption>((RegionAssumption*)this));
}

std::shared_ptr<Assumption> RegionAssumption::sub(std::shared_ptr<Assumption> other) const {
    return add(other->neg());
}

double limitMul(double lim1, double lim2) {
    if (!isfinite(lim1) && lim2 == 0) {
        return 0;
    }
    if (!isfinite(lim2) && lim1 == 0) {
        return 0;
    }
    return lim1 * lim2;
}

std::shared_ptr<Assumption> RegionAssumption::mul(std::shared_ptr<Assumption> other) const {
    if (isEmpty()) return std::shared_ptr<RegionAssumption>((RegionAssumption*)this);
    if (other->isEmpty()) return other;
    if (auto regionAssumption = std::dynamic_pointer_cast<RegionAssumption>(other)) {
        if (regionAssumption->isReal() && isReal()) {
            double min1min2 = limitMul(x_min, regionAssumption->x_min);
            double min1max2 = limitMul(x_min, regionAssumption->x_max);
            double max1min2 = limitMul(x_max, regionAssumption->x_min);
            double max1max2 = limitMul(x_max, regionAssumption->x_max);
            double max = std::max({min1min2, min1max2, max1min2, max1max2});
            double min = std::min({min1min2, min1max2, max1min2, max1max2});
            return std::make_shared<RegionAssumption>(
                    min, max, 0, 0,
                    false, false, false, false, integer && regionAssumption->integer
            );
        } else return Assumption::any(); // TODO
    } else return other->mul(std::shared_ptr<RegionAssumption>((RegionAssumption*)this));
}

std::shared_ptr<Assumption> RegionAssumption::div(std::shared_ptr<Assumption> other) const {
    return mul(other->rec());
}

std::string RegionAssumption::toString() const {
    std::stringstream res;
    res << "RegionAssumption{";
    if (x_min != -std::numeric_limits<double>::infinity()) {
        res << x_min << " <";
        if (!x_min_strict) res << "=";
        res << " ";
    }
    res << "real";
    if (x_max != std::numeric_limits<double>::infinity()) {
        res << " <";
        if (!x_max_strict) res << "=";
        res << " " << x_max;
    }
    res << ", ";
    if (y_min != -std::numeric_limits<double>::infinity()) {
        res << y_min << " <";
        if (!y_min_strict) res << "=";
        res << " ";
    }
    res << "img";
    if (y_max != std::numeric_limits<double>::infinity()) {
        res << " <";
        if (!y_max_strict) res << "=";
        res << " " << y_max;
    }
    res << "}";
    return res.str();
}

std::shared_ptr<Assumption> RegionAssumption::neg() const {
    return std::make_shared<RegionAssumption>(
            -x_max, -x_min, -y_max, -y_min,
            x_max_strict, x_min_strict,
            y_max_strict, y_min_strict,
            integer
    );
}

std::shared_ptr<Assumption> RegionAssumption::rec() const {
    if (isEmpty()) return std::shared_ptr<RegionAssumption>((RegionAssumption*)this);
    return Assumption::any(); // TODO: implement properly
}

bool RegionAssumption::isReal() const {
    return y_min == 0 && y_max == 0 && !y_min_strict && !y_max_strict;
}

RegionAssumption::RegionAssumption(double xMin, double xMax, double yMin, double yMax, bool xMinStrict, bool xMaxStrict,
                                   bool yMinStrict, bool yMaxStrict, bool integer)
                                   : x_min(xMin), x_max(xMax), y_min(yMin), y_max(yMax),
                                   x_min_strict(xMinStrict), x_max_strict(xMaxStrict),
                                   y_min_strict(yMinStrict), y_max_strict(yMaxStrict),
                                   integer(integer) {
    if (integer) {
        if (x_min_strict) {
            x_min = std::floor(x_min) + 1;
            x_min_strict = false;
        } else {
            x_min = std::ceil(x_min);
        }
        if (y_min_strict) {
            y_min = std::floor(y_min) + 1;
            y_min_strict = false;
        } else {
            y_min = std::ceil(y_min);
        }
        if (x_max_strict) {
            x_max = std::ceil(x_max) - 1;
            x_max_strict = false;
        } else {
            x_max = std::floor(x_max);
        }
        if (y_max_strict) {
            y_max = std::ceil(y_max) - 1;
            y_max_strict = false;
        } else {
            y_max = std::floor(y_max);
        }
    }
}

UnionAssumption::UnionAssumption(std::vector<std::shared_ptr<Assumption>> assumptions) {
    std::copy_if(assumptions.begin(), assumptions.end(), std::back_inserter(this->assumptions),
        [](std::shared_ptr<Assumption> assumption) {
            return !assumption->isEmpty();
        }
    );
}

std::shared_ptr<Assumption> UnionAssumption::intersect(std::shared_ptr<Assumption> other) const {
    if (!std::dynamic_pointer_cast<RegionAssumption>(other) && !std::dynamic_pointer_cast<UnionAssumption>(other)) {
        return other->intersect(std::shared_ptr<UnionAssumption>((UnionAssumption*)this));
    }
    return opsHelper(other, [](auto a1, auto a2) { return a1->intersect(a2); });
}

std::shared_ptr<Assumption> UnionAssumption::add(std::shared_ptr<Assumption> other) const {
    if (!std::dynamic_pointer_cast<RegionAssumption>(other) && !std::dynamic_pointer_cast<UnionAssumption>(other)) {
        return other->add(std::shared_ptr<UnionAssumption>((UnionAssumption*)this));
    }
    return opsHelper(other, [](auto a1, auto a2) { return a1->add(a2); });
}

std::shared_ptr<Assumption> UnionAssumption::sub(std::shared_ptr<Assumption> other) const {
    if (!std::dynamic_pointer_cast<RegionAssumption>(other) && !std::dynamic_pointer_cast<UnionAssumption>(other)) {
        return other->sub(std::shared_ptr<UnionAssumption>((UnionAssumption*)this));
    }
    return opsHelper(other, [](auto a1, auto a2) { return a1->sub(a2); });
}

std::shared_ptr<Assumption> UnionAssumption::mul(std::shared_ptr<Assumption> other) const {
    if (!std::dynamic_pointer_cast<RegionAssumption>(other) && !std::dynamic_pointer_cast<UnionAssumption>(other)) {
        return other->mul(std::shared_ptr<UnionAssumption>((UnionAssumption*)this));
    }
    return opsHelper(other, [](auto a1, auto a2) { return a1->mul(a2); });
}

std::shared_ptr<Assumption> UnionAssumption::div(std::shared_ptr<Assumption> other) const {
    if (!std::dynamic_pointer_cast<RegionAssumption>(other) && !std::dynamic_pointer_cast<UnionAssumption>(other)) {
        return other->div(std::shared_ptr<UnionAssumption>((UnionAssumption*)this));
    }
    return opsHelper(other, [](auto a1, auto a2) { return a1->div(a2); });
}

std::shared_ptr<Assumption> UnionAssumption::neg() const {
    std::vector<std::shared_ptr<Assumption>> res;
    for (auto assumption: assumptions) res.push_back(assumption->neg());
    return std::make_shared<UnionAssumption>(res);
}

std::shared_ptr<Assumption> UnionAssumption::rec() const {
    std::vector<std::shared_ptr<Assumption>> res;
    for (auto assumption: assumptions) res.push_back(assumption->rec());
    return std::make_shared<UnionAssumption>(res);
}

bool UnionAssumption::operator==(std::shared_ptr<Assumption> other) const {
    return false;
}

bool UnionAssumption::isEmpty() const {
    return assumptions.empty();
}

bool UnionAssumption::isReal() const {
    return std::all_of(assumptions.begin(), assumptions.end(), [](auto a) {return a->isReal();});
}

std::string UnionAssumption::toString() const {
    std::stringstream res;
    res << "UnionAssumption{";
    for (auto it = assumptions.begin(); it < assumptions.end(); it++) {
        if (it != assumptions.begin()) res << ", ";
        res << (*it)->toString();
    }
    res << "}";
    return res.str();
}

std::shared_ptr<Assumption> Assumption::any() {
    return std::make_shared<RegionAssumption>(
            -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
            -std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity(),
            false, false, false, false, false
    );
}

std::shared_ptr<Assumption> Assumption::unite(std::shared_ptr<Assumption> other) const {
    std::vector<std::shared_ptr<Assumption>> res;
    res.push_back(std::shared_ptr<Assumption>((Assumption*)this));
    res.push_back(other);
    return std::make_shared<UnionAssumption>(res);
}

std::shared_ptr<RegionAssumption> Assumption::equals(double v) {
    return std::make_shared<RegionAssumption>(
            v, v, 0, 0,
            false, false, false, false, false
    );
}

std::shared_ptr<RegionAssumption> Assumption::greaterEquals(double v) {
    return std::make_shared<RegionAssumption>(
            v, std::numeric_limits<double>::infinity(), 0, 0,
            false, false, false, false, false
    );
}

std::shared_ptr<RegionAssumption> Assumption::greaterThan(double v) {
    return std::make_shared<RegionAssumption>(
            v, std::numeric_limits<double>::infinity(), 0, 0,
            true, false, false, false, false
    );
}

std::shared_ptr<RegionAssumption> Assumption::lessEquals(double v) {
    return std::make_shared<RegionAssumption>(
            -std::numeric_limits<double>::infinity(), v, 0, 0,
            false, false, false, false, false
    );
}

std::shared_ptr<RegionAssumption> Assumption::lessThan(double v) {
    return std::make_shared<RegionAssumption>(
            -std::numeric_limits<double>::infinity(), v, 0, 0,
            false, true, false, false, false
    );
}

std::shared_ptr<RegionAssumption> Assumption::real() {
    return std::make_shared<RegionAssumption>(
            -std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity(),
            0, 0,
            false, true, false, false, false
    );
}
