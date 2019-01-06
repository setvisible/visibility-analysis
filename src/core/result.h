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

#ifndef CORE_RESULT_H
#define CORE_RESULT_H

#include <Core/Segment>
#include <QtCore/QList>

#include <QtCore/QMetaType>
#include <QtCore/QString>

QT_BEGIN_NAMESPACE
class QDebug;
QT_END_NAMESPACE

class Result
{
public:
    explicit Result();

    void clear();

    void addSegment(const Segment &segment);
    QList<Segment> segments() const;

    bool operator==(const Result &other) const;
    bool operator!=(const Result &other) const;


private:
    QList<Segment> m_segments;
};

#ifdef QT_TESTLIB_LIB
char *toString(const Result &result);
#endif

Q_DECLARE_METATYPE(Result)

#ifdef QT_DEBUG
QT_BEGIN_NAMESPACE
QDebug operator<<(QDebug dbg, const Result &result);
QT_END_NAMESPACE
#endif

#endif // CORE_RESULT_H
