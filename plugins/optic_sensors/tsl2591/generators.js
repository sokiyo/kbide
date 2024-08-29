Blockly.JavaScript['tsl2591.get_illuminance'] = function(block) {
	return [
		'DEV_I2C1.TSL2591(' + block.getFieldValue('CHANNEL') + ', ' + block.getFieldValue('ADDRESS') + ').get_illuminance(' + block.getFieldValue('GAIN') + ',' + block.getFieldValue('TIME') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};
