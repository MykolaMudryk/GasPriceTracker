#ifndef GASPRICECLIENT_H
#define GASPRICECLIENT_H

#include <QByteArray>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QUrl>

class GasPriceClient : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString gasPrice READ gasPrice NOTIFY gasPriceChanged)

 public:
  explicit GasPriceClient(QObject *parent = nullptr);
  QString gasPrice() const;
  Q_INVOKABLE void fetchGasPrice();

 signals:
  void gasPriceChanged();

 private slots:
  void onGasPriceFetched(QNetworkReply *reply);

 private:
  QNetworkAccessManager *networkManager;

  void loadConfig();

  QString m_gasPrice;
  QString m_apiKey;
  QString m_apiSecret;
};

#endif  // GASPRICECLIENT_H
