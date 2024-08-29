Blockly.JavaScript['bigstream'] = function(block) {
	var value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);
	if (value.length === 0) value = '0';
	var code = 'DEV_IO.BIGSTREAM().sendSensor(CLIENTID, "' + block.getFieldValue('TYPE') + '",' + value + ');\n';
	return code;
};

Blockly.JavaScript['bigstream.is_error'] = function(block) {
	var value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);
	if (value.length === 0) value = '0';
	return [
		'DEV_IO.BIGSTREAM().sendSensor(CLIENTID, "' + block.getFieldValue('TYPE') + '",' + value + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['bigstream.location'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'lat', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'lng', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var code = 'DEV_IO.BIGSTREAM().sendLocation(CLIENTID, ' + argument0 + ',' + argument1 + ');\n';
	return code;
};