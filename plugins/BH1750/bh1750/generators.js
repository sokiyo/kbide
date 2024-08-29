Blockly.JavaScript['bh1750_read_light_level'] = function(block) {
	var code = 'DEV_I2C1.BH1750(0, 0x23).readLightLevel()';
	return [code, Blockly.JavaScript.ORDER_NONE];
};
