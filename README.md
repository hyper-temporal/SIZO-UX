# SIZO-UX
a set of gui components created to ultimately integrate audio workflows
Every components can be created from QML (so js is also available and should be considered)

### what is cool
Components are written in C++ and derives from QQuickPaintedItem
Big object like GraphEditor and PianoRoll using QGraphics stuffs so very efficient. 
The QML accessibility is a cool feature to allow devs easily create UX and develop rich components using qt

Draw functionnalities include zooming and edit graph connections, add remove events
## Components
- tree view is used to show a json structure with , well tree view style
- graph editor (edit connections, zoom in and out) 
- piano roll (zoom, events edition)
- shape(1D)/enveloppe(2D) editors
- fader horizontal or vertical
- rotary knobs
- simple action trigger
- XY control .. and more


install qt >= 5 + CMake >= 3 (should come with the first)
then build and run :)


### TODO: 
- allow user to CRUD UI states using json
- allow user to adapt pianoroll and graph to it's own pipeline (graph and event based)
- add the real time thread safe mecanism to update and report UI


![graph & connections screenshot](https://github.com/camillebassuel/SIZO-UX/blob/main/graph.png
 "qgraphicscene from qml - small graph and connection - screenshot")

![main selecter screenshot](https://github.com/camillebassuel/SIZO-UX/blob/main/main_selecter.png "qgraphicscene from qml - main selecter screenshot")
