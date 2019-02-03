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
class QJsonObject;
class QString;
QT_END_NAMESPACE

class Scene;
class Solver;

class SceneManager : public QObject
{
    Q_OBJECT
public:
    explicit SceneManager(QObject *parent = Q_NULLPTR);

    /* JSON Serialization */
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    /* Public Getters */
    QString title() const;
    QString author() const;
    QString date() const;
    QString description() const;

    Result result() const;

Q_SIGNALS:
    void changed();
    void resultsChanged();

public Q_SLOTS:
    virtual void clear();

    virtual void setTitle(const QString &title);
    virtual void setAuthor(const QString &author);
    virtual void setDate(const QString &date);
    virtual void setDescription(const QString &description);
  
private:
    QSharedPointer<Scene> m_scene;
    QSharedPointer<Solver> m_solver;
    Result m_result;

    void recalculate();
};

#endif // CORE_SCENEMANAGER_H
