Blockly.Blocks["rd_analog.get_analog_raw"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.RD_ANALOG_TITLE)
			.appendField(new Blockly.FieldDropdown([
				["IN3", "34"],
				["IN4", "35"],
				["VN", "39"]
			]), 'INPUT');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.RD_ANALOG_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.RD_ANALOG_HELPURL);
	}
};
