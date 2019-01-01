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

#include "solver.h"

#include "types.h"
#include <Core/Scene>

#include <istream>
#include <vector>

Solver::Solver()
{
}

/******************************************************************************
 ******************************************************************************/
Result Solver::calculate(const Scene */*scene*/)
{
    /// \todo implement
    return Result();
}

/******************************************************************************
 ******************************************************************************/
void Solver::solve_method1()
{
    //create environment
    Point_2 p1(0,4), p2(0,0), p3(3,2), p4(4,0), p5(4,4), p6(1,2);
    std::vector<Segment_2> segments;
    segments.push_back(Segment_2(p1, p2));
    segments.push_back(Segment_2(p2, p3));
    segments.push_back(Segment_2(p3, p4));
    segments.push_back(Segment_2(p4, p5));
    segments.push_back(Segment_2(p5, p6));
    segments.push_back(Segment_2(p6, p1));

    Arrangement_2 env;
    CGAL::insert_non_intersecting_curves(env,segments.begin(),segments.end());

    // find the face of the query point
    // (usually you may know that by other means)
    Point_2 q(0.5, 2);
    Arrangement_2::Face_const_handle * face;
    CGAL::Arr_naive_point_location<Arrangement_2> pl(env);
    CGAL::Arr_point_location_result<Arrangement_2>::Type obj = pl.locate(q);
    // The query point locates in the interior of a face
    face = boost::get<Arrangement_2::Face_const_handle> (&obj);

    // compute non regularized visibility area
    // Define visibiliy object type that computes non-regularized visibility area
    typedef CGAL::Simple_polygon_visibility_2<Arrangement_2, CGAL::Tag_false> NSPV;
    Arrangement_2 non_regular_output;
    NSPV non_regular_visibility(env);

    non_regular_visibility.compute_visibility(q, *face, non_regular_output);

    std::cout << "Non-regularized visibility region of q has "
              << non_regular_output.number_of_edges()
              << " edges:" << std::endl;
    for (Edge_const_iterator eit = non_regular_output.edges_begin(); eit != non_regular_output.edges_end(); ++eit)
        std::cout << "[" << eit->source()->point() << " -> " << eit->target()->point() << "]" << std::endl;

    // compute regularized visibility area
    // Define visibiliy object type that computes regularized visibility area
    typedef CGAL::Simple_polygon_visibility_2<Arrangement_2, CGAL::Tag_true> RSPV;
    Arrangement_2 regular_output;
    RSPV regular_visibility(env);

    regular_visibility.compute_visibility(q, *face, regular_output);

    std::cout << "Regularized visibility region of q has "
              << regular_output.number_of_edges()
              << " edges:" << std::endl;
    for (Edge_const_iterator eit = regular_output.edges_begin();
         eit != regular_output.edges_end(); ++eit) {
        std::cout << "[" << eit->source()->point()
                  << " -> " << eit->target()->point()
                  << "]" << std::endl;
    }
    //return 0;
}

void Solver::solve_method2()
{
    // Defining the input geometry
    Point_2 p1(1,2), p2(12, 3), p3(19,-2), p4(12,6), p5(14,14), p6( 9,5);
    Point_2 h1(8,3), h2(10, 3), h3( 8, 4), h4(10,6), h5(11, 6), h6(11,7);
    std::vector<Segment_2> segments;
    segments.push_back(Segment_2(p1,p2));
    segments.push_back(Segment_2(p2,p3));
    segments.push_back(Segment_2(p3,p4));
    segments.push_back(Segment_2(p4,p5));
    segments.push_back(Segment_2(p5,p6));
    segments.push_back(Segment_2(p6,p1));

    segments.push_back(Segment_2(h1,h2));
    segments.push_back(Segment_2(h2,h3));
    segments.push_back(Segment_2(h3,h1));
    segments.push_back(Segment_2(h4,h5));
    segments.push_back(Segment_2(h5,h6));
    segments.push_back(Segment_2(h6,h4));

    // insert geometry into the arrangement
    Arrangement_2 env;
    CGAL::insert_non_intersecting_curves(env,segments.begin(),segments.end());

    //Find the halfedge whose target is the query point.
    //(usually you may know that already by other means)
    Point_2 query_point = p4;
    Halfedge_const_handle he = env.halfedges_begin();
    while (he->source()->point() != p3 || he->target()->point() != p4)
        he++;

    //visibility query
    Arrangement_2 output_arr;
    TEV tev(env);
    Face_handle fh = tev.compute_visibility(query_point, he, output_arr);

    //print out the visibility region.
    std::cout << "Regularized visibility region of q has "
              << output_arr.number_of_edges()
              << " edges." << std::endl;

    std::cout << "Boundary edges of the visibility region:" << std::endl;
    Arrangement_2::Ccb_halfedge_circulator curr = fh->outer_ccb();
    std::cout << "[" << curr->source()->point() << " -> " << curr->target()->point() << "]" << std::endl;
    while (++curr != fh->outer_ccb())
        std::cout << "[" << curr->source()->point() << " -> " << curr->target()->point() << "]"<< std::endl;

}
