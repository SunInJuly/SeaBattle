#include "humanPlayer.h"

HumanPlayer::HumanPlayer(const QSharedPointer<GameField>& plrField,
                         const QSharedPointer<GameField>& enmField,
                         const QSharedPointer<FieldView>& _plrFieldView,
                         const QSharedPointer<FieldView>& _enmFieldView,
                         QObject* parent):
    Player(plrField, enmField, parent),
    plrFieldView(_plrFieldView),
    enmFieldView(_enmFieldView),
    fleetInst(NULL)
{
    connect(enmFieldView.data(), SIGNAL(attack(int)), this, SLOT(cellWasAttacked(int)));
}

void HumanPlayer::installFleet(const QSharedPointer<FleetInstaller> &fleetInstaller)
{
    fleetInst = fleetInstaller;
    setFleetHealth(fleetInst->getFleet());
    connect(plrFieldView.data(), SIGNAL(placeShip(int,int)), fleetInst.data(), SLOT(shipPlaced(int,int)));
    connect(plrFieldView.data(), SIGNAL(deleteShip(int)), fleetInst.data(), SLOT(deleteShip(int)));
    connect(fleetInst.data(), SIGNAL(fleetInstalled()), this, SLOT(reEmitFleetInstalled()));
    /*
    connect(fleetInstaller, SIGNAL(shipPlacedSuccesfully(NameOfShips, int))
            , view, SLOT(changeCounter(NameOfShips,int)));
    */

}

void HumanPlayer::turn()
{

}

void HumanPlayer::cellWasAttacked(int id)
{
    attack(id);
}

void HumanPlayer::reEmitFleetInstalled()
{
    emit fleetInstalled(this);
}
