
var readFileByLine = require("./readFileByLine");

function hexfileRecordFromString(str) {

	str = str.trim();
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

module.exports = function(filename, callback) {
	readFileByLine(filename, function(err, line) {
		if(err) {
			callback(err, null);
		}

		if(line) {
			var hexFileRecord = hexfileRecordFromString(line);
			callback(null, hexFileRecord);
		}
		else {
			callback(null, null);
		}
	});
}

