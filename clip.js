var WebSocket = require('ws');
var clipboard = require('copypaste');
var websocket = new WebSocket('wss://stream.pushbullet.com/websocket/APIKEY');
process.on('uncaughtException', function (e) {
	console.error("api key related error");
	process.exit(1);
});
websocket.onmessage = function (e) {
	var chunk = JSON.parse(e.data);
	if (chunk.type == 'push') {
		if (chunk.push.type == 'clip') {
			if (chunk.push.source_device_iden != 'kdeDesktop') {
				clipboard.copy(chunk.push.body);
			}
		}
	}
}
