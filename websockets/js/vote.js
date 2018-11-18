(function( root, factory ) {
	if( typeof define === 'function' && define.amd ) {
		// AMD. Register as an anonymous module.
		define( function() {
			root.Vote = factory();
			return root.Vote;
		} );
	} else if( typeof exports === 'object' ) {
		// Node. Does not work with strict CommonJS.
		module.exports = factory();
	} else {
		// Browser globals.
		root.Vote = factory();
	}
}( this, function() {

	'use strict';

	var Vote;
	var config = {
		client_id: 0,
		isClient: false,
		userAgent: navigator.userAgent
	};

	var results = [];

	/**
	 * Extend object a with the properties of object b.
	 * If there's a conflict, object b takes precedence.
	 */
	function extend( a, b ) {
		for( var i in b ) {
			a[ i ] = b[ i ];
		}
	}

	function clicked(a, b, c)
	{
		var t = $(this);
		var selected = [];
		$('#BytesReadPoll > input').each(function( index, i ) {
			var idx = $(this).val();
			var s = $(this).prop('checked');
			selected.push({ idx: idx, value: s });
		});

		var o = {
			    vote_id: 99
			    ,poll_id: $('#BytesReadPoll').attr('pollid')    
			    ,client_id: config.client_id
			    ,selected: selected
			    ,timestamp: new Date()
			    /*[
				{idx: 1, value: false }
				,{idx: 2, value: true }
				,{idx: 3, value: true }
				,{idx: 4, value: "Erlang is the best" }
			    ]*/
			};
		
		Multiplex.socket().emit('data', o);
	}

	function init() {
		var voting = Reveal.getConfig().voting;
		extend(config, voting);

		$('#BytesReadPoll').on('click', 'input', null, clicked);
		if(!isClient)
		{
			$('#BytesReadPoll_Button').show();
			$('#BytesReadPoll_Button').click( function() { ShowResults();  } );
		}
	}

	function randomColorFactor() {
		return Math.round(Math.random() * 255);
	}

	function randomColor(opacity) {
		return 'rgba(' + randomColorFactor() + ',' + randomColorFactor() + ',' + randomColorFactor() + ',' + (opacity || '.3') + ')';
	}

	function ShowResults() {
		var ss = SummarizeResults();

		var config = {
			type: 'pie',
			data: {
			    datasets: [{
				data: [ ],
				backgroundColor: [ ],
			    }],
			    labels: [ ]
			},
			options: {
			    responsive: true
			}
		};

		$.each(ss.counts, function( idx, cnt ) {
			config.data.datasets[0].data.push(cnt);
			config.data.datasets[0].backgroundColor.push( randomColor(0.7) );
			config.data.labels.push( idx );
		});

		$("#BytesReadPoll").hide();
		$("#BytesReadPoll_Results").show();

		var ctx = $("#BytesReadPoll_Chart")[0].getContext("2d");
		window.myPie = new Chart(ctx, config);

	}

	function SummarizeResults() {
		// assume results contains only one poll, but possibly multiple votes from the same client
		// retain only the data with the latest timestamp per client
		var s = {};

		$.each(results, function( idx, r ) {
			if(!(r.client_id in s))
			{
				s[r.client_id] = r;
			}
			else if( s[r.client_id].timestamp < r.timestamp )
			{
					s[r.client_id] = r;
			}
			// else: r is older than s[]'s current vote 
		});
		
		// now s contains the latest results from each client
		// summarize the poll's values across all clients

		var summary = {
		    vote_id: 99
		    ,poll_id: $('#BytesReadPoll').attr('pollid')    
		    ,counts: {}
		    ,entries: {}
		};
		
		$.each(s, function( client_id, r ) {
			var sel = r.selected;
			$.each(sel, function( j, entry ) {
				if(!(entry.idx in summary.counts))
				{
					summary.entries[entry.idx]=entry;
					if(entry.value) {
						summary.counts[entry.idx]=1;
					} else {
						summary.counts[entry.idx]=0;
					} 
				}
				else 
				{
					if(entry.value) {
						summary.counts[entry.idx]++;
					} 
				}
			});
		});

		console.log(summary);
		console.log(JSON.toString(summary));
		return summary;
	}

	Vote = {
		init: init,
		socket: function() {
			return socket;
		},

		// Returns the current configuration object
		getConfig: function() {
			return config;
		},

		post: function () {
			DoExamplePoll();
		},

		results : function() {
			return results;
		},

		SaveResult : function(r) {
			results.push(r);
		},

		ClearResults : function() {
			results = [];
		},

		ShowResults : ShowResults,
		SummarizeResults : SummarizeResults,
	};

	return Vote;

}));



/*
var _pollSubscription = null, _voteSubscription = null, _membersSubscription = null;
var client_id = Math.random().toString(10);

var voteResults = [];

function receive (message) {
    console.log(message);

    var fromUser = message.data.user;
};

function receivePoll (message) {
    console.log(message);

    var title = message.data.title;
    var options = message.data.options;
    showPoll(message.data);
};

function receiveVote (message) {
    console.log("receiveVote!");
    console.log(message);

    voteResults.push(message.data);
    
    DisplayResults();
};

function DisplayResults()
{
	var s = '';
	var client_ids_seen = [];
	var selValTotals = {};
	
	$.each(voteResults, function( index, i ) {
		// only for this poll
		if( i.poll_id !== "4508" )
			return true;

		// skip previously counted client_ids
		if( $.inArray(i.client_id, client_ids_seen) !== -1 )
			return true;
		
		$.each(i.selected, function( idx2, i2 ) {
			var id = i2.idx;
			var val = i2.value;
			if(val)
			{
				if(id in selValTotals)
					selValTotals[id]++;
				else
					selValTotals[id] = 1;
			}
		});
		
	});

	$.each(selValTotals, function( key, value ) {
		s += 'key: ' + key + ', val: ' + value + '<br>';
	});

	$('#Results').html(s);
}

function showPoll (pollInfo) {
	if( $('#poll_id').val() === pollInfo.poll_id )
		return;
	
	$('#pollTitle').text(pollInfo.title);
	$('#poll_id').val(pollInfo.poll_id);
	
	var s = '';
	for(var i=0; i<pollInfo.options.length; i++)
	{
		var o = pollInfo.options[i];
		if(o.type === 'checkbox')
			s += '<input type="checkbox" id="checkbox' + o.idx + '" name="poll' + pollInfo.poll_id + '" value="' + o.idx + '" >' + o.display + '</input>';
		else if(o.type === 'radio')
			s += '<input type="radio" id="radio' + o.idx + '" name="poll' + pollInfo.poll_id + '" value="' + o.idx + '">' + o.display + '</input>';
		else if(o.type === 'write-in')
			s += o.display + ': <input type="text" id="write-in' + o.idx + '" name="poll' + pollInfo.poll_id + '" value="">' + '</input>';
		s += '<br/>';
	}

	$('#options').html(s);
};

function subscribe() {
	if(!_pollSubscription)
		_pollSubscription = $.cometd.subscribe('/chat/voting/polls', receivePoll);

	if(!_voteSubscription)
		_voteSubscription = $.cometd.subscribe('/chat/voting/votes', receiveVote);
	
	if(!_membersSubscription)
		_membersSubscription = $.cometd.subscribe('/chat/voting/members', receive);
}

function clicked(a, b, c)
{
	var t = $(this);
	var selected = [];
	$('#options > input').each(function( index, i ) {
		var idx = $(this).val();
		var s = $(this).prop('checked');
		selected.push({ idx: idx, value: s });
	});

	var o = {
		    vote_id: 99
		    ,poll_id: $('#poll_id').val()    
		    ,client_id: client_id
		    ,selected: selected
		    /*[
		        {idx: 1, value: false }
		        ,{idx: 2, value: true }
		        ,{idx: 3, value: true }
		        ,{idx: 4, value: "Erlang is the best" }
		    ]*/
/*
		};
	
    $.cometd.publish('/chat/voting/votes', o);
	
}

function listenForVoting()
{
	$('#options').on('click', 'input', null, clicked);
}

function publishTests()
{
    $.cometd.publish('/chat/voting/members', {
        user: 'test1',
        room: '/chat/demo'
    });
    
    $.cometd.publish('/chat/voting/polls', examplePoll2());
}


function examplePoll2() {
	return {
	    title: "Choose all your favorite programming languages"
	        ,poll_id: 4508
	        ,multiselect: true
	        ,options: 
	        [{
	            idx: 1
	            ,display: "C#"
	            ,type: "checkbox"
	        }
	        ,{
	            idx: 2
	            ,display: "Javascript"
	            ,type: "checkbox"
	        },{
	            idx: 3
	            ,display: "Perl"
	            ,type: "checkbox"
	        },{
	            idx: 4
	            ,display: "Something else"
	            ,type: "write-in"
	        }]
	    }; 
}

*/
