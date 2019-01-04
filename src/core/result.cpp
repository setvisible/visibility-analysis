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

#include "result.h"

#include <QtCore/QtGlobal>
#include <QtCore/QString>

#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif
#ifdef QT_TESTLIB_LIB
#  include <QtTest/QTest>
#endif

Result::Result()
{
}

void Result::clear()
{
    m_segments.clear();
}

/******************************************************************************
 ******************************************************************************/
void Result::addSegment(const Segment &segment)
{
    m_segments.append(segment);
}

QList<Segment> Result::segments() const
{
    return m_segments;
}

/******************************************************************************
 ******************************************************************************/
bool Result::operator==(const Result &other) const
{
    /* Compare the segments */
    if ((*this).m_segments.count() != other.m_segments.count()) {
        return false;
    }
    {
        QList<Segment> list = other.m_segments;
        for (int i = 0; i < (*this).m_segments.count(); ++i) {
            const Segment &item = (*this).m_segments.at(i);
            if (!list.removeOne(item)) {
                return false;
            }
        }
        Q_ASSERT(list.count() == 0);
    }

    return true;
}

bool Result::operator!=(const Result &other) const
{
    return ((*this) == other) ? false : true;
}


/******************************************************************************
 ******************************************************************************/
#ifdef QT_TESTLIB_LIB
/// This function is used by QCOMPARE() to output verbose information in case of a test failure.
char *toString(const Result &result)
{
    // bring QTest::toString overloads into scope:
    using QTest::toString;


    // delegate char* handling to QTest::toString(QByteArray):
    return toString( QString("<Result has '%0' segments>")
                     .arg(result.segments().count()) );
}
#endif

#ifdef QT_DEBUG
/// Custom Types to a Stream
QDebug operator<<(QDebug dbg, const Result &result)
{
    dbg.nospace() << QString("Result (total: '%0' segments)")
                     .arg(result.segments().count());
    return dbg.maybeSpace();
}
#endif
