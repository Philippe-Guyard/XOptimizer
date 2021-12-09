import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6
Rectangle {
    Plugin {
        id: mapPlugin
        name: "osm"
    }
    Map {
    id: mapView
    anchors.fill: parent
    plugin: mapPlugin
    center: QtPositioning.coordinate(48.7133, 2.2105);
    //center: QtPositioning.coordinate( );
    //48.71250170132551, 2.2163675687909805
    //{ latitude: 48.71250170132551, longitude:  2.2163675687909805 }
    zoomLevel: 16
    MapPolyline {
        line.width: 4
        line.color: 'blue'
        path: [
            { latitude: 48.71252662171624,longitude:  2.216211108304493 },
            { latitude: 48.712845188636074,longitude: 2.21278860962126 },
             { latitude:48.71455833614268, longitude:  2.212852982636907},
            { latitude: 48.71472823188787, longitude:  2.2098381797195574 },
            { latitude: 48.71382374153752,longitude:  2.2016154192405604 }
        ]
    }
    }

}


