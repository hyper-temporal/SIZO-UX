import QtQuick 2.7
import QtQuick.Controls 2.1
import DrTools 1.0

import "."
import "../../js/Helpers.js" as Hlp

Item
{
    TextInput{
        id: name
    }

    ListView{
        id: exciterBands
        model: ganttModelList
        delegate: CtrlExciterBand{
        }
    }
    ListView{
        id: resonnances
        height: parent.height
        model: ganttModelList
        delegate: CtrlResonnanceBand{
        }
    }
    Component.onCompleted: {
        Hlp.exposerObjet(OndeStore.getDBFxs())
    }

}
