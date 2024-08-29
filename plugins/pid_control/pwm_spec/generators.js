Blockly.JavaScript['pwm_spec.speed'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'SPEED', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.PWM_SPEC(' + '1' + ').speed((uint8_t)' + block.getFieldValue('DIRECTION') + ',(int)' + argument0 + ');\n';	
};

Blockly.JavaScript['pwm_spec.stop'] = function(block) {
	return 'DEV_IO.PWM_SPEC(' + '1' + ').stop();\n';	
}
