/*
 * Server.h
 *
 *  Created on: 17.09.2009
 *      Author: dmitry
 */

#ifndef SERVER_H_
#define SERVER_H_


#include <QtGui>
#include <QtNetwork>

 class Server : public QObject
 {
     Q_OBJECT
 public:
     Server();
     ~Server();
 private slots:
 void onConnect();

 private:
     QTcpServer *tcpServer;
 };


 #endif /* SERVER_H_ */
