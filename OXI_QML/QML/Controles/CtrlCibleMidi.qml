import QtQuick 2.0
import QtQuick.Controls 2.2
Item {
    Row{
        ComboBox{
            id: device
            model:OndeStore.getMIDIDevices()
        }
        ComboBox{
            id: channel
            model:OndeStore.getMIDIChannels()
        }
    }
}
