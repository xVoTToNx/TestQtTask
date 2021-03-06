#ifndef PROJECTINFOSCREEN_H
#define PROJECTINFOSCREEN_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QListWidget>

#include "network_protocol.h"

class MainWindow;

class ProjectInfoScreen : public QWidget
{
    Q_OBJECT

    NetworkProtocol* network_protocol;
    bool isProjectProcessing;

    MainWindow* main_window;

    QLabel* active_label;
    QLabel* name_label;
    QLabel* add_me_as_watcher_label;
    QLabel* project_icon_label;
    QLineEdit* project_name_edit;
    QPushButton* project_name_button;
    QCheckBox* active_button;
    QCheckBox* add_me_as_watcher_button;
    QGridLayout* project_info_layout;

public:
    ProjectInfoScreen(MainWindow* main_window, NetworkProtocol* network_protocol);
    void ShowMe(QJsonObject& project_info);

private slots:
    void onProjectNameButtonClicked();
};


#endif // PROJECTINFOSCREEN_H
