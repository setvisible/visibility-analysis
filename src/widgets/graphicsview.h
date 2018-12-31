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

#ifndef WIDGETS_GRAPHICSVIEW_H
#define WIDGETS_GRAPHICSVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtGui/QColor>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicsView(QWidget *parent = Q_NULLPTR);
    ~GraphicsView();

    bool isGridVisible() const;

    void setGridSize(int size);
    int gridSize() const;

    void setGridColor(QColor color);
    QColor gridColor() const;

    void setBackgroundColor(QColor color);
    QColor backgroundColor() const;

    QRectF getViewportRect() const;

Q_SIGNALS:

public Q_SLOTS:
    void setGridVisible(bool visible);

protected:
    virtual void drawForeground(QPainter *painter, const QRectF &rect);

private:
    bool m_isGridVisible;
    int m_gridSize;
    QColor m_gridColor;
    QColor m_backgroundColor;

};

#endif // WIDGETS_GRAPHICSVIEW_H
