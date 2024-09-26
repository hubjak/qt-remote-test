#include <QCoreApplication>
#include <QTimer>
#include <QtRemoteObjects/QtRemoteObjects>
#include <iostream>
#include "rep_serverobject_replica.h"  // Generated from the serverobject.rep file

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Create a remote object node to connect to the server
    QRemoteObjectNode node(QUrl(QStringLiteral("tcp://localhost:12345")));

    // Acquire the replica of the server object
    auto replica = node.acquire<ServerObjectReplica>();  // Generated replica class

    // Connect to the server object's valueChanged signal
    QObject::connect(replica, &ServerObjectReplica::serverValueChanged, [](int newValue) {
        std::cout << "Client received value: " << newValue << std::endl;
    });

    // Start the event loop
    return app.exec();
}
