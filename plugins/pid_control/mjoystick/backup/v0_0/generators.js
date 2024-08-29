Blockly.JavaScript['mjoystick.get_raw_position'] = function(block) {
	return [
		'DEV_IO.MJOYSTICK(ADC1_CHANNEL_6, ADC1_CHANNEL_7)' + '.get_raw_position(' + block.getFieldValue('AXIS') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['mjoystick.get_position'] = function(block) {
	return [
		'DEV_IO.MJOYSTICK(ADC1_CHANNEL_6, ADC1_CHANNEL_7)' + '.get_position(' + block.getFieldValue('AXIS') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};



Blockly.JavaScript['mjoystick.calibrate_set_x'] = function(block) {
	var release_value = Blockly.JavaScript.valueToCode(block, 'RELEASE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var downmost_value = Blockly.JavaScript.valueToCode(block, 'DOWNMOST', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var upmost_value = Blockly.JavaScript.valueToCode(block, 'UPMOST', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	return 'DEV_IO.MJOYSTICK(OUT1_GPIO, IN1_GPIO).calibrate_set(' + release_value + ', ' + downmost_value + ', ' + upmost_value + ');\n';
}

Blockly.JavaScript['mjoystick.calibrate_set_y'] = function(block) {
	var release_value = Blockly.JavaScript.valueToCode(block, 'RELEASE', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var leftmost_value = Blockly.JavaScript.valueToCode(block, 'LEFTMOST', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var rightmost_value = Blockly.JavaScript.valueToCode(block, 'RIGHTMOST', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	return 'DEV_IO.MJOYSTICK(OUT2_GPIO, IN2_GPIO).calibrate_set(' + release_value + ', ' + leftmost_value + ', ' + rightmost_value + ');\n';
}

function mJoystick_GetValue_Code(block) {
	// Numeric value.
	var code = parseInt(block.getFieldValue('VALUE'));
	var order = code >= 0 ? Blockly.JavaScript.ORDER_ATOMIC : Blockly.JavaScript.ORDER_UNARY_NEGATION;
	return [code, order];
}

Blockly.JavaScript["mjoystick.release_default"] = function(block) {
	return mJoystick_GetValue_Code(block);
};

Blockly.JavaScript["mjoystick.downmost_default"] = function(block) {
	return mJoystick_GetValue_Code(block);
};

Blockly.JavaScript["mjoystick.upmost_default"] = function(block) {
	return mJoystick_GetValue_Code(block);
};

Blockly.JavaScript["mjoystick.leftmost_default"] = function(block) {
	return mJoystick_GetValue_Code(block);
};

Blockly.JavaScript["mjoystick.rightmost_default"] = function(block) {
	return mJoystick_GetValue_Code(block);
};

