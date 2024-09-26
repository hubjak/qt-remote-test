#include <QCoreApplication>
#include <QtRemoteObjects/QtRemoteObjects>
#include <iostream>
#include <thread>
#include <chrono>
#include "rep_serverobject_source.h"

void updateValueInThread(ServerObjectSimpleSource* serverObject)
{
    int value = 0;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Sleep for 1 second

        ++value;
        // Use QMetaObject::invokeMethod to call setServerValue in the main thread
        QMetaObject::invokeMethod(serverObject, [serverObject, value]() {
            serverObject->setServerValue(value);
            std::cout << "Server updated value to: " << value << std::endl;
        }, Qt::QueuedConnection);  // Ensure the call is queued for execution in the main thread
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Create the server object that will be shared
    ServerObjectSimpleSource serverObject;

    // Host the server object on the network
    QRemoteObjectHost host(QUrl(QStringLiteral("tcp://localhost:12345")));
    host.enableRemoting(&serverObject);

    // Start a separate thread for updating the value periodically
    std::thread updateThread(updateValueInThread, &serverObject);

    // Detach the thread so it runs independently
    updateThread.detach();

    return app.exec();
}
