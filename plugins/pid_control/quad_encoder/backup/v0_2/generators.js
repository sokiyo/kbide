Blockly.JavaScript['encoder.get_position'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ')' + '.get_position()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['encoder.get_direction'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ')' + '.get_direction()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['encoder.get_speed'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ')' + '.get_speed()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};