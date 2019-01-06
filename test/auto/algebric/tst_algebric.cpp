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

#include <QtTest/QtTest>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include <istream>
#include <vector>

// Define the used kernel
//typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;

// Define the used kernel
typedef Kernel::Point_2    Point_2;
typedef Kernel::Segment_2  Segment_2;

class tst_Algebric : public QObject
{
    Q_OBJECT
private slots:
    void simple();
};

/***********************************************************************************
 ***********************************************************************************/
void tst_Algebric::simple()
{
    Point_2 p(0, 0.3), q, r(2, 0.9);
    {
      q = Point_2(1, 0.6);
      const bool actual = CGAL::collinear(p,q,r);
      const bool expected = false;
      QCOMPARE(actual, expected);
    }

    {
      std::istringstream input("0 0.3   1 0.6   2 0.9");
      input >> p >> q >> r;
      const bool actual = CGAL::collinear(p,q,r);
      const bool expected = true;
      QCOMPARE(actual, expected);
    }

    {
      q = CGAL::midpoint(p,r);
      const bool actual = CGAL::collinear(p,q,r);
      const bool expected = true;
      QCOMPARE(actual, expected);
    }
}


/***********************************************************************************
 ***********************************************************************************/

QTEST_APPLESS_MAIN(tst_Algebric)

#include "tst_algebric.moc"
