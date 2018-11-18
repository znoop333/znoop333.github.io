var http        = require('http');
var express		= require('express');
var fs			= require('fs');
var io			= require('socket.io');
var crypto		= require('crypto');

var app       	= express();
var staticDir 	= express.static;
var server    	= http.createServer(app);

var brown = '\033[33m',
	green = '\033[32m',
	reset = '\033[0m';

io = io(server);

// Returns a random integer between min (included) and max (included)
// Using Math.round() will give you a non-uniform distribution!
function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

var opts = {
	port: process.env.PORT || 1948,
	baseDir : __dirname + '/../../'
};

io.on( 'connection', function( socket ) {
	socket.on('subscribe', function(data) { socket.join(data.room); })
	socket.on('unsubscribe', function(data) { socket.leave(data.room); })

	socket.on('vote', function(data) {
		socket.broadcast.to('voting').emit('newvote', data);
		console.log( 'vote data: ' + data.client_id + ', ' + data.poll_id );
	});

	socket.on('multiplex-statechanged', function(data) {

		if (typeof data.secret == 'undefined' || data.secret == null || data.secret === '') return;
		if (createHash(data.secret) === data.socketId) {
			data.secret = null;
			socket.broadcast.emit(data.socketId, data);
		};

	});

	socket.on('ChooseWinner', function(data) {
		console.log( 'ChooseWinner for prize id: ' + data.id );
        var room = io.nsps['/'].adapter.rooms['prizes'];
        var nSock = Object.keys(room).length;
		console.log( nSock + ' sockets in room : ' + room );

		var winnerFound=false;
		for( var attempt = 0; attempt < 100 && !winnerFound; attempt++ )
		{
        	var winner = getRandomIntInclusive(1, nSock);
	
        	var sid, val, i = 1;
			for(sid in room)
			{
				if( i == winner && !(sid in data.previousWinners) ) {
					console.log( 'WINNER! Socket ' + i + ' is ' + sid );
					io.emit('WinnerChosen', {id: data.id, nSock: nSock, winner: winner, SID: sid, attempts: attempt});
					winnerFound = true;
				} else if( i == winner ) {
					console.log( 'Socket ' + i + ' is ' + sid + ', not a winner because you won prize id ' + data.previousWinners[sid] + ' before. Attempting again' );
				} else {
					console.log( 'Socket ' + i + ' is ' + sid + ', not a winner.' );
				}
				i++;
			}
		}

		if(!winnerFound)
		{
			console.log( 'Nobody won prize id ' + data.id + ' after ' + attempt + ' attempts! How did that happen?!' );
            socket.emit('NoWinnerChosen', {id: data.id, nSock: nSock, winner: '', SID: '', attempts: attempt});
		}
    });

	socket.on('NewPoll', function(data) {
		console.log( 'NewPoll: ' + data.socketId + ', ' + data.secret + ', ' + createHash(data.secret) );

		//socket.broadcast.emit(data.socketId, data);
		io.emit('NewPoll1', data);
	});

	var clientIp = socket.request.connection.remoteAddress;
	console.log(clientIp);

	socket.emit('welcome', {yourIP: clientIp, yourSID: socket.id});

	socket.on('data', function(data) {
		data.client_id = clientIp + ' ' + socket.id;
		io.to('results').emit('newdata', data);
		console.log( 'data: ' + data.client_id + ', ' + data.poll_id );
	});


	console.log( brown + "client connected:" + socket.id + reset + ' on ' + clientIp );
});

[ 'css', 'js', 'plugin', 'lib', 'img', 'echo' ].forEach(function(dir) {
	app.use('/' + dir, staticDir(opts.baseDir + dir));
});

app.get("/:master", function(req, res) {
	res.writeHead(200, {'Content-Type': 'text/html'});
	// req.params.master should be 'master' or 'client' for master or client, respectively

	var stream = fs.createReadStream(opts.baseDir + '/jeepws.html');
	stream.on('error', function( error ) {
		res.write('<style>body{font-family: sans-serif;}</style><h2>reveal.js multiplex server.</h2><a href="/token">Generate token</a>');
		res.end();
	});
	stream.on('readable', function() {
		stream.pipe(res);
	});
});

app.get("/token", function(req,res) {
	var ts = new Date().getTime();
	var rand = Math.floor(Math.random()*9999999);
	var secret = ts.toString() + rand.toString();
	res.send({secret: secret, socketId: createHash(secret)});
});

var createHash = function(secret) {
	var cipher = crypto.createCipher('blowfish', secret);
	return(cipher.final('hex'));
};

// Actually listen
server.listen( opts.port || null );


console.log( brown + "reveal.js:" + reset + " Multiplex running on port " + green + opts.port + reset );
