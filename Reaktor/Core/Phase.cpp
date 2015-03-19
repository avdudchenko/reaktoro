// Reaktor is a C++ library for computational reaction modelling.
//
// Copyright (C) 2014 Allan Leal
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "Phase.hpp"

// Reaktor includes
#include <Reaktor/Common/Constants.hpp>

namespace Reaktor {

struct Phase::Impl
{
    PhaseData data;

    std::vector<Element> elements;
};

Phase::Phase()
: pimpl(new Impl())
{}

Phase::Phase(const PhaseData& data)
: pimpl(new Impl{data, collectElements(data.species)})
{}

auto Phase::numElements() const -> unsigned
{
    return elements().size();
}

auto Phase::numSpecies() const -> unsigned
{
    return species().size();
}

auto Phase::name() const -> const std::string&
{
    return pimpl->data.name;
}

auto Phase::elements() const -> const std::vector<Element>&
{
    return pimpl->elements;
}

auto Phase::species() const -> const std::vector<Species>&
{
    return pimpl->data.species;
}

auto Phase::species(Index index) const -> const Species&
{
    return pimpl->data.species[index];
}

auto Phase::data() const -> const PhaseData&
{
    return pimpl->data;
}

auto Phase::standardGibbsEnergies(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardGibbsEnergy(T, P);
    return res;
}

auto Phase::standardEnthalpies(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardEnthalpy(T, P);
    return res;
}

auto Phase::standardHelmholtzEnergies(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardHelmholtzEnergy(T, P);
    return res;
}

auto Phase::standardEntropies(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardEntropy(T, P);
    return res;
}

auto Phase::standardVolumes(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardVolume(T, P);
    return res;
}

auto Phase::standardInternalEnergies(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardInternalEnergy(T, P);
    return res;
}

auto Phase::standardHeatCapacities(double T, double P) const -> ThermoVector
{
    const unsigned num_species = numSpecies();
    ThermoVector res(num_species);
    for(unsigned i = 0; i < num_species; ++i)
        res.row(i) = species(i).standardHeatCapacity(T, P);
    return res;
}

auto Phase::concentrations(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.concentrations(T, P, n);
}

auto Phase::lnActivityCoefficients(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.ln_activity_coefficients(T, P, n);
}

auto Phase::lnActivities(double T, double P, const Vector& n) const -> ChemicalVector
{
    return pimpl->data.ln_activities(T, P, n);
}

auto Phase::chemicalPotentials(double T, double P, const Vector& n) const -> ChemicalVector
{
    const double R = universalGasConstant;
    ThermoVector u0 = standardGibbsEnergies(T, P);
    ChemicalVector ln_a = lnActivities(T, P, n);
    ChemicalVector u = lnActivities(T, P, n);
    u.val = u0.val + R*T*ln_a.val;
    u.ddt = u0.ddt + R*T*ln_a.ddt + R*ln_a.val;
    u.ddp = u0.ddp + R*T*ln_a.ddp;
    u.ddn = R*T*ln_a.ddn;
    return u;
}

auto Phase::molarVolume(double T, double P, const Vector& n) const -> ChemicalScalar
{
    return pimpl->data.molar_volume(T, P, n);
}

auto operator<(const Phase& lhs, const Phase& rhs) -> bool
{
    return lhs.name() < rhs.name();
}

auto operator==(const Phase& lhs, const Phase& rhs) -> bool
{
    return lhs.name() == rhs.name();
}

auto collectSpecies(const std::vector<Phase>& phases) -> std::vector<Species>
{
    unsigned num_species = 0;
    for(const Phase& phase : phases)
        num_species += phase.species().size();

    std::vector<Species> list;
    list.reserve(num_species);
    for(const Phase& phase : phases)
        for(const Species& iter : phase.species())
            list.push_back(iter);
    return list;
}

} // namespace Reaktor
