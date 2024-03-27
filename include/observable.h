#pragma once

#include <string>
#include <memory>
#include <vector>

#include "ordered_map.h"

class Simulation; // Forward declaration

/* -------------------------------- */

class Observable {
public:
    explicit Observable(const Simulation& _sim, int _freq, const std::string& _out_unit);
    virtual void calculate() = 0;
    ~Observable();

    void initialize(std::vector<std::string> _labels);
    void resetValues();

    tsl::ordered_map<std::string, double> quantities;

protected:
    const Simulation& sim; // Reference to the simulation object
    int freq;              // Frequency at which the observable is recorded
    std::string out_unit;  // Units of the output quantities
};

/* -------------------------------- */

class ObservableFactory {
public:
    std::unique_ptr<Observable> createQuantity(const std::string& observable_type, const Simulation& _sim, int _freq, const std::string& _out_unit);
};

/* -------------------------------- */

class EnergyObservable : public Observable {
public:
    EnergyObservable(const Simulation& _sim, int _freq, const std::string& _out_unit);

    void calculate() override;
private:
    double primitiveKineticDistinguishable();
    void calculateClassicalKinetic();
    void calculateClassicalPotential();
    void calculateKinetic();
    void calculatePotential();
};