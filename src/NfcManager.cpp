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
#include "NfcManager.hpp"
#include "NdefType.hpp"
//#include "Logger.hpp"
#include "NfcWorker.hpp"
//#include "Settings.hpp"

NfcManager* NfcManager::_instance;

NfcManager::NfcManager() :
		_workerInstance(0), _bpsThread(0), _future(0), _watcher(0) {
	qDebug() << "XXXX Constructing NfcManager";
	_workerInstance = NfcWorker::getInstance();
	QObject::connect(this, SIGNAL(resetWorkerState()), _workerInstance, SLOT(reset()), Qt::QueuedConnection);
	qDebug() << "XXXX Done constructing NfcManager";
}

NfcManager::~NfcManager() {
	qDebug() << "XXXX NcfManager destructor";

	_instance = 0;

	stopNfcWorker();

	if (_future) {
		qDebug() << "XXXX NcfManager deleting QtConcurrent";
		delete _future;
		_future = 0;
	}

	if (_watcher) {
		qDebug() << "XXXX NcfManager deleting Watcher";
		delete _watcher;
		_watcher = 0;
	}

	if (_workerInstance) {
		qDebug() << "XXXX NcfManager deleting Worker";
		delete _workerInstance;
		_workerInstance = 0;
	}
}

NfcManager* NfcManager::getInstance() {
	if (_instance == 0) {
		_instance = new NfcManager;
	}
	return _instance;
}

void NfcManager::startEventProcessing() {
	qDebug() << "XXXX starting event processing...";
	_future = new QFuture<void>;
	_watcher = new QFutureWatcher<void>;
	*_future = QtConcurrent::run(_workerInstance, &NfcWorker::startEventLoop);
	_watcher->setFuture(*_future);
	QObject::connect(_watcher, SIGNAL(finished()), this, SLOT(workerStopped()));
	QObject::connect(_workerInstance, SIGNAL(message(QVariant)), this, SLOT(message(QVariant)), Qt::QueuedConnection);
	QObject::connect(_workerInstance, SIGNAL(clearMessages()), this, SLOT(clearMessages()), Qt::QueuedConnection);
	qDebug() << "XXXX startEventProcessing - event loop started";
}

void NfcManager::stopNfcWorker() {
	qDebug() << "XXXX About to request NfcWorker to stop";
	if (_workerInstance)
		_workerInstance->interruptBpsWaitLoop(NfcWorker::TERMINATE);
}

void NfcManager::handleTagReadInvocation(QByteArray data) {
	qDebug() << "XXXX NfcManager::handleTagReadInvocation";
	_workerInstance->handleTagReadInvocation(data);
}

void NfcManager::startEchoEmulation() {

	_workerInstance = NfcWorker::getInstance();
	QObject::disconnect(this, SIGNAL(start_echo_emulation()), 0,0);
	QObject::connect(this, SIGNAL(start_echo_emulation()), _workerInstance, SLOT(emulateEcho()), Qt::QueuedConnection);
	emit start_echo_emulation();
}

void NfcManager::workerStopped() {
	qDebug() << "XXXX NfcManager::workerStopped entered";
//	Logger::getInstance()->log("INF", "Worker thread has stopped");
	emit nfcManagerStopped();
}

void NfcManager::resetWorker() {
	qDebug() << "XXXX NfcManager::resetWorker entered";
	emit resetWorkerState();
}
