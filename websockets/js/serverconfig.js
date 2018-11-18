
//var socketIOserverURL = 'http://192.168.1.64:1948';
//var socketIOserverURL = 'http://192.168.10.146:1948';
//var socketIOserverURL = 'http://192.168.10.123:1948';
var socketIOserverURL = 'http://localhost:1948';
//var socketIOserverURL = 'http://104.9.34.41:1948';
//var socketIOserverURL = 'http://ws.djohn89.com:1948';
var socketIOtokenID = '945ed4588b7c98e5';
var socketIOsecret = '14761387193661141545';

/*
$.ajax({
	async: false
	,url: socketIOserverURL + '/token'
	,dataType: 'json'
	,method: 'GET'
	,success: function (data, textStatus, jqXHR) {
		socketIOtokenID = data.socketId;
		socketIOsecret = data.secret;
	}
	,error: function (jqXHR, textStatus, errorThrown) {
		console.log(errorThrown);
	}
});
*/


// get a completely separate token for voting messages
var vote_socketIOserverURL = 'http://192.168.10.146:1948';
var vote_socketIOtokenID = '';
var vote_socketIOsecret = '';

/*
$.ajax({
	async: false
	,url: socketIOserverURL + '/token'
	,dataType: 'json'
	,method: 'GET'
	,success: function (data, textStatus, jqXHR) {
		vote_socketIOtokenID = data.socketId;
		vote_socketIOsecret = data.secret;
	}
	,error: function (jqXHR, textStatus, errorThrown) {
		console.log(errorThrown);
	}
});
*/

