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

#include "scene.h"


#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif
#ifdef QT_TESTLIB_LIB
#  include <QtTest/QTest>
#endif

Scene::Scene()
    : m_title(QString())
    , m_author(QString())
    , m_date(QString())
    , m_description(QString())
{
}

/******************************************************************************
 ******************************************************************************/
/* JSON Serialization */
/*! \brief Assign the Scene's members values from the given \a json object.
 */
void Scene::read(const QJsonObject &json)
{
    m_title = json["title"].toString();
    m_author = json["author"].toString();
    m_date = json["date"].toString();
    m_description = json["description"].toString();

    m_points.clear();
    QJsonArray pointsArray = json["points"].toArray();
     for (int i = 0; i < pointsArray.size(); ++i) {
         QJsonObject pointObject = pointsArray[i].toObject();
         Point point;
         point.read(pointObject);
         m_points.append(point);
     }

     m_segments.clear();
     QJsonArray spacesArray = json["segments"].toArray();
     for (int i = 0; i < spacesArray.size(); ++i) {
         QJsonObject segmentObject = spacesArray[i].toObject();
         Segment segment;
         segment.read(segmentObject);
         m_segments.append(segment);
     }

     // Try to resolve correspondance segments <-> points
}

/*! \brief Assigns the values from the Scene to the given \a json object.
 */
void Scene::write(QJsonObject &json) const
{
    json["title"] = m_title;
    json["author"] = m_author;
    json["date"] = m_date;
    json["description"] = m_description;

    QJsonArray pointsArray;
    foreach (const Point point, m_points) {
        QJsonObject pointObject;
        point.write(pointObject);
        pointsArray.append(pointObject);
    }
    json["points"] = pointsArray;

    QJsonArray segmentsArray;
    foreach (const Segment segment, m_segments) {
        QJsonObject segmentObject;
        segment.write(segmentObject);
        segmentsArray.append(segmentObject);
    }
    json["segments"] = segmentsArray;
}

/******************************************************************************
 ******************************************************************************/
QString Scene::title() const
{
    return m_title;
}

void Scene::setTitle(const QString &title)
{
    m_title = title;
}

/******************************************************************************
 ******************************************************************************/
QString Scene::author() const
{
    return m_author;
}

void Scene::setAuthor(const QString &author)
{
    m_author = author;
}

/******************************************************************************
 ******************************************************************************/
QString Scene::date() const
{
    return m_date;
}

void Scene::setDate(const QString &date)
{
    m_date = date;
}

/******************************************************************************
 ******************************************************************************/
QString Scene::description() const
{
    return m_description;
}
void Scene::setDescription(const QString &description)
{
    m_description = description;
}

/******************************************************************************
 ******************************************************************************/
void Scene::addSegment(const Point &point1, const Point &point2)
{
    m_segments.append(Segment(point1, point2));
}

void Scene::addSegment(const Segment &segment)
{
    m_segments.append(segment);
}

void Scene::removeSegment(const Segment &segment)
{
    m_segments.removeAll(segment);
}

void Scene::removeSegmentAt(const int index)
{
    m_segments.removeAt(index);
}

void Scene::removeAllSegments()
{
    m_segments.clear();
}

QList<Segment> Scene::segments() const
{
    return m_segments;
}

/******************************************************************************
 ******************************************************************************/
