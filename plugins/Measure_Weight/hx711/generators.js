Blockly.JavaScript['hx711.read'] = function (block) {
	return [
		'DEV_IO.HX711().get_raw_weight()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['get_units'] = function (block) {
	return [
		'DEV_IO.HX711().get_units()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['set_weight'] = function (block) {
	var value_number = Blockly.JavaScript.valueToCode(block, 'number', Blockly.JavaScript.ORDER_ATOMIC);
	return 'DEV_IO.HX711().set_scale((float)' + value_number + ');\n';
};

Blockly.JavaScript['set_offset'] = function (block) {
	var value_number = Blockly.JavaScript.valueToCode(block, 'number', Blockly.JavaScript.ORDER_ATOMIC);
	return 'DEV_IO.HX711().set_offset((int)' + value_number + ');\n';
};

Blockly.JavaScript['tare'] = function (block) {
	return 'DEV_IO.HX711().tare();\n';
};

Blockly.JavaScript['calibrate'] = function (block) {
	return 'DEV_IO.HX711().calibrate();\n';
};
