#ifndef AIPLAYERTEST_H
#define AIPLAYERTEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "../../src/aiPlayer.h"

class AIPlayerTest : public QObject
{
    Q_OBJECT
private slots:
    // test that ai can make turnes, and after turn turnMade() signal called one time.
    void turnTest()
    {
        AIPlayer player;
        QSignalSpy turnMadeSpy(&player, SIGNAL(turnMade(int)));
        player.turn();
        QCOMPARE(turnMadeSpy.count(), 1);
    }
};

#endif // AIPLAYERTEST_H
