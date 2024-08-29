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
