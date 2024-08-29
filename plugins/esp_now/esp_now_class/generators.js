Blockly.JavaScript['esp_now.get_mac'] = function(block) {
	var code = 'DEV_IO.ESP_NOW_CLASS().getMAC()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['esp_now.send'] = function(block) {
	var value_data = Blockly.JavaScript.valueToCode(block, 'data', Blockly.JavaScript.ORDER_ATOMIC) || '\"\"';
	var code = 'DEV_IO.ESP_NOW_CLASS().send(' + value_data + ');\n';
	return code;
};

Blockly.JavaScript['esp_now.send2'] = function(block) {
	var value_data = Blockly.JavaScript.valueToCode(block, 'data', Blockly.JavaScript.ORDER_ATOMIC) || '\"\"';
	var text_mac = block.getFieldValue('mac');
	var code = 'DEV_IO.ESP_NOW_CLASS().send("' + text_mac + '", ' + value_data + ');\n';
	return code;
};

Blockly.JavaScript['esp_now.recv'] = function(block) {
	var statements_recv_cb = Blockly.JavaScript.statementToCode(block, 'recv_cb');
	var code = 'DEV_IO.ESP_NOW_CLASS().onRecv([]() { ' + statements_recv_cb + ' });\n';
	return code;
};

Blockly.JavaScript['esp_now.read_string'] = function(block) {
	var code = 'DEV_IO.ESP_NOW_CLASS().readString()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};

Blockly.JavaScript['esp_now.read_number'] = function(block) {
	var code = 'DEV_IO.ESP_NOW_CLASS().readNumber()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
