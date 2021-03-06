#ifndef QMLSTARTMENU_H
#define QMLSTARTMENU_H

#include <QQmlEngine>
#include <QSharedPointer>

#include <QQuickItem>

#include "InterfaceStartMenu.h"
#include "qmlWidgetAppender.h"
#include "qmlRootWidget.h"

class QmlStartMenu : public InterfaceStartMenu, public QmlRootWidget
{
	Q_OBJECT
public:
	QmlStartMenu(QObject* widget);

	void show();
	void hide();
signals:
	void buttonVsPlayerPushed();
	void buttonVsPcPushed();
	void buttonExitPushed();
	void buttonSettingsPushed();
private slots:
	void slo();

private:
	// QQuickItem - это сам объект, созданный из qml файла
	QObject* mStartMenu;
	// эта штука для добавления элементов на окно
	QSharedPointer<QmlWidgetAppender> mWidgetAppender;
};

#endif // QMLSTARTMENU_H
