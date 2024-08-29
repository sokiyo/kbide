Blockly.JavaScript['rd_analog.get_analog_raw'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.RD_ANALOG(' + block.getFieldValue('INPUT')  + ')' + '.get_analog_raw()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};
