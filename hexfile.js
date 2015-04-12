
var readFileByLine = require("./readFileByLine");

var hexFilename = process.argv[2];
if(hexFilename === undefined) {
	console.log("Error: missing file name");
	process.exit(1);
}

console.log("loading hex file: " + hexFilename);

function hexfileRecordFromString(str) {

	if(str[0] != ':')
		return null;

	var binRecord = new Buffer(str.substring(1), "hex");

	var byteCount = binRecord[0];

	var addrHi = binRecord[1];
	var addrLo = binRecord[2];
	var addr = addrHi << 8 | addrLo;

	var recordType = binRecord[3];
	
	var data = binRecord.slice(4, -1);
	if(data.length != byteCount)
		return null;

	var checksum = binRecord[binRecord.length - 1];
	checksum += (byteCount + addrHi + addrLo + recordType);
	for (var i = 0; i < data.length; i++)
		checksum += data[i];

	checksum &= 0xFF;
	if(checksum != 0)
		return null;

	return {
		"recordType" : recordType,
		"addr" : addr,
		"data" : data,
	};
}

readFileByLine(hexFilename, function(err, line) {
	if(err) throw err;

	if(line) {
		var hexFileRecord = hexfileRecordFromString(line);
		if(hexFileRecord != null) {
			console.log(
				"recordType: " + hexFileRecord.recordType +
				"; addr: " + hexFileRecord.addr +
				"; data: " + hexFileRecord.data.toString("hex"));
		}
	}
	else
		console.log("done!!!");
});

