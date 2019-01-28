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

#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include <Core/Point>
#include <Core/Segment>

#include <QtCore/QString>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE
class QJsonObject;
QT_END_NAMESPACE

class Scene
{
public:
    explicit Scene();

    /* JSON Serialization */
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QString title() const;
    void setTitle(const QString &title);

    QString author() const;
    void setAuthor(const QString &author);

    QString date() const;
    void setDate(const QString &date);

    QString description() const;
    void setDescription(const QString &description);

    void addSegment(const Point &point1, const Point &point2);
    void addSegment(const Segment &segment);
    void removeSegment(const Segment &segment);
    void removeSegmentAt(const int index);
    void removeAllSegments();
    QList<Segment> segments() const;

private:
    QString m_title;
    QString m_author;
    QString m_date;
    QString m_description;

    QList<Point> m_points;
    QList<Segment> m_segments;
};

#endif // CORE_SCENE_H
