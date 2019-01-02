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

#ifndef CORE_SCENEMANAGER_H
#define CORE_SCENEMANAGER_H

#include <Core/Result>

#include <QtCore/QObject>
#include <QtCore/QtContainerFwd> /* Forward Declarations of the Qt's Containers */

#include <QtCore/QSet>
#include <QtCore/QSharedPointer>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class Scene;
class Solver;

class SceneManager : public QObject
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = Q_NULLPTR);


    /* Plain Old Text Serialization */
    void read(QByteArray &bytes, bool *ok = 0);
    void write(QByteArray &bytes) const;

    /* Public Getters */
    Scene* scene() const { return m_scene; }

Q_SIGNALS:
    void changed();

public Q_SLOTS:
    virtual void clear();
  
private:
    Scene* m_scene;
    QSharedPointer<Solver> m_solver;
    Result m_result;

    void recalculate();
};

#endif // CORE_SCENEMANAGER_H
