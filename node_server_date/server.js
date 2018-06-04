var express = require('express');
var app = express();

app.get('/time_now', function(req, res) {
    var now = new Date();
    res.send({
        time_now: now.toISOString(),
        time_now_millis: now.getTime()
    });
});

var server = app.listen(3000, function() {
    console.log((new Date()) + ' Server is listening on port ' + server.address().port);
});