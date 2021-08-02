import QtQml.Models 2.2
import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.3
import DrTools 1.0
import "."

Item {

    CtrlPotard{
        id : tcut
    }
    CtrlPotard{
        id : trange
    }
    CtrlEnveloppe{
        id: env
    }

    CtrlPotard{
        id : tmin
    }
    CtrlPotard{
        id : tmax
    }

}
