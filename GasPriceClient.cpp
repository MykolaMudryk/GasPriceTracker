#include "GasPriceClient.h"

GasPriceClient::GasPriceClient(QObject *parent)
    : QObject(parent), networkManager(new QNetworkAccessManager(this)) {
  loadConfig();
}

void GasPriceClient::loadConfig() {
  QString configFilePath = qgetenv("CONFIG_PATH");

  if (configFilePath.isEmpty()) {
    qDebug() << "Змінна середовища CONFIG_PATH не задана.";
    return;
  }

  QSettings settings(configFilePath, QSettings::IniFormat);

  if (!settings.contains("API/Key") || !settings.contains("API/Secret")) {
    qDebug() << "Не вдалося знайти ключі в конфігурації.";
    qDebug() << "Current path:" << configFilePath;
  }

  m_apiKey = settings.value("API/Key").toString();
  m_apiSecret = settings.value("API/Secret").toString();
  qDebug() << "API Key:" << (m_apiKey.isEmpty() ? "Empty" : m_apiKey);
  qDebug() << "API Secret:" << (m_apiSecret.isEmpty() ? "Empty" : m_apiSecret);
}

QString GasPriceClient::gasPrice() const { return m_gasPrice; }

void GasPriceClient::fetchGasPrice() {
  QString url =
      "https://gas.api.infura.io/networks/1/suggestedGasFees";  // Ethereum
                                                                // Mainnet
  QNetworkRequest request((QUrl(url)));

  QString authString = QString("%1:%2").arg(m_apiKey, m_apiSecret);

  QByteArray encodedAuth = authString.toLocal8Bit().toBase64();
  request.setRawHeader("Authorization", "Basic " + encodedAuth);

  QNetworkReply *reply = networkManager->get(request);
  connect(reply, &QNetworkReply::finished, this,
          [=]() { onGasPriceFetched(reply); });
}

void GasPriceClient::onGasPriceFetched(QNetworkReply *reply) {
  if (reply->error() == QNetworkReply::NoError) {
    QByteArray response = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response);

    if (jsonResponse.isObject()) {
      QJsonObject jsonObject = jsonResponse.object();
      if (jsonObject.contains("estimatedBaseFee")) {
        QString estimatedBaseFee = jsonObject["estimatedBaseFee"].toString();
        qDebug() << "Estimated Base Fee:" << estimatedBaseFee;

        m_gasPrice = estimatedBaseFee;
        emit gasPriceChanged();
      } else {
        qDebug() << "Key 'estimatedBaseFee' not found in response.";
      }
    } else {
      qDebug() << "Response is not a valid JSON object.";
    }
  } else {
    qDebug() << "Server responded with error:" << reply->errorString();
  }
  reply->deleteLater();
}
