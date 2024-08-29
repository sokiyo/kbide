Blockly.JavaScript['quad_encoder.get_position'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.QUAD_ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ', ' + block.getFieldValue('PULSES') + ')' + '.get_position()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['quad_encoder.get_direction'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.QUAD_ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ', ' + block.getFieldValue('PULSES') + ')' + '.get_direction()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['quad_encoder.get_speed'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.QUAD_ENCODER(' + block.getFieldValue('PHASEA') + ', ' + block.getFieldValue('PHASEB') + ', ' + block.getFieldValue('PULSES') + ')' + '.get_speed()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};