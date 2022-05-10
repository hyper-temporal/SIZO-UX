# OXI-client
a set of gui components created to ultimately integrate audio workflows
Every components can be created from QML (so js is also available and should be considered)
TODO: 
- allow user to CRUD UI states using json
- allow user to adapt pianoroll and graph to it's own pipeline (graph and event based)
- add the real time thread safe mecanism to update and report UI

Components are written in C++ and derives from QQuickPaintedItem
Big object like GraphEditor and PianoRoll using QGraphics stuffs so very efficient 
Draw functionnalities include zooming and edit graph connections, add remove events

- tree view is used to show a json structure with , well tree view style
- graph editor (edit connections, zoom in and out) 
- piano roll (zoom, events edition)
- fader horizontal or vertical
- rotary knobs with 
- simple action trigger etc


install qt >= 5 + CMake >= 3 (should come with the first)
then build and run :)
