
/*process.argv.forEach(function(val, index, array) {
		  console.log(index + ': ' + val);
});*/

var fs = require('fs');

var hexFilename = process.argv[2];
if(hexFilename === undefined) {
		console.log("Error: missing file name");
		process.exit(1);
}

console.log("loading hex file: " + hexFilename);

var readFileByLine = function(filename, options, callback) {
		fs.open(filename, 'r', function(err, fd) {
				if(err) {
						callback(err, null);
						return;
				}

				fs.close(fd, function(err) {
						if(err)
							console.log("warning: can't close file: " + err);
				});
		});
}

/*fs.readFile(hexFileName, { encoding: "utf-8" }, function(err, data) {
		if(err) throw err;
		var hexFileStrings = data.split(/\r?\n/);

		hexFileStrings.forEach(function(val, index, array) {
		});

		//console.log(hexFileStrings);
});*/

readFileByLine(hexFilename, { encoding : "utf-8" }, function(err, line) {
});

var val = ":100030000250036E640E046E0A0E1FEF00F0056E90";
var fields = val.match(/^:([0-9A-Z]{2})([0-9A-Z]{4})([0-9A-Z]{2})([0-9A-Z]*)([0-9A-Z]{2})$/i);

//console.log(fields);
console.log("Byte count: " + fields[1]);
console.log("Address: " + fields[2]);
console.log("Record type: " + fields[3]);
console.log("Data: " + fields[4]);
console.log("Checksum: " + fields[5]);

var smalloc = require("smalloc");
console.log(smalloc.kMaxLength);

