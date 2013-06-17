APP_NAME = NfcTool

CONFIG += qt warn_on cascades10
LIBS += -lnfc -lnfc_bps -lbbsystem -lQtNfcSubset 
QT += network
include(config.pri)
