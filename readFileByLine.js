
var fs = require('fs');

module.exports = function(filename, callback) {
	fs.open(filename, 'r', function(err, fd) {
		if(err) {
			callback(err, null);
			return;
		}

		var read_all = function(fd, buffer, callback) {
			fs.read(fd, buffer, 0, buffer.length, null, function(err, bytesRead, buffer) {
				callback(err, bytesRead, buffer);

				if(!err && bytesRead > 0)
					read_all(fd, buffer, callback);
			});
		};

		var line = "";
		var buf = new Buffer(1024);

		read_all(fd, buf, function(err, bytesRead, buffer) {
			if(err) {
    		    fs.close(fd, function(err) { });
				callback(err, null);
			}
			else if(bytesRead == 0) {
				if(line.length > 0)
					callback(null, line);
				
				fs.close(fd, function(err) { });
				callback(null, null);
			}
			else {
				var str = buffer.toString("ascii", 0, bytesRead);
				for(var i = 0; i < str.length; i++) {
				   	var ch = str[i];

					if(ch == '\r') {
						continue;
					}
					else if(ch == '\n') {
						callback(null, line);
						line = "";
					}
					else {
						line += ch;
					}
				}
			}
		});
	});
}

