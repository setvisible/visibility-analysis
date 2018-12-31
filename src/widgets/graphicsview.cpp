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

#include "graphicsview.h"

#include <QtCore/QVarLengthArray>
#include <QtGui/QPen>
#include <QtGui/QWheelEvent>

static const double C_SCALE_FACTOR = 1.15;

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
  , m_isGridVisible(false)
  , m_gridSize(50)
  , m_gridColor(Qt::black)
  , m_backgroundColor(Qt::white)
{
    zoomFit();
    setBackgroundBrush(QBrush(m_backgroundColor));
}

GraphicsView::~GraphicsView()
{
}

/******************************************************************************
 ******************************************************************************/
void GraphicsView::setGridVisible(bool visible)
{
    m_isGridVisible = visible;
}

bool GraphicsView::isGridVisible() const
{
    return m_isGridVisible;
}

void GraphicsView::setGridSize(int size)
{
    m_gridSize = size;
}

int GraphicsView::gridSize() const
{
    return m_gridSize;
}

void GraphicsView::setGridColor(QColor color)
{
    m_gridColor = color;
}

QColor GraphicsView::gridColor() const
{
    return m_gridColor;
}

void GraphicsView::setBackgroundColor(QColor color)
{
    m_backgroundColor = color;
}

QColor GraphicsView::backgroundColor() const
{
    return m_backgroundColor;
}

/******************************************************************************
 ******************************************************************************/
void GraphicsView::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    const QRectF viewportRect = getViewportRect();
    if (m_isGridVisible) {
        // compute integer-spaced grid lines
        QVarLengthArray<QLineF, 100> linesX;
        QVarLengthArray<QLineF, 100> linesY;
        const qreal left = int(viewportRect.left()) - (int(viewportRect.left()) % m_gridSize);
        const qreal top = int(viewportRect.top()) - (int(viewportRect.top()) % m_gridSize);

        for(qreal x = left; x < viewportRect.right(); x += m_gridSize) {
            linesX.append(QLineF(x, viewportRect.top(), x, viewportRect.bottom()));
        }
        for(qreal y = top; y < viewportRect.bottom(); y += m_gridSize){
            linesY.append(QLineF(viewportRect.left(), y, viewportRect.right(), y));
        }

        // set up the painter
        QPen savePen = painter->pen();
        QPen gridPen(savePen);
        gridPen.setColor(m_gridColor);
        painter->setPen(gridPen);

        // draw the grid
        painter->drawLines(linesX.data(), linesX.size());
        painter->drawLines(linesY.data(), linesY.size());

        // revert the painter
        painter->setPen(savePen);
    }
}

/******************************************************************************
 ******************************************************************************/
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    if (event->delta() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
}

/******************************************************************************
 ******************************************************************************/
void GraphicsView::zoomFit()
{
    const QMatrix matrix(1.0, 0.0, 0.0, -1.0, 0.0, 0.0);
    this->setMatrix(matrix);
}

void GraphicsView::zoomIn()
{
    this->scale(C_SCALE_FACTOR, C_SCALE_FACTOR);
}

void GraphicsView::zoomOut()
{
    this->scale(1.0 / C_SCALE_FACTOR, 1.0 / C_SCALE_FACTOR);
}

/******************************************************************************
 ******************************************************************************/
QRectF GraphicsView::getViewportRect() const
{
    const QPointF p1 = mapToScene(0, 0);
    const QPointF p2 = mapToScene(width(), height());

    const double xmin = qMin(p1.x(), p2.x());
    const double xmax = qMax(p1.x(), p2.x());
    const double ymin = qMin(p1.y(), p2.y());
    const double ymax = qMax(p1.y(), p2.y());

    const QRectF res = QRectF(QPointF(xmin, ymin), QPointF(xmax, ymax));
    return res;
}
