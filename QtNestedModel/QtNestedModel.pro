TEMPLATE = app
TARGET = WaveSession
QT += core widgets charts qml quick
CONFIG +=   c++20 qt warn_off exceptions

INCLUDEPATH +=\
../Models\
../QtJson\

RESOURCES +=    \
    ressources.qrc

HEADERS += \
    Models/iomodel.h \
    Models/qtoutils.h \
    Models/treeitem.h \
    Models/treemodel.h \
    PianoRoll/drgantt.h \
    PianoRoll/ganttdata.h \
    PianoRoll/ganttmodel.h \
    customctrls.h \
    damodel.h \
    dataobject.h \
    drenveloppe.h \
    drfader.h \
    drgraphconnection.h \
    drgraphcursor.h \
    drgraphe.h \
    drgraphitempart.h \
    drgraphitemselector.h \
    drgraphlabel.h \
    drgraphscene.h \
    drgraphview.h \
    dronde.h \
    drpotard.h \
    drshape.h \
    drvaleur.h \
    drxy.h \
    dsonde.h \
    dto/editable.h \
    dto/editarrangement.h \
    dto/editcigale.h \
    dto/editconffloo.h \
    dto/editconfgoo.h \
    dto/editinstrument.h \
    dto/editmotif.h \
    dto/editondine.h \
    dto/genericdto.h \
    dto/graphblockdata.h \
    jeudetest.h \
    objectstore.h \
    ondestore.h \
    treestyle.h \
    treevue.h

SOURCES += \
    Models/iomodel.cpp \
    Models/qtoutils.cpp \
    Models/treeitem.cpp \
    Models/treemodel.cpp \
    PianoRoll/drgantt.cpp \
    PianoRoll/ganttdata.cpp \
    PianoRoll/ganttmodel.cpp \
    arrow.cpp \
    customctrls.cpp \
    damodel.cpp \
    dataobject.cpp \
    diagramscene.cpp \
    diagramtextitem.cpp \
    drenveloppe.cpp \
    drfader.cpp \
    drgraphcursor.cpp \
    drgraphe.cpp \
    dronde.cpp \
    drpotard.cpp \
    drshape.cpp \
    drvaleur.cpp \
    drxy.cpp \
    dsonde.cpp \
    dto/editable.cpp \
    dto/editinstrument.cpp \
    dto/editondine.cpp \
    dto/graphblockdata.cpp \
    jeudetest.cpp \
    main.cpp \
    objectstore.cpp \
    ondegraphpart.cpp \
    ondegraphselector.cpp \
    ondestore.cpp \
    treestyle.cpp \
    treevue.cpp \
    vuegraph.cpp



