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

#include "point.h"

#include <QtCore/QtGlobal> /* qFuzzyCompare() */
#include <QtCore/QJsonObject>

Point::Point()
    : m_uid(QString())
    , m_x(0)
    , m_y(0)
{
}

Point::Point(const qreal x, const qreal y)
    : m_uid(QString())
    , m_x(x)
    , m_y(y)
{
}

/******************************************************************************
 ******************************************************************************/
/* JSON Serialization */
/*! \brief Assign the Point's members values from the given \a json object.
 */
void Point::read(const QJsonObject &json)
{
    m_uid = json["uid"].toString();
    m_x = json["position_x"].toDouble();
    m_y = json["position_y"].toDouble();
}

/*! \brief Assigns the values from the Point to the given \a json object.
 */
void Point::write(QJsonObject &json) const
{
    json["uid"] = m_uid;
    json["position_x"] = m_x;
    json["position_y"] = m_y;
}

/******************************************************************************
 ******************************************************************************/
bool Point::operator==(const Point &other) const
{
    return qFuzzyCompare((*this).x(), other.x())
            && qFuzzyCompare((*this).y(), other.y());
}

bool Point::operator!=(const Point &other) const
{
    return ((*this) == other) ? false : true;
}
