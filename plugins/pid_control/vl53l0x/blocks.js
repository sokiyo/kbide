Blockly.Blocks["vl53l0x.get_distance"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.VL53L0X_DISTANCE_TITLE);

		// i2c channel 0 to 64
		var channel_array = [];
		for (var i = 0;i <= 64; i++) {
			channel_array.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.CHANNEL)
			.appendField(new Blockly.FieldDropdown(channel_array), 'CHANNEL');
	
		this.appendDummyInput()
			.appendField(Blockly.Msg.VL53L0X_DISTANCE_UNIT)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.VL53L0X_DISTANCE_MM, "0"],
				[Blockly.Msg.VL53L0X_DISTANCE_CM, "1"],
				[Blockly.Msg.VL53L0X_DISTANCE_INCH, "2"]
			]), 'UNIT');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.VL53L0X_DISTANCE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.VL53L0X_DISTANCE_HELPURL);
	}
};


