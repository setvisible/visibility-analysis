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

#ifndef WIDGETS_VIEWERWIDGET_H
#define WIDGETS_VIEWERWIDGET_H

#include <QtWidgets/QWidget>

class SceneManager;
class GraphicsView;

class QGraphicsScene;

namespace Ui {
class ViewerWidget;
}

class ViewerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerWidget(QWidget *parent = 0);
    ~ViewerWidget();

    void setModel(SceneManager *sceneManager);

    virtual QGraphicsScene* getScene() const;
    virtual GraphicsView* getView() const;

public Q_SLOTS:

private:
    Ui::ViewerWidget *ui;
    SceneManager *m_sceneManager;

    GraphicsView *m_graphicsView;
    QGraphicsScene *m_scene;
};

#endif // WIDGETS_VIEWERWIDGET_H
