#ifndef QMLBATTLEWIDGET_H
#define QMLBATTLEWIDGET_H

#include "InterfaceBattleWidget.h"
#include <QQuickWindow>
#include <QQuickItem>
#include "qmlRootWidget.h"
#include "qmlWidgetAppender.h"
#include "types.h"
#include "qmlInfoTab.h"
#include "qmlChatAndStatus.h"
#include "qmlField.h"


class QmlBattleWidget : public InterfaceBattleWidget, public QmlRootWidget
{
	Q_OBJECT
public:
	QmlBattleWidget(QObject* widget);

	void showPlayerField();
	void showEnemyField();
	void showInfoTab();
	void setTime(int time);
	void hideTimer();
	void showCountersOfFleet();
	void setCountOfFleet(Players plr, int count);
	void clearItself();
	void showGameBreakDialog(const QString& message);
	void showQuitDialog();
	void switchToPlayerField();
	void switchToEnemyField();

	void show();
	void hide();

	QSharedPointer<InterfaceField> getPlayerFieldView();
	QSharedPointer<InterfaceField> getEnemyFieldView();
	QSharedPointer<InterfaceInfoTab> getInfoTabView();
	QSharedPointer<InterfaceChatAndStatus> getChatAndStatus();

signals:
	void buttonBackPressed();
	void gameBreakDialogOkPressed();
	void quitDialogOkPressed();
	void quitDialogCancelPressed();

public slots:
	void setMessage(QString text);
private slots:
	void handleDeleteShipMode(bool isActive);
	void delayedSwitchToPlayerField();
	void delayedSwitchToEnemyField();
private:
	QSharedPointer<QmlInfoTab> mInfoTab;
	QSharedPointer<QmlField> mPlrField;
	QSharedPointer<QmlField> mEnemyField;
	QSharedPointer<QmlChatAndStatus> mChatAndStatus;

	QObject* mBattleWidget;
	QSharedPointer<QmlWidgetAppender> mWidgetAppender;
	QObject *timer;
	QObject *dialog;
};

#endif // QMLBATTLEWIDGET_H
