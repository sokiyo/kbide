Blockly.JavaScript['spec_ios.get_analog_raw'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.SPEC_IOS(' + block.getFieldValue('INPUT')  + ')' + '.get_analog_raw()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['specialoutput_write'] = function(block) {
	return 'ports.output' + block.getFieldValue('OUTPUT') + '_write(' + block.getFieldValue('STATUS') + ');\n';
};

Blockly.JavaScript['spec_ios.rd_digital'] = function(block) {
	return [
		// input = IN1(gpio 32), IN2(gpio 33), IN3(gpio 34), IN4(gpio 35)
		'DEV_IO.SPEC_IOS(' + block.getFieldValue('INPUT')  + ')' + '.rd_digital()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};