/* - Visibility Analysis - Copyright (C) 2018-2019 Sebastien Vavassori
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

#include "resultitem.h"

#include <QtCore/QDebug>
#include <QtGui/QCursor>
#include <QtGui/QPainter>

#define C_LINE_SIZE 1.0

/*!
 * \class ResultItem
 * \brief Draw the result polygon.
 */
ResultItem::ResultItem(QGraphicsItem *parent) : QGraphicsObject(parent)
  , m_polygonItem(new QGraphicsPolygonItem(this))
  , m_brush(QBrush(QColor(153, 217, 234, 126))) /* cyan */
  , m_brushSelected(QBrush(QColor(217, 153, 234, 126))) /* pink */
{
    this->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    this->setCursor(Qt::SizeAllCursor);

    this->setZValue(100);

    m_polygonItem->setFillRule(Qt::WindingFill);
    m_polygonItem->setPen(Qt::NoPen);
}

Result ResultItem::result() const
{
    return m_result;
}

void ResultItem::setResult(const Result &result)
{
    m_result = result;
    m_polygonItem->setPolygon(polygon());
    QGraphicsItem::update();
}

QRectF ResultItem::boundingRect() const
{
    return m_polygonItem->boundingRect();
}

QPainterPath ResultItem::shape() const
{
    QPainterPath path;
    path.addPolygon(this->polygon());
    path.closeSubpath();
    QPainterPathStroker stroker;
    stroker.setWidth(C_LINE_SIZE);
    return stroker.createStroke(path);
}

void ResultItem::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    bool selected = isSelected();
    if (selected) {
        m_polygonItem->setBrush(m_brushSelected);
    } else {
        m_polygonItem->setBrush(m_brush);
    }
}

QPolygonF ResultItem::polygon() const
{
    QPolygonF polygon;
    foreach (auto segment, m_result.segments()) {
        const QPointF point = QPointF(segment.point1().x(), segment.point1().y());
        polygon << point;
    }
    if (m_result.segments().size() > 0) {
        // Close the polygon
        Point firstPoint = m_result.segments().first().point1();
        polygon << QPointF(firstPoint.x(), firstPoint.y());
    }
    return polygon;
}
