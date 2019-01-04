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

#include <Core/Solver>

#include <QtTest/QtTest>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

class tst_Solver : public QObject
{
    Q_OBJECT
private slots:
    void simple();
};

/***********************************************************************************
 ***********************************************************************************/
void tst_Solver::simple()
{
    // Given
    QSharedPointer<Scene> scene(QSharedPointer<Scene>(new Scene));

    // Defining the input geometry
    Point p1(1,2), p2(12, 3), p3(19,-2), p4(12,6), p5(14,14), p6( 9,5);
    Point h1(8,3), h2(10, 3), h3( 8, 4), h4(10,6), h5(11, 6), h6(11,7);

    scene->addSegment(Segment(p1, p2));
    scene->addSegment(Segment(p2, p3));
    scene->addSegment(Segment(p3, p4));
    scene->addSegment(Segment(p4, p5));
    scene->addSegment(Segment(p5, p6));
    scene->addSegment(Segment(p6, p1));

    scene->addSegment(Segment(h1, h2));
    scene->addSegment(Segment(h2, h3));
    scene->addSegment(Segment(h3, h1));
    scene->addSegment(Segment(h4, h5));
    scene->addSegment(Segment(h5, h6));
    scene->addSegment(Segment(h6, h4));

    Point query = p4;

    // Defining the expected output
    Result expected;
    expected.addSegment(Segment( 19, -2             , 12, 6));
    expected.addSegment(Segment( 12,  6             , 14,14));
    expected.addSegment(Segment( 14, 14             , 10.4286, 7.57143));
    expected.addSegment(Segment( 10.4286, 7.57143   , 11, 7));
    expected.addSegment(Segment( 11, 7              , 11, 6));
    expected.addSegment(Segment( 11, 6              , 10, 6));
    expected.addSegment(Segment( 10, 6              , 9.55556, 6));
    expected.addSegment(Segment( 9.55556, 6         , 9, 5));
    expected.addSegment(Segment( 9, 5               , 1, 2));
    expected.addSegment(Segment( 1, 2               , 4.66667, 2.33333));
    expected.addSegment(Segment( 4.66667, 2.33333   , 8, 4));
    expected.addSegment(Segment( 8, 4               , 10, 3));
    expected.addSegment(Segment( 10, 3              , 9.87097, 2.80645));
    expected.addSegment(Segment( 9.87097, 2.80645   , 12, 3));
    expected.addSegment(Segment( 12, 3              , 19, -2));

    Solver target;

    // When
    Result actual = target.calculate(scene.data(), query);

    // Then   
    QCOMPARE(actual, expected);
}


/***********************************************************************************
 ***********************************************************************************/

QTEST_APPLESS_MAIN(tst_Solver)

#include "tst_solver.moc"
