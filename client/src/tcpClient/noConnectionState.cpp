#include "client.h"
#include "stateCollection.h"
#include "noConnectionState.h"

const int NoConnectionState::connectionTimeout = 10 * 1000;

NoConnectionState::NoConnectionState(const QWeakPointer<Client> &_client, QObject *parent):
    ClientState(_client, parent)
{
    timer.setSingleShot(true);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(connectionTimeoutHandler()));
    QObject::connect(client.data(), SIGNAL(connectedWithServer()), this, SLOT(connectedHandler()));
}

void NoConnectionState::connect(const QString & hostName, quint16 port) throw(Protocol::AlreadyConnected)
{
    Q_UNUSED (hostName);

    socket->connectToHost(Protocol::ServerName, port);
    timer.start(connectionTimeout);
    moveIntoState(getStateCollection()->getWaitingForServerConnectionState());
}

void NoConnectionState::connectedHandler()
{
    timer.stop();
}

void NoConnectionState::connectionTimeoutHandler()
{
    client.toStrongRef()->abort();
    emit error(QString("Server response time elapsed"));
}

