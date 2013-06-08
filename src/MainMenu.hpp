/* Copyright (c) 2012 Research In Motion Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef MainMenu_H
#define MainMenu_H

#include <bb/cascades/QmlDocument>
#include <QtCore/QObject>
#include <bb/cascades/Control>
#include <bb/cascades/Container>
#include <bb/cascades/AbstractPane>
#include <bb/system/InvokeManager.hpp>
#include <bb/system/SystemDialog.hpp>


#include "NfcManager.hpp"

using namespace bb::cascades;

class MainMenu : public QObject
{
    Q_OBJECT

public:
    MainMenu(Application *app);
    virtual ~MainMenu();
    // This is our constructor that sets up the recipe.
//        StarshipSettingsApp();
//        ~StarshipSettingsApp();

        /* Invokable functions that we can call from QML*/

        /**
         * This Invokable function gets a value from the QSettings,
         * if that value does not exist in the QSettings database, the default value is returned.
         *
         * @param objectName Index path to the item
         * @param defaultValue Used to create the data in the database when adding
         * @return If the objectName exists, the value of the QSettings object is returned.
         *         If the objectName doesn't exist, the default value is returned.
         */
        Q_INVOKABLE
        QString getValueFor(const QString &objectName, const QString &defaultValue);

        /**
         * This function sets a value in the QSettings database. This function should to be called
         * when a data value has been updated from QML
         *
         * @param objectName Index path to the item
         * @param inputValue new value to the QSettings database
         */
        Q_INVOKABLE
        void saveValueFor(const QString &objectName, const QString &inputValue);

private:
    EventLog* _eventLog;
    NfcManager* _nfcManager;

	bb::system::SystemDialog *_systemDialog;

    QString _appVersion;

    void startEventProcessing();
    void createModules();
    void connectSignals();
    void deleteModules();

    QmlDocument *_qml;
	AbstractPane *_root;
    void findAndConnectControls();

    Application *_app;
    bb::system::InvokeManager * _invokeManager;

signals:
    void emulate_echo_selected();

public slots:
	void onMainMenuTriggered();
	void onButtonClicked(bool);
	//void onListSelectionChanged(const QVariantList indexPath);
	void menuShowing();
	void cleanUpOnExit();

private slots:
	void emulateEcho();
};

#endif // ifndef MainMenu_H
