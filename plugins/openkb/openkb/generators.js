Blockly.JavaScript['openkb_digital_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.OpenKB().digitalRead(' + dropdown_pin + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['openkb_digital_write'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.OpenKB().digitalWrite(' + dropdown_pin + ', ' + value_value + ');\n';
	return code;
};

Blockly.JavaScript['openkb_analog_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.OpenKB().analogRead(' + dropdown_pin + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['openkb_analog_write'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.OpenKB().analogWrite(' + dropdown_pin + ', ' + value_value + ');\n';
	return code;
};

Blockly.JavaScript['openkb_servo'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_angle = Blockly.JavaScript.valueToCode(block, 'angle', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.OpenKB().servoSetAngle(' + dropdown_pin + ', ' + value_angle + ');\n';
	return code;
};

Blockly.JavaScript['openkb_servo_calibrate'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_min = block.getFieldValue('min');
	var number_max = block.getFieldValue('max');
	var code = 'DEV_IO.OpenKB().servoCalibrate(' + dropdown_pin + ', ' + number_min + ', ' + number_max + ');\n';
	return code;
};
