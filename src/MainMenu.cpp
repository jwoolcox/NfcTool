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
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/ListView>
#include <bb/cascades/controls/imagetogglebutton.h>
#include <bb/cascades/controls/button.h>
#include <bb/cascades/Page>
#include <cstdlib>

#include "MainMenu.hpp"
#include "Settings.hpp"
#include "StateManager.hpp"
#include "Navigator.hpp"

using namespace bb::cascades;

MainMenu::MainMenu(Application *app) :
		_nfcManager(0), _appVersion(QString(Settings::AppVersion)) {

	_app = app;
	_qml = QmlDocument::create("asset:///main.qml");
	_qml->setContextProperty("_mainMenu", this);
	_root = _qml->createRootObject<AbstractPane>();
	StateManager* state_mgr = StateManager::getInstance();
	_qml->setContextProperty("_stateManager", state_mgr);

	_invokeManager = new bb::system::InvokeManager();
	Navigator* nav = Navigator::getInstance();
	NavigationPane* navpane = dynamic_cast<NavigationPane*>(_root);
	nav->setNavigationPane(navpane);

	_systemDialog = new bb::system::SystemDialog(this);
	_systemDialog->setTitle("NFC Transaction");
	bb::system::SystemUiButton *confirmButton = _systemDialog->confirmButton();
	confirmButton->setLabel("OK");

	createModules();
	startEventProcessing();
	qDebug() << "XXXX calling connectSignals";
	connectSignals();
	qDebug() << "XXXX done calling connectSignals";
	onMainMenuTriggered();

}

MainMenu::~MainMenu() {
	qDebug() << "XXXX MainMenu destructor";
	deleteModules();
}

void MainMenu::startEventProcessing() {
	_nfcManager = NfcManager::getInstance();
	_nfcManager->startEventProcessing();
}

void MainMenu::deleteModules() {
	qDebug() << "XXXX deleting instances of all other modules...";
	if (_eventLog) {
		delete _eventLog;
		_eventLog = 0;
	}
	if (_nfcManager) {
		delete _nfcManager;
		_nfcManager = 0;
	}
	qDebug() << "XXXX ...done";
}

void MainMenu::createModules() {
	qDebug() << "XXXX creating instances of all other modules...";
	_eventLog = EventLog::getInstance();
	qDebug() << "XXXX ...done";
}

void MainMenu::connectSignals() {
	Navigator* nav = Navigator::getInstance();
	NavigationPane* navpane = nav->getNavigationPane();
	QObject::connect(navpane, SIGNAL(menuShowing()), this, SLOT(menuShowing()));
	QObject::connect(_invokeManager,
			SIGNAL(invoked(const bb::system::InvokeRequest&)), this,
			SLOT(receivedInvokeRequest(const bb::system::InvokeRequest&)));
	QObject::connect(this, SIGNAL(launchEventLog()), _eventLog, SLOT(show()));
}

void MainMenu::findAndConnectControls() {

	ImageToggleButton *activatebutton = _root->findChild<ImageToggleButton*>(
			"imgtgbtn");
	QObject::connect(activatebutton, SIGNAL(checkedChanged(bool)), this,
			SLOT(onButtonClicked(bool)));

	QObject::connect(this, SIGNAL(emulate_echo_selected()), this,
			SLOT(emulateEcho()));
}

void MainMenu::onButtonClicked(bool checked) {
	if (checked) { //button state is on
		emit emulate_echo_selected();
	} else {
		StateManager* state_mgr = StateManager::getInstance();
		state_mgr->setDefaultState();
		_nfcManager = NfcManager::getInstance();
		_nfcManager->resetWorker();
	}
}

void MainMenu::onMainMenuTriggered() {
	qDebug() << "XXXX onMainMenuTriggered()";

	qDebug() << "XXXX setting scene to main menu";
	_app->setScene(_root);

	findAndConnectControls();
}

void MainMenu::menuShowing() {
	qDebug() << "XXXX menuShowing()";
	StateManager* state_mgr = StateManager::getInstance();
	state_mgr->setDefaultState();
	_nfcManager = NfcManager::getInstance();
	_nfcManager->resetWorker();
}

void MainMenu::cleanUpOnExit() {
	qDebug() << "XXXX Clean up on application exit";
}

void MainMenu::emulateEcho() {
	qDebug() << "XXXX MainMenu:emulateEcho() start";
	//_eventLog->show();
	//StateManager* state_mgr = StateManager::getInstance();
	//state_mgr->setEventLogShowing(true);
	_nfcManager->startEchoEmulation();
	qDebug() << "XXXX MainMenu:emulateEcho() end";
}
