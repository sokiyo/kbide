Blockly.JavaScript['bt_setup'] = function(block) {
	var value_name = Blockly.JavaScript.valueToCode(block, 'name', Blockly.JavaScript.ORDER_ATOMIC);
	var code = 'DEV_IO.BT().setup(' + value_name + ');\n';
	return code;
};

Blockly.JavaScript['bt_on_auth'] = function(block) {
	var statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');
	var code = 'DEV_IO.BT().on_auth([]() {\n' + statements_callback + '});\n';
	return code;
};

Blockly.JavaScript['bt_get_password'] = function(block) {
	var code = 'DEV_IO.BT().get_password()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bt_on_data'] = function(block) {
	var statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');
	var code = 'DEV_IO.BT().on_data([]() {\n' + statements_callback + '});\n';
	return code;
};

Blockly.JavaScript['bt_get_data'] = function(block) {
	var code = 'DEV_IO.BT().get_data()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bt_available'] = function(block) {
	var code = 'DEV_IO.BT().available()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bt_read'] = function(block) {
	var code = 'DEV_IO.BT().read()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['bt_send_data'] = function(block) {
	var value_data = Blockly.JavaScript.valueToCode(block, 'data', Blockly.JavaScript.ORDER_ATOMIC);
	var code = 'DEV_IO.BT().send(' + value_data + ');';
	return code;
};