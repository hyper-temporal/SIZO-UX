QT          +=  core qml quick widgets
TARGET      =   DrDiag
TEMPLATE    =   lib
CONFIG      +=  c++20 qt warn_off exceptions


INCLUDEPATH +=\
../Models\


SOURCES += \
    treestyle.cpp \
    treevue.cpp \
    jeudetest.cpp \
    arrow.cpp \
    diagramscene.cpp \
    diagramtextitem.cpp \
    vuegraph.cpp \
    ondegraphpart.cpp \
    ondegraphselector.cpp \
    drgraphe.cpp \
    objectstore.cpp \
    dto/editable.cpp \
    dto/graphblockdata.cpp \
    dto/editinstrument.cpp \
    dto/editondine.cpp \
    drgraphcursor.cpp




HEADERS += \
    treestyle.h \
    treevue.h \
    jeudetest.h \
    drgraphscene.h \
    drgraphitempart.h \
    drgraphitemselector.h \
    drgraphlabel.h \
    drgraphconnection.h \
    drgraphe.h \
    drgraphview.h \
    objectstore.h \
    dto/genericdto.h \
    dto/editable.h \
    dto/graphblockdata.h \
    dto/editinstrument.h \
    dto/editarrangement.h \
    dto/editcigale.h \
    dto/editmotif.h \
    dto/editconffloo.h \
    dto/editconfgoo.h \
    dto/editondine.h \
    drgraphcursor.h

