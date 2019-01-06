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

#ifndef WIDGETS_GRAPHICS_RESULT_ITEM_H
#define WIDGETS_GRAPHICS_RESULT_ITEM_H

#include <Core/Result>
#include <QtWidgets/QGraphicsObject>

#include <QtGui/QBrush>

class QGraphicsPolygonItem;

class ResultItem : public QGraphicsObject
{
public:
    explicit ResultItem(QGraphicsItem *parent = Q_NULLPTR);

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    Result result() const;
    void setResult(const Result &result);

private:
    Result m_result;
    QGraphicsPolygonItem *m_polygonItem;

    QBrush m_brush;
    QBrush m_brushSelected;

    QPolygonF polygon() const;
};

#endif // WIDGETS_GRAPHICS_RESULT_ITEM_H
