Blockly.JavaScript['vl53l0x.get_distance'] = function(block) {

	//console.log('Hello!');

	return [
		'DEV_I2C1.VL53L0X(' + block.getFieldValue('CHANNEL') + ', 41' + ').get_distance(' + block.getFieldValue('UNIT') + ')',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

