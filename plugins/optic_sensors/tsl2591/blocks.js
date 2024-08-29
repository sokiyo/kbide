Blockly.Blocks["tsl2591.get_illuminance"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.TSL2591_GET_LUX_TITLE);

		// i2c channel 0 to 64
		var channel_array = [];
		for (var i = 0; i <= 64; i++) {
			channel_array.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField(Blockly.Msg.CHANNEL)
			.appendField(new Blockly.FieldDropdown(channel_array), 'CHANNEL');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.ADDRESS)
			.appendField(new Blockly.FieldDropdown([
				["0x29", "41"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.GAIN)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TSL2591_GAIN_LOW, "0"],
				[Blockly.Msg.TSL2591_GAIN_MED, "16"],
				[Blockly.Msg.TSL2591_GAIN_HIGH, "32"],
				[Blockly.Msg.TSL2591_GAIN_MAX, "48"]
			]), 'GAIN');

		this.appendDummyInput()
			.appendField(Blockly.Msg.TIME)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TSL2591_TIME_100MS, "0"],
				[Blockly.Msg.TSL2591_TIME_200MS, "1"],
				[Blockly.Msg.TSL2591_TIME_300MS, "2"],
				[Blockly.Msg.TSL2591_TIME_400MS, "3"],
				[Blockly.Msg.TSL2591_TIME_500MS, "4"],
				[Blockly.Msg.TSL2591_TIME_600MS, "5"]
			]), 'TIME');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.TSL2591_GET_LUX_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.TSL2591_GET_LUX_HELPURL);
		this.setFieldValue("16", "GAIN");
		this.setFieldValue("2", "TIME");
	}
};