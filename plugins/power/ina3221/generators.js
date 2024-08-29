Blockly.JavaScript['ina3221.get_voltage'] = function(block) {
	return [
		'DEV_I2C1.INA3221(0, ' + block.getFieldValue('ADDRESS') + ').get_voltage(' + block.getFieldValue('INA3221_CH') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['ina3221.get_current'] = function(block) {
	return [		
		'DEV_I2C1.INA3221(0, ' + block.getFieldValue('ADDRESS') + ').get_current(' + block.getFieldValue('INA3221_CH') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['ina3221.set_shunt_resistor'] = function(block) {
	return 'DEV_I2C1.INA3221(0, ' + block.getFieldValue('ADDRESS') + ').set_shunt_resistor(' + block.getFieldValue('INA3221_CH') + ', ' + + block.getFieldValue('SHUNT_RESISTOR') + ');\n';
};
