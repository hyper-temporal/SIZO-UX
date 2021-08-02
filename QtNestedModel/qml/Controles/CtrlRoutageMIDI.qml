import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
/*

    std::string _methode;
    short _device,_type;
    short _ch;
    short _dt1;
    short _dt2;
*/
    ComboBox{
        id:methode
        model:OndeStore.getMethodes_bang()
    }
    ComboBox{
        id:device
        model:OndeStore.getMIDIDevices()
    }

}
