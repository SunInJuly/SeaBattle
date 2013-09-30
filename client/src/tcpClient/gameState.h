#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "clientstate.h"

class GameState : public ClientState
{
    Q_OBJECT
public:
    explicit GameState(const QWeakPointer<Client>& _client, QObject *parent);
    
public slots:
    /**
      *
      */
    //void connect(const QString & hostName, quint16 port) throw(Protocol::AlreadyConnected);
    /**
      *
      */
    void abort();
    /**
      *
      */
    virtual void send(Protocol::RequestType type, const QByteArray& bytes)
        throw (Protocol::SendingForbidden, Protocol::RequestTypeForbidden);
protected:
    void handleRecievedRequest(Protocol::RequestType type, const QByteArray &bytes);
};


#endif // GAMESTATE_H
