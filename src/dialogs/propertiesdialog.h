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

#ifndef DIALOGS_PROPERTIES_DIALOG_H
#define DIALOGS_PROPERTIES_DIALOG_H

#include <QtWidgets/QDialog>

class SceneManager;

namespace Ui {
class PropertiesDialog;
}

class PropertiesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropertiesDialog(SceneManager *sceneManager, QWidget *parent = 0);
    ~PropertiesDialog();

public Q_SLOTS:
    virtual void accept() Q_DECL_OVERRIDE;

private:
    Ui::PropertiesDialog *ui;
    SceneManager *m_sceneManager;

};

#endif // DIALOGS_PROPERTIES_DIALOG_H
