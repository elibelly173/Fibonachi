cordova.define('cordova/plugin_list', function(require, exports, module) {
module.exports = [
    {
        "file": "plugins/cordova-plugin-vibration/www/vibration.js",
        "id": "cordova-plugin-vibration.notification",
        "pluginId": "cordova-plugin-vibration",
        "merges": [
            "navigator.notification",
            "navigator"
        ]
    },
    {
        "file": "plugins/cordova-plugin-device/www/device.js",
        "id": "cordova-plugin-device.device",
        "pluginId": "cordova-plugin-device",
        "clobbers": [
            "device"
        ]
    },
    {
        "file": "plugins/jaeger.Html5Video/www/Html5Video.js",
        "id": "jaeger.Html5Video.Html5Video",
        "pluginId": "jaeger.Html5Video",
        "clobbers": [
            "plugins.html5Video"
        ]
    }
];
module.exports.metadata = 
// TOP OF METADATA
{
    "cordova-plugin-vibration": "2.1.2",
    "cordova-plugin-device": "1.1.2",
    "jaeger.Html5Video": "1.2.2"
}
// BOTTOM OF METADATA
});