(function() {
	var multiplex = Reveal.getConfig().multiplex;
	var socketId = multiplex.id;

	var socket = io.connect(multiplex.url);

	socket.emit("subscribe", { room: "voting" });
	socket.emit("subscribe", { room: "results" });
	socket.emit("subscribe", { room: "prizes" });

	socket.on(multiplex.id, function(data) {
		// ignore data from sockets that aren't ours
		if (data.socketId !== socketId) { return; }
		if( window.location.host === 'localhost:1947' ) return;

		Reveal.setState(data.state);
	});

	socket.on('welcome', function(data) {
        $('#clientIp').html(data.yourIP);
        $('#clientSID').html(data.yourSID);
        $('#robotimg').attr('src', 'https://robohash.org/' + data.yourSID);
    });    

	socket.on('WinnerChosen', function(data) {
        $('#currentPrizeId').html(data.id);
        $('#winnerSID').html(data.SID);
        $('#HistoryOutcomes').append('<p>For prize ' + data.id + ', the winner was: ' + data.SID + '</p>');
        $('#WinnerRobotImg').attr('src', 'https://robohash.org/' + data.SID);

		if( $('#clientSID').html() == data.SID )
		{
				$('#Outcome').html('You won!');
				$('#Outcome').addClass('winner').removeClass('notWinner');
		}
		else
		{
				$('#Outcome').html('Sorry, you did not win.');
				$('#Outcome').addClass('notWinner').removeClass('winner');
		}
    });    

	socket.on('NoWinnerChosen', function(data) {
        $('#currentPrizeId').html(data.id);
        $('#HistoryOutcomes').append('<p>For prize ' + data.id + ', there was no winner! Reset the history?</p>');
        $('#WinnerRobotImg').attr('src', '');
    });    

	socket.on('PollResults', function(data) {
		console.log('PollResults-' + data);
	});

	socket.on('NewPoll1', function(data) {
		console.log('client-' + data);
	});

	var Multiplex = {
		socket: function () { return socket; },
		mx: function () { return multiplex; }
	};

	window.Multiplex = Multiplex;
	return Multiplex;
}());
