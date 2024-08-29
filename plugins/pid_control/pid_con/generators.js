/*
Blockly.JavaScript['pid_con.run'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'KP', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'KI', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument2 = Blockly.JavaScript.valueToCode(block, 'KD', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument3 = Blockly.JavaScript.valueToCode(block, 'SETPOINT', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument4 = Blockly.JavaScript.valueToCode(block, 'SENSOR', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	return 'DEV_IO.PID_CON(0).run(' + argument0 + ',' + argument1 + ',' + argument2 + ',' + argument3 + ',' + argument4 +');\n';
};
*/


Blockly.JavaScript['pid_con.run'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'KP', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'KI', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument2 = Blockly.JavaScript.valueToCode(block, 'KD', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument3 = Blockly.JavaScript.valueToCode(block, 'SETPOINT', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument4 = Blockly.JavaScript.valueToCode(block, 'SENSOR', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';

	var code = 'DEV_IO.PID_CON(0).run(' + argument0 + ',' + argument1 + ',' + argument2 + ',' + argument3 + ',' + argument4 + ')';

	//console.log(code);

	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['ms_delay'] = function(block) {
	return 'vTaskDelay(' + parseInt(1000 * parseFloat(block.getFieldValue('VALUE'))) + ' / portTICK_RATE_MS);\n';
};

Blockly.JavaScript['spec_math_number'] = function(block) {
	console.log('--- ', block.getField('VALUE'), block.getField('VALUE').sourceBlock_.type);
	return [
		'(double)' + block.getFieldValue('VALUE'),
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['ser_print'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'STRING', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'NUMBER', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.PID_CON(' + '1' + ').ser_print(' + argument0 + ',' + argument1 + ');\n';	
};

Blockly.JavaScript['ser_print_1'] = function(block) {
	var argument0 = Blockly.JavaScript.valueToCode(block, 'NUMBER', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_IO.PID_CON(' + '1' + ').ser_print_1(' + argument0 + ');\n';	
};

Blockly.JavaScript['som_prints'] = function (block) {
	var statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');

	var code = `${statements_callback} printf(\"\\n\");\n`;
	return code;
};