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

#ifndef CORE_POINT_H
#define CORE_POINT_H

#include <QtCore/QtGlobal>
#include <QtCore/QString>

QT_BEGIN_NAMESPACE
class QJsonObject;
QT_END_NAMESPACE

class Point
{
public:
    explicit Point();
    explicit Point(const qreal x, const qreal y);

    /* JSON Serialization */
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;

    qreal x() const { return m_x; }
    qreal y() const { return m_y; }

private:
    QString m_uid;
    qreal m_x;
    qreal m_y;
};

#endif // CORE_POINT_H
