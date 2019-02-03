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

#include "propertiesdialog.h"
#include "ui_propertiesdialog.h"

#include <Core/SceneManager>

PropertiesDialog::PropertiesDialog(SceneManager *sceneManager, QWidget *parent) : QDialog(parent)
  , ui(new Ui::PropertiesDialog)
  , m_sceneManager(sceneManager)
{
    ui->setupUi(this);

    Q_ASSERT(m_sceneManager);
    ui->titleLineEdit->setText(m_sceneManager->title());
    ui->authorLineEdit->setText(m_sceneManager->author());
    ui->dateLineEdit->setText(m_sceneManager->date());
    ui->descriptionTextEdit->setPlainText(m_sceneManager->description());
}

PropertiesDialog::~PropertiesDialog()
{
    delete ui;
}

void PropertiesDialog::accept()
{
    Q_ASSERT(m_sceneManager);
    if (m_sceneManager->title() != ui->titleLineEdit->text()) {
        m_sceneManager->setTitle(ui->titleLineEdit->text());
    }
    if (m_sceneManager->author() != ui->authorLineEdit->text()) {
        m_sceneManager->setAuthor(ui->authorLineEdit->text());
    }
    if (m_sceneManager->date() != ui->dateLineEdit->text()) {
        m_sceneManager->setDate(ui->dateLineEdit->text());
    }
    if (m_sceneManager->description() != ui->descriptionTextEdit->toPlainText()) {
        m_sceneManager->setDescription(ui->descriptionTextEdit->toPlainText());
    }

    QDialog::accept();
}
