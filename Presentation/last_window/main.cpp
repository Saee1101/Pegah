#include "MainWindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <Cutelyst/Application>

#include <Cutelyst/Server/server.h>
#include <QtConcurrent/QtConcurrent>


#include "APIController.h"

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Cutelyst::Server server;



    // Open HTTP/1.1 3000 port
    server.setHttpSocket({
                          {QStringLiteral(":3000")},
                          });

    // Allow HTTP/1.1 upgrade to HTTP2 at 3000 port
    server.setUpgradeH2c(true);

    // HTTP2 requires a larger buffer size
    server.setBufferSize(16393);

    // Open HTTP/2 at 3001 port
    server.setHttp2Socket({
                           {QStringLiteral(":3001")},
                           });

    // Open FastCGI 3002 port
    server.setFastcgiSocket({
                             {QStringLiteral(":3002")},
                             });

    server.exec(new APIController);

    return a.exec();
}
