
var readHexFile = require("./readHexFile");

var hexFilename = process.argv[2];
if(hexFilename === undefined) {
	console.log("Error: missing file name");
	process.exit(1);
}

console.log("loading hex file: " + hexFilename);

readHexFile(hexFilename, function(err, hexfileRecord) {
	if(err) throw err;

	if(hexfileRecord != null) {
		console.log("recordType: " + hexfileRecord.recordType + "; addr: " + hexfileRecord.addr + "; data: " + hexfileRecord.data.toString("hex"));
	}
	else {
		console.log("done");
	}
});

