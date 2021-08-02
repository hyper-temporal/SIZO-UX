cmake_minimum_required(VERSION 3.14)

project(OXI_CLIENT LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

include_directories(
    ../Models
    ../QtJson
    )

set(PROJECT_SOURCES
    arrow.cpp
    damodel.cpp
    damodel.h
    dataobject.cpp
    dataobject.h
    diagramscene.cpp
    diagramtextitem.cpp
    drenveloppe.cpp
    drenveloppe.h
    drfader.cpp
    drfader.h
    drgraphconnection.h
    drgraphcursor.cpp
    drgraphcursor.h
    drgraphe.cpp
    drgraphe.h
    drgraphitempart.h
    drgraphitemselector.h
    drgraphlabel.h
    drgraphscene.h
    drgraphview.h
    dronde.cpp
    dronde.h
    drpotard.cpp
    drpotard.h
    drshape.cpp
    drshape.h
    drvaleur.cpp
    drvaleur.h
    drxy.cpp
    drxy.h
    dsonde.cpp
    dsonde.h
    jeudetest.cpp
    jeudetest.h
    main.cpp
    objectstore.cpp
    objectstore.h
    ondegraphpart.cpp
    ondegraphselector.cpp
    ondestore.cpp
    ondestore.h
    QtNestedModel.pro
    ressources.qrc
    treestyle.cpp
    treestyle.h
    treevue.cpp
    treevue.h
    vuegraph.cpp
    Models/iomodel.cpp
    Models/iomodel.h
    Models/qtoutils.cpp
    Models/qtoutils.h
    Models/treeitem.cpp
    Models/treeitem.h
    Models/treemodel.cpp
    Models/treemodel.h

    dto/editable.cpp
    dto/editable.h
    dto/editarrangement.h
    dto/editcigale.h
    dto/editconffloo.h
    dto/editconfgoo.h
    dto/editinstrument.cpp
    dto/editinstrument.h
    dto/editmotif.h
    dto/editondine.cpp
    dto/editondine.h
    dto/genericdto.h
    dto/graphblockdata.cpp
    dto/graphblockdata.h

    PianoRoll/drgantt.cpp
    PianoRoll/drgantt.h
    PianoRoll/ganttdata.cpp
    PianoRoll/ganttdata.h
    PianoRoll/ganttmodel.cpp
    PianoRoll/ganttmodel.h


    js/Helpers.js

    QML/Controles/CtrlBouton.qml
    QML/Controles/CtrlCibleMidi.qml
    QML/Controles/CtrlCigale.qml
    QML/Controles/CtrlCompound.qml
    QML/Controles/CtrlConfigAudio.qml
    QML/Controles/CtrlConfigMIDI.qml
    QML/Controles/CtrlElementsCheck.qml
    QML/Controles/CtrlEnveloppe.qml
    QML/Controles/CtrlExciterBand.qml
    QML/Controles/CtrlFader.qml
    QML/Controles/CtrlFiltreMIDI.qml
    QML/Controles/CtrlFX.qml
    QML/Controles/CtrlGraph.qml
    QML/Controles/CtrlImpactSynth.qml
    QML/Controles/CtrlMotif.qml
    QML/Controles/CtrlMotifInterprete.qml
    QML/Controles/CtrlOperation.qml
    QML/Controles/CtrlOscillateur.qml
    QML/Controles/CtrlPianoRoll.qml
    QML/Controles/CtrlPointEvenement.qml
    QML/Controles/CtrlPotard.qml
    QML/Controles/CtrlResonnanceBand.qml
    QML/Controles/CtrlRoughness.qml
    QML/Controles/CtrlRoutageMIDI.qml
    QML/Controles/CtrlSample.qml
    QML/Controles/CtrlSequence.qml
    QML/Controles/CtrlShape.qml
    QML/Controles/CtrlWaveTable.qml
    QML/Controles/CxAudioOut.qml
    QML/Controles/CxConstantes.qml
    QML/Controles/CxEnveloppeAny.qml
    QML/Controles/CxHyperWave.qml
    QML/Controles/CxImpact.qml
    QML/Controles/CxMIDI.qml


    QML/ActionsDBs.qml
    QML/Arbre.qml
    QML/ArbreEnvironnment.qml
    QML/Composer.qml
    QML/Configuration.qml
    QML/CxAudioOut.qml
    QML/CxConstantes.qml
    QML/CxEnveloppeAny.qml
    QML/CxHyperWave.qml
    QML/CxImpact.qml
    QML/CxMIDI.qml
    QML/CxOperation.qml
    QML/DomaineDef.qml
    QML/EditEnveloppe.qml
    QML/EditeurArrangement.qml
    QML/EditeurCigale.qml
    QML/EditeurConfig.qml
    QML/EditeurListe.qml
    QML/EditeurMotif.qml
    QML/EditeurSequence.qml
    QML/JsonDialog.qml
    QML/JsonForm.qml
    QML/JsonListEditDelegate.qml
    QML/JsonListEditView.qml
    QML/JsonMenu.qml
    QML/JsonTreeView.qml
    QML/LaucherComponent.qml
    QML/LauncherDelegate.qml
    QML/LauncherList.qml
    QML/main.qml
    QML/MenuConfig.qml
    QML/MenuDBs.qml
    QML/MenuNewObject.qml
    QML/ScopeView.qml
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OXI_CLIENT
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(OXI_CLIENT SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(OXI_CLIENT
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(OXI_CLIENT
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(OXI_CLIENT
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::Widgets
  Qt${QT_VERSION_MAJOR}::Charts
  Qt${QT_VERSION_MAJOR}::Qml

  )


