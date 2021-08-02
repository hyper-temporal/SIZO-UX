import QtQuick 2.0
import "."
Item {

    CtrlCompound {
        id:formule
    }
    CtrlOscillateur{
        id:osc
    }
    CtrlPotard{
        id:fmin
    }
    CtrlPotard{
        id:fmax
    }
    CtrlPotard{
        id:rmin
    }
    CtrlPotard{
        id:rmax
    }
    CtrlRoughness{
        id: roughness
    }
}
