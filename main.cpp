#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "GasPriceClient.h"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  GasPriceClient *gasPriceClient = new GasPriceClient();

  qmlRegisterType<GasPriceClient>("GasClient", 1, 0, "GasPriceClient");
  engine.rootContext()->setContextProperty("gasPriceClient", gasPriceClient);

  const QUrl url(QStringLiteral("qrc:/GasPriceTracker/Main.qml"));
  engine.load(url);

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
