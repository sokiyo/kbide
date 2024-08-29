Blockly.JavaScript['KB_JOY_read'] = function (block) {

	var value = block.getFieldValue('AIN');
	var code = 'DEV_I2C1.KB_JOY(0, 0).read(' + value + ')';
	return [code, Blockly.JavaScript.ORDER_ATOMIC];
};

