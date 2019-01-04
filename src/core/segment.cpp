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

#include "segment.h"

Segment::Segment(const Point &point1, const Point &point2)
    : m_point1(point1)
    , m_point2(point2)
{    
}

Segment::Segment(qreal x1, qreal y1, qreal x2, qreal y2)
    : m_point1(Point(x1, y1))
    , m_point2(Point(x2, y2))
{
}

/******************************************************************************
 ******************************************************************************/
bool Segment::operator==(const Segment &other) const
{
    return m_point1 == other.m_point1
            && m_point2 == other.m_point2;

}

bool Segment::operator!=(const Segment &other) const
{
    return ((*this) == other) ? false : true;
}
