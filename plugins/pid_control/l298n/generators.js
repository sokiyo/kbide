Blockly.JavaScript['l298n.speed'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'SPEED', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.L298N(' + block.getFieldValue('ADDRESS') + ').speed((uint8_t)' + block.getFieldValue('DIRECTION') + ',(int)' + argument0 + ');\n';	
};

Blockly.JavaScript['l298n.stop'] = function(block) {
	return 'DEV_IO.L298N(' + block.getFieldValue('ADDRESS') + ').stop();\n';	
}
