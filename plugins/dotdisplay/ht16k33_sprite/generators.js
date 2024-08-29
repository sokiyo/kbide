Blockly.JavaScript['basic_led16x8_sprite'] = function(block) {
	var buf = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00];
	for (var x = 0; x < 16; x++) {
		var byte = 0;
		for (var y = 0; y < 8; y++) {
			var val = block.getFieldValue('POS_X' + x + '_Y' + y);
			if (val == 'TRUE') {
				byte |= (0x01 << y);
			};
		}
		buf[x] = byte;
	}

	var str = '';
	for (var i = 0; i < 16; i++) {
		str += '\\x' + buf[i].toString(16);;
	}

	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).show((uint8_t *)"' + str + '");\n';
};

Blockly.JavaScript['basic_led16x8_clr_sprite'] = function(block) {
	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).clear();\n'
};

Blockly.JavaScript['led16x8.dot'] = function(block) {
	//var buf = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00];
	var x = parseInt(block.getFieldValue('X'));
	var y = parseInt(block.getFieldValue('Y'));
	//buf[x] = (0x01 << y);

	//var str = '';
	//for (var i = 0; i < 16; i++) {
	//	str += '\\x' + buf[i].toString(16);;
	//}
	var type = parseInt(block.getFieldValue('TYPE'));

	//return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).show((uint8_t *)"' + str + '");\n';
	//return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).dot((uint8_t *)"' + str + '");\n';
	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).dot(' + x + ',' + y + ',' + type + ');\n';
};

Blockly.JavaScript['led16x8.dot_var'] = function(block) {
	var type = parseInt(block.getFieldValue('TYPE'));
	var argument0 = Blockly.JavaScript.valueToCode(block, 'X', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'Y', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).dot(' + argument0 + ',' + argument1 + ',' + type + ');\n';
};

Blockly.JavaScript['led16x8.dot_move'] = function(block) {
	var move = parseInt(block.getFieldValue('MOVE'));
	var type = parseInt(block.getFieldValue('TYPE'));
	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).move(' + move + ',' + type + ');\n';
};

Blockly.JavaScript['led16x8.dot_stack'] = function(block) {
	var type = parseInt(block.getFieldValue('TYPE'));
	var argument0 = Blockly.JavaScript.valueToCode(block, 'X', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	var argument1 = Blockly.JavaScript.valueToCode(block, 'Y', Blockly.JavaScript.ORDER_ASSIGNMENT) || '0';
	return 'DEV_I2C0.HT16K33_SPRITE(0, 0x70).dot_stack(' + argument0 + ',' + argument1 + ',' + type + ');\n';
};
