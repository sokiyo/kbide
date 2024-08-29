Blockly.JavaScript['pwm_bldc.drive'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'SPEED', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.PWM_BLDC(' + '1' + ').drive((uint8_t)' + block.getFieldValue('DIRECTION') + ',(float)' + argument0 + ');\n';	
};

Blockly.JavaScript['pwm_bldc.stop'] = function(block) {
	return 'DEV_IO.PWM_BLDC(' + '1' + ').stop();\n';	
}
