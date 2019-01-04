/* - Visibility Analysis - Copyright (C) 2018 Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORE_SOLVER_H
#define CORE_SOLVER_H

#include <Core/Result>
#include <Core/Scene>
#include <Core/Point>

class Solver
{
public:
    explicit Solver();

    void solve_method1();
    void solve_method2();

    Result calculate(const Scene *scene, const Point &query) const;
};

#endif // CORE_SOLVER_H
