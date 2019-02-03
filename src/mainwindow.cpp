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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "about.h"
#include "version.h"
#include "globals.h"

#include <Core/SceneManager>
#include <Dialogs/PropertiesDialog>
#include <Widgets/GraphicsView>
#include <Widgets/MainWidget>

#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QSettings>
#include <QtCore/QStandardPaths>
#include <QtCore/QUrl>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#ifdef QT_DEBUG
#  include <QtCore/QDebug>
#endif


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , m_sceneManager(new SceneManager(this))
  , m_dirty(false)
  , m_physicalFile(false)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,10);

    this->setWindowTitle(QString("%0 v%1").arg(STR_APPLICATION_NAME).arg(STR_APPLICATION_VERSION));
    this->setWindowIcon(QIcon(":/icons/logo/maps-pin-place.ico"));
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setAcceptDrops(true);

    ui->viewerWidget->setModel(m_sceneManager);

    QObject::connect(m_sceneManager, SIGNAL(changed()), this, SLOT(setDirty()));

    createActions();
    createMenus();


    // TEST
    m_sceneManager->clear();

    readSettings();

    newFile();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::newFile()
{
    if (maybeSave()) {
        m_physicalFile = false;
        m_currentFile = QFileInfo();
        m_currentFile.setFile(QStringLiteral("untitled.json"));
        m_sceneManager->clear();

        /* Settings */
        //ui->sceneToolBar->reset();

        this->setClean();
    }
}

bool MainWindow::isExampleFile() const
{
    return m_currentFile.filePath().startsWith(":/");
}

bool MainWindow::isPhysicalFile() const
{
    return m_physicalFile
            && m_currentFile.isFile()
            && !m_currentFile.isSymLink()
            && !isExampleFile();
}

bool MainWindow::save()
{
    if ( isPhysicalFile() ){
        return saveFile(m_currentFile.absoluteFilePath());
    } else {
        return saveAs();
    }
}

bool MainWindow::saveAs()
{
    QString filePath = askSaveFileName(QStringLiteral("Data File (*.json)"),
                                       tr("Data File"));
    if (filePath.isEmpty()) {
        return false;
    }
    return saveFile(filePath);
}

void MainWindow::open()
{
    if (maybeSave()) {
        QString filePath = askOpenFileName(tr("Data File (*.json);;All files (*.*)"));
        if (!filePath.isEmpty()) {
            if (loadFile(filePath)) {
                this->setClean();
            }
        }
    }
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::showFileProperties()
{
    PropertiesDialog dialog(m_sceneManager, this);
    dialog.exec();
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::about()
{
    QMessageBox msgBox(QMessageBox::NoIcon, tr("About Visibility Analysis"), aboutHtml());
    msgBox.exec();
}

/******************************************************************************
 ******************************************************************************/
bool MainWindow::maybeSave()
{
    if (m_dirty) {
        int ret = QMessageBox::warning(
                    this, tr("Unsaved changes"),
                    tr("The scene has not been saved.\n\n"
                       "Do you want to save your changes ?"),
                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (ret == QMessageBox::Save) {
            return save();
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

QString MainWindow::niceFileName() const
{
    if ( isPhysicalFile() ){
        return QDir::toNativeSeparators(m_currentFile.canonicalFilePath());
    }else{
        return m_currentFile.fileName();
    }
}

void MainWindow::setDirty()
{
    if (!m_dirty) {
        m_dirty = true;
        this->setWindowTitle( niceFileName() + QStringLiteral("* - Visibility Analysis"));
    }
}

void MainWindow::setClean()
{
    m_dirty = false;
    this->setWindowTitle( niceFileName() + QStringLiteral(" - Visibility Analysis "));
}


/******************************************************************************
 ******************************************************************************/
QString MainWindow::askSaveFileName(const QString &fileFilter, const QString &title)
{
    QString suggestedPath;
    if ( isPhysicalFile() ) {
        suggestedPath = m_currentFile.canonicalFilePath();
    }else{
        const QString dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
        suggestedPath = dir + QDir::separator() + m_currentFile.fileName();
        suggestedPath = QDir::toNativeSeparators(suggestedPath);
    }
    return QFileDialog::getSaveFileName(this, title, suggestedPath, fileFilter);
}

QString MainWindow::askOpenFileName(const QString &fileFilter, const QString &title)
{
    QString currentDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if ( isPhysicalFile() ){
        currentDir = m_currentFile.absolutePath();
    }
    return QFileDialog::getOpenFileName(this, title, currentDir, fileFilter);
}


/******************************************************************************
 ******************************************************************************/
void MainWindow::readSettings()
{
    QSettings settings;
    if ( !isMaximized() ) {
        this->move(settings.value("Position", QPoint(100, 100)).toPoint());
        this->resize(settings.value("Size", QSize(350, 350)).toSize());
    }
    this->setWindowState( (Qt::WindowStates)settings.value("WindowState", 0).toInt() );

}

void MainWindow::writeSettings()
{
    QSettings settings;

    if( !(isMaximized() | isFullScreen()) ) {
        settings.setValue("Position", this->pos());
        settings.setValue("Size", this->size());
    }
    settings.setValue("WindowState", (int)this->windowState()); // minimized, maximized, active, fullscreen...


    // --------------------------------------------------------------
    // Write also the current version of application in the settings,
    // because it might be used by 3rd-party update manager softwares like
    // FileHippo or Google Updater (aka gup).
    // --------------------------------------------------------------
    settings.setValue("Version", STR_APPLICATION_VERSION );
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::createActions()
{
    //! [0] File
    ui->action_New->setShortcuts(QKeySequence::New);
    ui->action_New->setStatusTip(tr("Create a new world"));
    connect(ui->action_New, SIGNAL(triggered()), this, SLOT(newFile()));

    ui->action_Open->setShortcuts(QKeySequence::Open);
    ui->action_Open->setStatusTip(tr("Open a world from a file"));
    connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(open()));

    ui->action_Save->setShortcuts(QKeySequence::Save);
    ui->action_Save->setStatusTip(tr("Save the world to current file"));
    connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));

    ui->action_SaveAs->setShortcuts(QKeySequence::SaveAs);
    ui->action_SaveAs->setStatusTip(tr("Save the world to a different file"));
    connect(ui->action_SaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

    // --
    ui->action_Properties->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F2));
    ui->action_Properties->setStatusTip(tr("Show the properties of the current file"));
    connect(ui->action_Properties, SIGNAL(triggered()), this, SLOT(showFileProperties()));

    // --
    ui->action_Exit->setShortcuts(QKeySequence::Quit);
    ui->action_Exit->setStatusTip(tr("Quit Visibility Analysis"));
    connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));
    //! [0]

    //! [1] Edit
    //! [1]

    //! [2] Find
    //! [2]

    //! [3] View
    GraphicsView *graphicsView = ui->viewerWidget->getView();

    ui->action_ZoomFit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_0));
    ui->action_ZoomFit->setStatusTip(tr("Zoom Fit"));
    connect(ui->action_ZoomFit, SIGNAL(triggered()), graphicsView, SLOT(zoomFit()));

    ui->action_ZoomIn->setShortcuts(QKeySequence::ZoomIn);
    ui->action_ZoomIn->setStatusTip(tr("Zoom In"));
    connect(ui->action_ZoomIn, SIGNAL(triggered()), graphicsView, SLOT(zoomIn()));

    ui->action_ZoomOut->setShortcuts(QKeySequence::ZoomOut);
    ui->action_ZoomOut->setStatusTip(tr("Zoom Out"));
    connect(ui->action_ZoomOut, SIGNAL(triggered()), graphicsView, SLOT(zoomOut()));

    // --
    ui->action_Axes->setStatusTip(tr("Show Axes"));
    ui->action_Axes->setCheckable(true);
    ui->action_Axes->setChecked(false);
    //connect(ui->action_Axes, SIGNAL(toggled(bool)), m_option, SLOT(setAxesVisible(bool)));
    //connect(m_option, SIGNAL(axesVisibilityChanged(bool)), ui->action_Axes, SLOT(setChecked(bool)));

    ui->action_Grid->setStatusTip(tr("Show Grid"));
    ui->action_Grid->setCheckable(true);
    ui->action_Grid->setChecked(false);
    connect(ui->action_Grid, SIGNAL(toggled(bool)), graphicsView, SLOT(setGridVisible(bool)));
    //connect(ui->action_Grid, SIGNAL(toggled(bool)), m_option, SLOT(setGridVisible(bool)));
    //connect(m_option, SIGNAL(gridVisibilityChanged(bool)), ui->action_Grid, SLOT(setChecked(bool)));

    ui->action_Background->setStatusTip(tr("Show Background"));
    ui->action_Background->setCheckable(true);
    ui->action_Background->setChecked(false);
    //connect(ui->action_Background, SIGNAL(toggled(bool)), m_option, SLOT(setBackgroundVisible(bool)));
    //connect(m_option, SIGNAL(backgroundVisibilityChanged(bool)), ui->action_Background, SLOT(setChecked(bool)));
    //! [3]

    //! [4] Database
    //! [4]

    //! [5] Options
    //! [5]

    //! [6] Examples
    //! [6]

    //! [7] Help
    ui->action_About->setShortcuts(QKeySequence::HelpContents);
    ui->action_About->setStatusTip(tr("About %0").arg(STR_APPLICATION_NAME));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(about()));

    ui->action_AboutQt->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F1));
    ui->action_AboutQt->setStatusTip(tr("About Qt"));
    connect(ui->action_AboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    //! [7]
}

void MainWindow::createMenus()
{

}


/******************************************************************************
 ******************************************************************************/
bool MainWindow::saveFile(const QString &path)
{
    QDir::setCurrent(path);
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        QMessageBox::warning(this, tr("Cannot save file"),
                             tr("Cannot write to file %1:\n%2.")
                             .arg(path)
                             .arg(file.errorString()));
        return false;
    }

    QJsonObject json;
    m_sceneManager->write(json);
    QJsonDocument saveDoc(json);
    file.write( saveDoc.toJson() );

    m_physicalFile = true;
    m_currentFile.setFile(path);
    this->statusBar()->showMessage(tr("File saved"), 2000);
    this->setClean();
    return true;
}

/******************************************************************************
 ******************************************************************************/
bool MainWindow::loadFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open file.");
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(path)
                             .arg(file.errorString()));
        return false;
    }
    QByteArray saveData = file.readAll();
    QJsonParseError ok;
    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData, &ok) );

    if (ok.error != QJsonParseError::NoError) {
        qCritical("Couldn't parse JSON file.");
        QMessageBox::warning(this, tr("Error"),
                             tr("Cannot parse the JSON file:\n"
                                "%1\n\n"
                                "At character %2, %3.\n\n"
                                "Operation cancelled.")
                             .arg(path)
                             .arg(ok.offset)
                             .arg(ok.errorString()));
        return false;
    }

    m_sceneManager->read(loadDoc.object());
    m_physicalFile = true;
    m_currentFile = path;
    this->statusBar()->showMessage(tr("File loaded"), 5000);
    this->setClean();
    return true;
}

/******************************************************************************
 ******************************************************************************/
void MainWindow::on_action_SimpleDrawing_triggered()
{
    if (maybeSave()) {
        loadFile(":/examples/SimpleDrawing.json");
    }
}

