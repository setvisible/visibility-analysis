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

#include <Core/Result>
#include <Core/Scene>
#include <Core/Solver>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif

/*! \class Manager
 *  \brief The class Manager is an adapter class for SceneManager.
 *
 * It manages the Undo/Redo Mechanism for the SceneManager.
 */
SceneManager::SceneManager(QObject *parent) : QObject(parent)
  , m_scene(QSharedPointer<Scene>(new Scene))
  , m_solver(QSharedPointer<Solver>(new Solver))
{
    this->clear();
}

/******************************************************************************
 ******************************************************************************/
/*!
 * \fn void SceneManager::changed()
 * \brief This signal is emitted whenever the SceneManager data is changed.
 */

/******************************************************************************
 ******************************************************************************/
void SceneManager::clear()
{
    m_scene->setTitle(QStringLiteral("untitled"));
    m_scene->setAuthor(QStringLiteral("-"));
    m_scene->setDate(QStringLiteral("-"));
    m_scene->setDescription(QString());

    // ...

}

/******************************************************************************
 ******************************************************************************/
/* SERIALISATION JSON */
/*! \brief Assign the SceneManager's members values from the given \a json object.
 */
void SceneManager::read(const QJsonObject &json)
{
    clear();
    m_scene->read(json);
    emit changed();
    qDebug() << "Loaded: [title: "  << m_scene->title()
             << ", description: "   << m_scene->description()
             << ", date: "          << m_scene->date()
             << ", author: "        << m_scene->author()
             <<"]";
}

/*! \brief Assigns the values from the SceneManager to the given \a json object.
 */
void SceneManager::write(QJsonObject &json) const
{
    m_scene->write(json);
}

/******************************************************************************
 ******************************************************************************/
Result SceneManager::result() const
{
    return m_result;
}

/******************************************************************************
 ******************************************************************************/
void SceneManager::recalculate()
{
    /// \todo Use worker thread here.
    /// \todo see  Mandelbrot Example  or  Blocking Fortune Client Example
    if (m_solver && m_scene) {
        m_result = m_solver->calculate(m_scene.data(), Point(0,0));
    } else {
        m_result.clear();
    }
    emit resultsChanged();
}
