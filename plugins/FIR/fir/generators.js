Blockly.JavaScript['FIR.begin'] = function (block) {
	var host = block.getFieldValue('HOST');
	var key = block.getFieldValue('KEY');
	host = host.replace(/\s+/g, ''); //remove space
	key = key.replace(/\s+/g, ''); //remove space
	return 'DEV_IO.FIR().begin("'+host+'", "'+key+'");\n';
}

Blockly.JavaScript['FIR.get_string'] = function (block) {
	var path = Blockly.JavaScript.valueToCode(block, 'PATH', Blockly.JavaScript.ORDER_ATOMIC) || '';
	path = path.replace("(char *)","");
	return [`DEV_IO.FIR().get_string(`+path+`)`, Blockly.JavaScript.ORDER_ATOMIC]
}

Blockly.JavaScript['FIR.set'] = function (block) {
	var path = Blockly.JavaScript.valueToCode(block, 'PATH', Blockly.JavaScript.ORDER_ATOMIC) || '';
	// path = path.replace("(char *)","");

	var data = Blockly.JavaScript.valueToCode(block, 'DATA', Blockly.JavaScript.ORDER_ATOMIC) || '';
	// data = data.replace("(char *)","");
	return `DEV_IO.FIR().set(`+path+`, `+data+`);\n`;
	// return 'DEV_IO.FIR().debug();\n';
}

Blockly.JavaScript['FIR.delete'] = function (block) {
	var path = Blockly.JavaScript.valueToCode(block, 'PATH', Blockly.JavaScript.ORDER_ATOMIC) || '';
	path = path.replace("(char *)","");
	return `DEV_IO.FIR().remove(`+path+`);\n`;
}

Blockly.JavaScript['FIR.onvalue'] = function(block) {
	const insertAt = (str, sub, pos) => `${str.slice(0, pos)}${sub}${str.slice(pos)}`;
	var path = block.getFieldValue('PATH') || '';
	// path = insertAt(path, "/", path.indexOf("\"") + 1);
	path = "\"" + path + "\"";
	var statement = Blockly.JavaScript.statementToCode(block, 'DO');

	Blockly.JavaScript.taskNumber++;
	var funcName = 'FIR_Task' + Blockly.JavaScript.taskNumber;
	var code = 'DEV_IO.FIR().on_values('+path+',[](){'+statement+'});\n';
	code = Blockly.JavaScript.scrub_(block, code);
	Blockly.JavaScript.definitions_['%' + funcName] = code;
	// return 'DEV_IO.FIR().on_values('+path+',[](){'+statement+'});\n';
	return null;
};

Blockly.JavaScript['FIR.value_text'] = function(block) {
	// const insertAt = (str, sub, pos) => `${str.slice(0, pos)}${sub}${str.slice(pos)}`;
	var path = Blockly.JavaScript.valueToCode(block, 'PATH', Blockly.JavaScript.ORDER_ATOMIC) || '';
	// path = path.replace("(char *)","");
	// path = insertAt(path, "/", path.indexOf("\"") + 1);
	// path = "\"" + path + "\"";
	return [`DEV_IO.FIR().value_string(`+path+`)`, Blockly.JavaScript.ORDER_ATOMIC]
};

Blockly.JavaScript['FIR.convert'] = function(block) {
	// const insertAt = (str, sub, pos) => `${str.slice(0, pos)}${sub}${str.slice(pos)}`;
	var data = Blockly.JavaScript.valueToCode(block, 'DATA', Blockly.JavaScript.ORDER_ATOMIC) || '';
	// data = insertAt(data, "/", data.indexOf("\"") + 1);
	// data = "\"" + data + "\"";
	return [`DEV_IO.FIR().convert(`+data+`)`, Blockly.JavaScript.ORDER_ATOMIC]
};

Blockly.JavaScript['FIR.concat'] = function(block) {
	var left = String(Blockly.JavaScript.valueToCode(block, 'LEFT', Blockly.JavaScript.ORDER_ATOMIC) || '');
	// left = left.replace("(char *)","");
	// left = left.replace(/\"/g,"");
	var right = String(Blockly.JavaScript.valueToCode(block, 'RIGHT', Blockly.JavaScript.ORDER_ATOMIC) || '');
	// right = right.replace("(char *)","");
	// right = right.replace(/\"/g,"");
	return [`DEV_IO.FIR().concat(`+left+`,`+right+`)`, Blockly.JavaScript.ORDER_ATOMIC]
	// return [`"${left} + ${right}"`, Blockly.JavaScript.ORDER_ATOMIC]
};
