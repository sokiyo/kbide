Blockly.JavaScript['pwm_bdc.speed'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'SPEED', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.PWM_BDC(' + block.getFieldValue('ADDRESS') + ').speed((uint8_t)' + block.getFieldValue('DIRECTION') + ',(int)' + argument0 + ');\n';	
};

Blockly.JavaScript['pwm_bdc.stop'] = function(block) {
	return 'DEV_IO.PWM_BDC(' + block.getFieldValue('ADDRESS') + ').stop();\n';	
}
