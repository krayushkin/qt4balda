/*
 * Server.cpp
 *
 *  Created on: 17.09.2009
 *      Author: dmitry
 */

#include "Server.h"


 #include <QtGui>
 #include <QtNetwork>

 Server::Server()
 {
     tcpServer = new QTcpServer;
     if (!tcpServer->listen()) {
         return;
     }

     connect(tcpServer, SIGNAL(newConnection()), this, SLOT(onConnect()));
 }

 Server::~Server()
 {
   delete tcpServer;
 }

 void Server::onConnect()
 {
     QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
     connect(clientConnection, SIGNAL(disconnected()),
             clientConnection, SLOT(deleteLater()));

     clientConnection->disconnectFromHost();
 }
