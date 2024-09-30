import QtQuick 2.15
import QtQuick.Controls 2.15
import GasClient 1.0

// Не забудьте імпортувати ваш модуль
ApplicationWindow {
  visible: true
  width: 640
  height: 480

  Column {
    spacing: 20
    padding: 20

    Button {
      text: "Get Gas Price"
      onClicked: gasPriceClient.fetchGasPrice()
    }

    Text {
      text: "Current Gas Price: " + gasPriceClient.gasPrice
    }
  }
}
