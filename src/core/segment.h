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

#ifndef CORE_SEGMENT_H
#define CORE_SEGMENT_H

#include <Core/Point>

class Segment
{
public:
    explicit Segment(const Point &point1, const Point &point2);
    explicit Segment(qreal x1, qreal y1, qreal x2, qreal y2);

    bool operator==(const Segment &other) const;
    bool operator!=(const Segment &other) const;

    Point point1() const { return m_point1; }
    Point point2() const { return m_point2; }

private:
    Point m_point1;
    Point m_point2;
};


#endif // CORE_SEGMENT_H
