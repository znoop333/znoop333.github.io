(function() {

	// Don't emit events from inside of notes windows
	if ( window.location.search.match( /receiver/gi ) ) { return; }

	var multiplex = Reveal.getConfig().multiplex;

	var socket = io.connect( multiplex.url );

	socket.emit("subscribe", { room: "voting" });
	socket.emit("subscribe", { room: "results" });
	socket.emit("subscribe", { room: "prizes" });

	socket.on('welcome', function(data) {
        $('#clientIp').html(data.yourIP);
        $('#clientSID').html(data.yourSID);
        $('#robotimg').attr('src', 'https://robohash.org/' + data.yourSID);
    });    

// Returns a random integer between min (included) and max (included)
// Using Math.round() will give you a non-uniform distribution!
function getRandomIntInclusive(min, max) {
  min = Math.ceil(min);
  max = Math.floor(max);
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

	// remember who won so they don't get additional prizes
	// keys: winner SID, values: prize IDs
	var previousWinners = {};
	var lastPrizeID = 0;

    function ChooseWinner() {
        var id = lastPrizeID + 1;
        socket.emit("ChooseWinner", { id: id, previousWinners: previousWinners });
        $('#currentPrizeId').html(id);
	}

    function Reset() {
        previousWinners = {};
        lastPrizeID = 0;
	}

    // only the master should have a button to click to choose a winner
    $('#ChooseWinner_Button').show();
    $('#ChooseWinner_Button').click( function() { ChooseWinner();  } );
    $('#Reset_Button').show();
    $('#Reset_Button').click( function() { Reset();  } );

	socket.on('WinnerChosen', function(data) {
        $('#currentPrizeId').html(data.id);
        $('#winnerSID').html(data.SID);
        $('#HistoryOutcomes').append('<p>For prize ' + data.id + ', the winner was: ' + data.SID + '</p>');
        $('#WinnerRobotImg').attr('src', 'https://robohash.org/' + data.SID);

		lastPrizeID = data.id;
		previousWinners[data.SID] = data.id;

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

	function post() {

		var messageData = {
			state: Reveal.getState(),
			secret: multiplex.secret,
			socketId: multiplex.id
		};

		socket.emit( 'multiplex-statechanged', messageData );

	};

	// Monitor events that trigger a change in state
	Reveal.addEventListener( 'slidechanged', post );
	Reveal.addEventListener( 'fragmentshown', post );
	Reveal.addEventListener( 'fragmenthidden', post );
	Reveal.addEventListener( 'overviewhidden', post );
	Reveal.addEventListener( 'overviewshown', post );
	Reveal.addEventListener( 'paused', post );
	Reveal.addEventListener( 'resumed', post );

	socket.on('NewPoll1', function(data) {
		console.log('master-' + data);
	});

	socket.on('newdata', function(data) {
		Vote.SaveResult(data);
		console.log('newdata-' + data);
	});


	function examplePoll() {
		return {
		    title: "should VIM be upgraded?"
			,poll_id: 4503
			,multiselect: false
			,options: 
			[{
			    idx: 1
			    ,display: "Yes"
			    ,type: "radio"
			}
			,{
			    idx: 2
			    ,display: "No"
			    ,type: "radio"
			}]
		    }; 
	}

	function DoExamplePoll() {
		var messageData = {
			state: examplePoll(),
			secret: multiplex.secret,
			socketId: multiplex.id
		};

		socket.emit( 'NewPoll', messageData );

		console.log('DoExamplePoll: ' + messageData);
	}

	var Multiplex = {
		socket: function () { return socket; },
		mx: function () { return multiplex; },
		post: post,
		DoExamplePoll: DoExamplePoll,
	};

	window.Multiplex = Multiplex;
	return Multiplex;
}());
