import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Rectangle {
    id: mapRectangle

//    property pathToShow: pathProvider.createObject()
//
//    property Component pathProvider:
//
//    function addToPath(coordinate) {
//        pathToShow.addCoordinate(coordinate)
//    }
//
//    function showPath() {
//        mapView.addMapItem(pathToShow)
//    }
//
//    function clearMapItems() {
//        mapView.clearMapItems()
//    }
//
//    function clearMapPath() {
//        mapView.clearMapItems()
//        pathToShow.setPath([])
//    }

    Plugin {
        id: mapPlugin
        name: "osm"
    }
    Map {
        id: mapView
        anchors.fill: parent
        plugin: mapPlugin
        center: data_out.gnssPosition
        //center: QtPositioning.coordinate( );
        //48.71250170132551, 2.2163675687909805
        //{ latitude: 48.71250170132551, longitude:  2.2163675687909805 }
        zoomLevel: 12

        MapPolyline {
            line.width: 4
            line.color: 'blue'
            path: data_out.path
        }

    }

//    Connections {
//        target: data_out
//        function onGnssPositionChanged() {
//
//        }
//    }

}
