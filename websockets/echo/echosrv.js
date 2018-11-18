#!/usr/bin/env node
var WebSocketServer = require('websocket').server;
var http = require('http');
 
var server = http.createServer(function(request, response) {
    console.log(getTimestamp() + ' Received request for ' + request.url);
    response.writeHead(404);
    response.end();
});
server.listen(8080, function() {
    console.log(getTimestamp() + ' Server is listening on port 8080');
});
 
wsServer = new WebSocketServer({
    httpServer: server,
    // You should not use autoAcceptConnections for production 
    // applications, as it defeats all standard cross-origin protection 
    // facilities built into the protocol and the browser.  You should 
    // *always* verify the connection's origin and decide whether or not 
    // to accept it. 
    autoAcceptConnections: false
});
 
function originIsAllowed(origin) {
  // put logic here to detect whether the specified origin is allowed. 
  return true;
}

function sayItAgainUTF8(conn,txt,clientStr) {
	var s = getTimestamp() + ' Hey ' + clientStr + ', you said ' + txt + ' 10 seconds ago!';
	conn.sendUTF(s);
	console.log(s);
}
 
function sayItAgain(conn,data,clientStr) {
	conn.sendBytes(data);
}

function getTimestamp() {
    return (new Date() + '').replace(' GMT-0400 (Eastern Daylight Time)', '');
}

wsServer.on('request', function(request) {
    var clientString = request.remoteAddress.replace('::ffff:', '') + ':' + request.socket.remotePort;

    if (!originIsAllowed(request.origin)) {
      // Make sure we only accept requests from an allowed origin 
      request.reject();
      console.log(getTimestamp() + ' Connection from origin ' + request.origin + ' rejected.');
      return;
    }

    if(request.requestedProtocols.indexOf('echo-protocol') !== -1)
    {
        var connection = request.accept('echo-protocol', request.origin);
        console.log(getTimestamp() + ' Connection accepted from ' + clientString);
        connection.on('message', function(message) {
            if (message.type === 'utf8') {
                console.log(getTimestamp() + ' Received Message: ' + message.utf8Data + ' from ' + clientString);
                connection.sendUTF(message.utf8Data);
                setTimeout(function () { sayItAgainUTF8(connection, message.utf8Data, clientString); }, 10000);
            }
            else if (message.type === 'binary') {
                console.log(getTimestamp() + ' Received Binary Message of ' + message.binaryData.length + ' bytes from ' + clientString);
                connection.sendBytes(message.binaryData);
                setTimeout(function () {sayItAgain(connection, message.binaryData, clientString); }, 10000);
            }
        });
        connection.on('close', function(reasonCode, description) {
            console.log(getTimestamp() + ' Peer ' + connection.remoteAddress + ' disconnected.');
        });
    }
    else
    {
        var connection = request.reject(500, 'echo-protocol required!');
        console.log(getTimestamp() + ' Connection rejected!');
    }
});
