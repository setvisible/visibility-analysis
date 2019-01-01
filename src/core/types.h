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

#ifndef CGALTYPES_H
#define CGALTYPES_H

#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_naive_point_location.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Simple_polygon_visibility_2.h>
#include <CGAL/Triangular_expansion_visibility_2.h>

// Define the used kernel
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;

typedef Kernel::Point_2                                   Point_2;
typedef Kernel::Segment_2                                 Segment_2;

// Define arrangement
typedef CGAL::Arr_segment_traits_2<Kernel>                Traits_2;
typedef CGAL::Arrangement_2<Traits_2>                     Arrangement_2;
typedef Arrangement_2::Face_handle                        Face_handle;
typedef Arrangement_2::Edge_const_iterator                Edge_const_iterator;
typedef Arrangement_2::Ccb_halfedge_circulator            Ccb_halfedge_circulator;
typedef Arrangement_2::Halfedge_const_handle              Halfedge_const_handle;

// Define the used visibility class
typedef CGAL::Triangular_expansion_visibility_2<Arrangement_2>  TEV;

#endif // CGALTYPES_H
