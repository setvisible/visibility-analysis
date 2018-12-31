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

#include "scenemanager.h"

#include "scene.h"


/*! \class Manager
 *  \brief The class Manager is an adapter class for SceneManager.
 *
 * It manages the Undo/Redo Mechanism for the SceneManager.
 */
SceneManager::SceneManager(QObject *parent) : QObject(parent)
  , m_scene(new Scene(this))
{
    this->clear();
}

/******************************************************************************
 ******************************************************************************/
/*! \brief Clear and emit the change, in order to update the views,
 * that derive from AbstractSceneView.
 */
void SceneManager::clear()
{
}

/******************************************************************************
 ******************************************************************************/
/* SERIALISATION */
void SceneManager::read(QByteArray &bytes, bool *ok)
{
}

void SceneManager::write(QByteArray &bytes) const
{
}
