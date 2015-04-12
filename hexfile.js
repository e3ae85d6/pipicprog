
var fs = require("fs");
var readHexFile = require("./readHexFile");

var hexFilename = process.argv[2];
if(hexFilename === undefined) {
	console.log("Error: missing file name");
	process.exit(1);
}

console.log("loading hex file: " + hexFilename);

var extendedLinearAddress = 0;
var hexfileData = [];

readHexFile(hexFilename, function(err, hexfileRecord) {
	if(err) throw err;

	if(hexfileRecord != null) {
		//console.log("recordType: " + hexfileRecord.recordType + "; addr: " + hexfileRecord.addr + "; data: " + hexfileRecord.data.toString("hex"));
		if(hexfileRecord.recordType == 0) {
			var offset = (extendedLinearAddress << 16) | hexfileRecord.addr;
			//console.log("record offset: " + offset.toString(16));
			for(var i = 0; i < hexfileRecord.data.length; i++) {
				if(hexfileData[offset + i] == undefined) {
					hexfileData[offset + i] = hexfileRecord.data[i];
				}
				else {
					console.log("warning: byte at " + (offset + i).toString(16) + " already defined");
				}
			}
		}
		else if(hexfileRecord.recordType == 1) {
			for(var i = 0; i < hexfileData.length; i++) {
				if(hexfileData[i] == undefined)
					console.log("warning: byte at " + (offset + i).toString(16) + " undefined");
			}

			var binFilename = hexFilename + ".bin";
			console.log("writing " + hexfileData.length + " bytes to: " + binFilename);
			writeFileBuffer(binFilename, new Buffer(hexfileData), function(err) {
				if(err) throw err;
			});

		}
		else if(hexfileRecord.recordType == 2) {
			console.log("warning: 2 - unsupported record type");
		}
		else if(hexfileRecord.recordType == 3) {
			console.log("warning: 3 - unsupported record type");
		}
		else if(hexfileRecord.recordType == 4) {
			//console.log("data: " + hexfileRecord.data.toString("hex"));
			//var addrHi = hexfileRecord.data[0];
			//var addrLo = hexfileRecord.data[1];
			//extendedLineadAddress = addrHi << 8 | addrLo;//hexfileRecord.data.readUInt16BE();
			extendedLinearAddress = hexfileRecord.data.readUInt16BE(0);
			//extendedLinearAddress -= 0x0050;
		}
		else if(hexfileRecord.recordType == 5) {
			console.log("warning: 5 - unsupported record type");
		}
	}
	else {
		console.log("done");
	}
});

function writeFileBuffer(filename, buffer, callback) {
	fs.open(filename, 'w', function(err, fd) {
		if(err) {
			callback(err);
			return;
		}

		fs.write(fd, buffer, 0, buffer.length, 0, function(err, written, buffer) {
			if(err) {
				fs.close(fd, function() {});
				callback(err);
				return;
			}

			if(written < buffer.length) {
				console.log("not all data has been written");
			}

			fs.close(fd, callback);
		});
	});
}


