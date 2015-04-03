
var readFileByLine = require("./readFileByLine");

var hexFilename = process.argv[2];
if(hexFilename === undefined) {
	console.log("Error: missing file name");
	process.exit(1);
}

console.log("loading hex file: " + hexFilename);

function hexfileRecordFromString(str) {

	if(str[0] != ':') {
		console.log("invalid start code: " + str);
		return null;
	}

	var binRecord = new Buffer(str.substring(1), "hex");

	var byteCount = binRecord[0];

	var addrHi = binRecord[1];
	var addrLo = binRecord[2];
	var addr = addrHi << 8 | addrLo;

	var recordType = binRecord[3];
	
	var data = binRecord.slice(4, -1);
	if(data.length != byteCount) {
		console.log("length of data != byte count: " + str);
		return null;
	}

	var checksum = binRecord[binRecord.length - 1];
	checksum += (byteCount + addrHi + addrLo + recordType);
	for (var i = 0; i < data.length; i++)
		checksum += data[i];

	checksum &= 0xFF;

	if(checksum != 0) {
		console.log("wrong checksum: " + str);
		return null;
	}

	console.log(
			"byteCount: " + byteCount.toString(16) +
			"; addr: " + addr.toString(16) +
			"; recordType: " + recordType.toString(16) +
			"; data: " + data.toString("hex") +
			"; checksum: " + checksum.toString(16));

	return null;
}

readFileByLine(hexFilename, { encoding : "utf-8" }, function(err, line) {
	if(err) throw err;

	if(line)
		hexfileRecordFromString(line);
	else
		console.log("done!!!");
});

