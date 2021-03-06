#include "qmlBattleWidget.h"
#include <QDebug>
#include <QTimer>


//i know, that this code very horrible, but...deadline and other problem make me to do this

QmlBattleWidget::QmlBattleWidget(QObject* widget) :
	mBattleWidget(widget),
	mChatAndStatus(new QmlChatAndStatus())
{
	timer = mBattleWidget->findChild<QObject*>("timer");
	connect(mBattleWidget, SIGNAL(buttonBackPressed()), this, SIGNAL(buttonBackPressed()));
	connect(mBattleWidget, SIGNAL(deleteMode(bool)), SLOT(handleDeleteShipMode(bool)));
	mInfoTab = QSharedPointer<QmlInfoTab>(new QmlInfoTab(mBattleWidget->findChild<QObject*>("mAutoButton")
													 ,mBattleWidget->findChild<QObject*>("mButtonReady")
													 ,mBattleWidget->findChild<QObject*>("mCountOfShip")));
	mPlrField = QSharedPointer<QmlField>(new QmlField(mBattleWidget->findChild<QObject*>("mPlrField")));
	mEnemyField = QSharedPointer<QmlField>(new QmlField(mBattleWidget->findChild<QObject*>("mEnemyField")));
	dialog = mBattleWidget->findChild<QObject*>("dialogs");
	connect(dialog, SIGNAL(gameBreakDialogOkPressed()), this, SIGNAL(gameBreakDialogOkPressed()));
	connect(dialog, SIGNAL(quitDialogOkPressed()), this, SIGNAL(quitDialogOkPressed()));
	connect(dialog, SIGNAL(quitDialogCancelPressed()), this, SIGNAL(quitDialogCancelPressed()));
}

void QmlBattleWidget::showPlayerField()
{
	// crashed here ...
	QObject* mField = mBattleWidget->findChild<QObject*>("mPlrField");
	qDebug() << mField;
	mField->setProperty("visible", true);
}

void QmlBattleWidget::showEnemyField()
{
	//to do, there we give command to start
	mBattleWidget->setProperty("isFight", true);
	mPlrField->setBattleMode(true);
	mEnemyField->setBattleMode(true);
}

void QmlBattleWidget::showInfoTab()
{
	//unused....
}

void QmlBattleWidget::setTime(int time)
{
	timer->setProperty("visible", true);
	timer->setProperty("currentTime", time);
}

void QmlBattleWidget::hideTimer()
{
	timer->setProperty("visible", false);
}

void QmlBattleWidget::showCountersOfFleet()
{
	//unused....
}

void QmlBattleWidget::setCountOfFleet(Players plr, int count)
{
	if (plr == YOU){
		mBattleWidget->setProperty("countOfPlr", count);
	}else{
		mBattleWidget->setProperty("countOfEnemy", count);
	}
}

void QmlBattleWidget::clearItself()
{
	//to do call in children
	mBattleWidget->setProperty("isFight", false);
	mInfoTab->clearItself();
	mPlrField->clearItself();
	mBattleWidget->setProperty("countOfEnemy", 10);
	mBattleWidget->setProperty("countOfPlr", 10);
	mEnemyField->clearItself();
	mPlrField->setBattleMode(false);
	mEnemyField->setBattleMode(false);
}
//property alias backButtonVisible: backButton.visible
//property alias breakDialogOkVisible: breakDialogOk.visible
//property alias okButtonVisible: okButton.visible
void QmlBattleWidget::showGameBreakDialog(const QString& message)
{
	dialog->setProperty("text", message);
	dialog->setProperty("visible", true);
	dialog->setProperty("backButtonVisible", false);
	dialog->setProperty("breakDialogOkVisible", true);
	dialog->setProperty("okButtonVisible", false);
}

void QmlBattleWidget::showQuitDialog()
{
	dialog->setProperty("text", "Вы уверены, что хотите выйти в главное меню?");
	dialog->setProperty("visible", true);
	dialog->setProperty("backButtonVisible", true);
	dialog->setProperty("breakDialogOkVisible", false);
	dialog->setProperty("okButtonVisible", true);
}

void QmlBattleWidget::switchToPlayerField()
{
	QTimer::singleShot(1000, this, SLOT(delayedSwitchToPlayerField()));
}

void QmlBattleWidget::delayedSwitchToPlayerField()
{
	QMetaObject::invokeMethod(mBattleWidget, "switchToPlayerField");
}

void QmlBattleWidget::switchToEnemyField()
{
	QTimer::singleShot(1000, this, SLOT(delayedSwitchToEnemyField()));
}

void QmlBattleWidget::delayedSwitchToEnemyField()
{
	QMetaObject::invokeMethod(mBattleWidget, "switchToEnemyField");
}

void QmlBattleWidget::show()
{
}

void QmlBattleWidget::hide()
{
}

QSharedPointer<InterfaceField> QmlBattleWidget::getPlayerFieldView()
{
	return mPlrField;
}

QSharedPointer<InterfaceField> QmlBattleWidget::getEnemyFieldView()
{
	return mEnemyField;
}

QSharedPointer<InterfaceInfoTab> QmlBattleWidget::getInfoTabView()
{
	return mInfoTab;
}

QSharedPointer<InterfaceChatAndStatus> QmlBattleWidget::getChatAndStatus()
{
	return mChatAndStatus;
}

void QmlBattleWidget::setMessage(QString text)
{
	//unused....
	Q_UNUSED(text)
}

void QmlBattleWidget::handleDeleteShipMode(bool isActive)
{
	mPlrField->setDeleteShipMode(isActive);
}

