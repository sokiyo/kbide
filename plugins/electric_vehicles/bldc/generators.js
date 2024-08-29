Blockly.JavaScript['bldc.forward'] = function (block) {
	return 'DEV_IO.BLDC().forward();\n';
};

Blockly.JavaScript['bldc.backward'] = function (block) {
	return 'DEV_IO.BLDC().backward();\n';
};

Blockly.JavaScript['bldc.left'] = function (block) {
	return 'DEV_IO.BLDC().left();\n';
};

Blockly.JavaScript['bldc.right'] = function (block) {
	return 'DEV_IO.BLDC().right();\n';
};


//Blockly.JavaScript['bldc.start'] = function (block) {
//	return 'DEV_IO.BLDC().start();\n';
//};

Blockly.JavaScript['bldc.stop'] = function (block) {
	return 'DEV_IO.BLDC().stop();\n';
};
