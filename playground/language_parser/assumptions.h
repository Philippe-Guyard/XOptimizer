//
// Created by Nykyta Ostapliuk on 18.10.2021 AD.
//

#ifndef XOPTIMIZER_ASSUMPTIONS_H
#define XOPTIMIZER_ASSUMPTIONS_H

#include <memory>
#include <vector>

namespace XOptimizer {
    namespace Assumptions {
        class RegionAssumption;
        class Assumption {
        public:
            static std::shared_ptr<Assumption> any();
            static std::shared_ptr<RegionAssumption> equals(double v);
            static std::shared_ptr<RegionAssumption> greaterThan(double v);
            static std::shared_ptr<RegionAssumption> greaterEquals(double v);
            static std::shared_ptr<RegionAssumption> lessThan(double v);
            static std::shared_ptr<RegionAssumption> lessEquals(double v);
            static std::shared_ptr<RegionAssumption> real();
            virtual std::shared_ptr<Assumption> intersect(std::shared_ptr<Assumption> other) const = 0;
            virtual std::shared_ptr<Assumption> add(std::shared_ptr<Assumption> other) const = 0;
            virtual std::shared_ptr<Assumption> sub(std::shared_ptr<Assumption> other) const = 0;
            virtual std::shared_ptr<Assumption> mul(std::shared_ptr<Assumption> other) const = 0;
            virtual std::shared_ptr<Assumption> div(std::shared_ptr<Assumption> other) const = 0;
            virtual std::shared_ptr<Assumption> neg() const = 0;
            virtual std::shared_ptr<Assumption> rec() const = 0;
            virtual std::shared_ptr<Assumption> unite(std::shared_ptr<Assumption> other) const;
            virtual bool implies(std::shared_ptr<Assumption> other) const {
                auto intersection = intersect(other);
                return operator==(intersection);
            }
            virtual bool isEmpty() const = 0;
            virtual bool isReal() const = 0;
            virtual bool operator==(std::shared_ptr<Assumption> other) const = 0;
            virtual bool operator!=(std::shared_ptr<Assumption> other) const {
                return !(operator==(other));
            }
            virtual std::string toString() const = 0;
        };
        class RegionAssumption: public Assumption {
            double x_min, x_max, y_min, y_max;
            bool x_min_strict, x_max_strict, y_min_strict, y_max_strict, integer;
            template<typename T>
            typename std::enable_if<
                    std::is_same<
                        std::tuple<double, bool>,
                        decltype((*(T*)0)(0.0, false, 0.0, false, false, false))
                    >::value,
                    std::shared_ptr<RegionAssumption>
            >::type opsHelper(std::shared_ptr<RegionAssumption> other, T func) const {
                auto [new_x_min, new_x_min_strict] = func(
                        x_min, x_min_strict,
                        other->x_min, other->x_min_strict,
                        false, false
                );
                auto [new_y_min, new_y_min_strict] = func(
                        y_min, y_min_strict,
                        other->y_min, other->y_min_strict,
                        true, false
                );
                auto [new_x_max, new_x_max_strict] = func(
                        x_max, x_max_strict,
                        other->x_max, other->x_max_strict,
                        false, true
                );
                auto [new_y_max, new_y_max_strict] = func(
                        y_max, y_max_strict,
                        other->y_max, other->y_max_strict,
                        true, true
                );
                return std::make_shared<RegionAssumption>(
                        new_x_min, new_x_max,
                        new_y_min, new_y_max,
                        new_x_min_strict, new_x_max_strict,
                        new_y_min_strict, new_y_max_strict,
                        other->integer
                );
            }
        public:
            RegionAssumption(double xMin, double xMax, double yMin, double yMax,
                             bool xMinStrict, bool xMaxStrict,
                             bool yMinStrict, bool yMaxStrict, bool integer);

            double getXMin() const {
                return x_min;
            }

            double getXMax() const {
                return x_max;
            }

            double getYMin() const {
                return y_min;
            }

            double getYMax() const {
                return y_max;
            }

            bool isXMinStrict() const {
                return x_min_strict;
            }

            bool isXMaxStrict() const {
                return x_max_strict;
            }

            bool isYMinStrict() const {
                return y_min_strict;
            }

            bool isYMaxStrict() const {
                return y_max_strict;
            }

            bool isInteger() const {
                return integer;
            }

            std::shared_ptr<Assumption> intersect(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> add(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> sub(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> mul(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> div(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> neg() const override;
            std::shared_ptr<Assumption> rec() const override;
            std::shared_ptr<RegionAssumption> makeInteger(bool v) const {
                return std::make_shared<RegionAssumption>(
                        x_min, x_max, y_min, y_max,
                        x_min_strict, x_max_strict,
                        y_min_strict, y_max_strict,
                        v
                );
            }
            bool operator==(std::shared_ptr<Assumption> other) const override;
            bool isEmpty() const override;
            bool isReal() const override;
            std::string toString() const override;
        };

        class UnionAssumption: public Assumption {
            std::vector<std::shared_ptr<Assumption>> assumptions;
            template<typename T>
            typename std::enable_if<
                    std::is_same<
                            std::shared_ptr<Assumption>,
                            decltype((*(T*)0)(std::shared_ptr<Assumption>(), std::shared_ptr<Assumption>()))
                    >::value,
                    std::shared_ptr<Assumption>
            >::type opsHelper(std::shared_ptr<Assumption> other, T func) const {
                if (other->isEmpty()) return other;
                std::vector<std::shared_ptr<Assumption>> res, other_assumptions;
                if (auto regionAssumption = std::dynamic_pointer_cast<RegionAssumption>(other)) {
                    other_assumptions.push_back(regionAssumption);
                } else if (auto unionAssumption = std::dynamic_pointer_cast<UnionAssumption>(other)) {
                    other_assumptions = unionAssumption->assumptions;
                }
                for (auto assumption1: assumptions) {
                    for (auto assumption2: other_assumptions) {
                        auto assumption = func(assumption1, assumption2);
                        if (!assumption->isEmpty()) res.push_back(assumption);
                    }
                }
                return std::make_shared<UnionAssumption>(res);
            }
        public:
            explicit UnionAssumption(std::vector<std::shared_ptr<Assumption>> assumptions);

            const std::vector<std::shared_ptr<Assumption>> &getAssumptions() const {
                return assumptions;
            }

            std::shared_ptr<Assumption> intersect(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> add(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> sub(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> mul(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> div(std::shared_ptr<Assumption> other) const override;
            std::shared_ptr<Assumption> neg() const override;
            std::shared_ptr<Assumption> rec() const override;
            bool operator==(std::shared_ptr<Assumption> other) const override;
            bool isEmpty() const override;
            bool isReal() const override;
            std::string toString() const override;
        };
    }
}

#endif //XOPTIMIZER_ASSUMPTIONS_H
