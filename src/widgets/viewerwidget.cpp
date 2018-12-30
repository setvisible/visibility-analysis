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

#include "viewerwidget.h"
#include "ui_viewerwidget.h"

#include <Widgets/GraphicsView>

#include <QtWidgets/QGraphicsScene>

ViewerWidget::ViewerWidget(QWidget *parent) : QWidget(parent)
  , ui(new Ui::ViewerWidget)
  , m_sceneManager(Q_NULLPTR)
  , m_graphicsView(new GraphicsView(this))
  , m_scene(new QGraphicsScene(-100, -100, 100, 100))
{
    ui->setupUi(this);

    layout()->addWidget(m_graphicsView);
    m_graphicsView->setScene(m_scene);
    m_graphicsView->setMouseTracking(true);
}

ViewerWidget::~ViewerWidget()
{
    delete ui;
}

/******************************************************************************
 ******************************************************************************/
void ViewerWidget::setModel(SceneManager *sceneManager)
{
    m_sceneManager = sceneManager;
}

QGraphicsScene* ViewerWidget::getScene() const
{
  return m_scene;
}

GraphicsView* ViewerWidget::getView() const
{
  return m_graphicsView;
}
