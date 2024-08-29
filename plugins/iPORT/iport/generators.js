Blockly.JavaScript['iport_digital_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.iPORT().digitalRead(' + dropdown_pin + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['iport_digital_write'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.iPORT().digitalWrite(' + dropdown_pin + ', ' + value_value + ');\n';
	return code;
};

Blockly.JavaScript['iport_analog_read'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.iPORT().analogRead(' + dropdown_pin + ')';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['iport_analog_write'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.iPORT().analogWrite(' + dropdown_pin + ', ' + value_value + ');\n';
	return code;
};

Blockly.JavaScript['iport_servo'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_angle = Blockly.JavaScript.valueToCode(block, 'angle', Blockly.JavaScript.ORDER_ATOMIC) || "0";
	var code = 'DEV_IO.iPORT().servoSetAngle(' + dropdown_pin + ', ' + value_angle + ');\n';
	return code;
};

Blockly.JavaScript['iport_servo_calibrate'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_min = block.getFieldValue('min');
	var number_max = block.getFieldValue('max');
	var code = 'DEV_IO.iPORT().servoCalibrate(' + dropdown_pin + ', ' + number_min + ', ' + number_max + ');\n';
	return code;
};

Blockly.JavaScript['iport_write_usb'] = function(block) {
	var dropdown_value = block.getFieldValue('value');
	var code = 'DEV_IO.iPORT().usbWrite(' + dropdown_value  + ');\n';
	return code;
};

Blockly.JavaScript['iport_toggle_usb'] = function(block) {
	var code = 'DEV_IO.iPORT().usbToggle();\n';
	return code;
};

Blockly.JavaScript['iport_read_usb'] = function(block) {
	var code = 'DEV_IO.iPORT().usbRead()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['iport_analog_write_usb'] = function(block) {
	var value_value = Blockly.JavaScript.valueToCode(block, 'value', Blockly.JavaScript.ORDER_ATOMIC);
	var code = 'DEV_IO.iPORT().usbAnalogWrite(' + value_value + ');\n';
	return code;
  };
