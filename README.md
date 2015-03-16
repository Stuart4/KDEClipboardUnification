# KDEClipboardUnification
A demonstration application that shows how the clipboard of an Android phone and a KDE Desktop can be shared.
# How To Build

Clone the source
```
$ git clone https://github.com/Stuart4/KDEClipboardUnification.git
$ cd KDEClipboardUnification
```

Edit the source file clip.js and replace APIKEY on line
```
var websocket = new WebSocket('wss://stream.pushbullet.com/websocket/APIKEY');
```
with your Pushbullet API key from https://www.pushbullet.com/account

Edit the source file mainwindow.cpp and replace APIKEY on line
```
header.push_back("Authorization: Bearer APIKEY");
```
with your Pushbullet API key from https://www.pushbullet.com/account

```
$ qmake
$ make
$ ./Test
```
