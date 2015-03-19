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

#pragma once

// Reaktor includes
#include <Reaktor/Thermodynamics/Activity/GaseousActivity.hpp>

namespace Reaktor {

/// Create the gaseous activity function of species CO<sub>2</sub>(g) based on the model of Duan et al. (2006)
///
/// @b References
/// 1. Duan, Z., Sun, R., Zhu, C., Chou, I. (2006). An improved model for the calculation of CO2 solubility in aqueous mixtures containing Na+, K+, Ca2+, Mg2+, Cl-, and SO42-. Marine Chemistry, 98(2-4), 131–139. doi:10.1016/j.marchem.2005.09.001
///
/// @param mixture The gaseous mixture instance
/// @return The gaseous activity function of species CO<sub>2</sub>(g)
/// @see GaseousMixture, GaseousActivity
auto gaseousActivityDuanSunCO2(const GaseousMixture& mixture) -> GaseousActivity;

} // namespace Reaktor
