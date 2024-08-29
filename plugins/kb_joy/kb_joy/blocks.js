Blockly.Blocks['KB_JOY_read'] = {
	init: function() {

		this.appendDummyInput()
			.appendField('Read Value From')
			.appendField(new Blockly.FieldDropdown([
				["Stick1 X", "0"],
				["Stick1 Y", "1"],
				["Stick2 X", "2"],
				["Stick2 Y", "3"]
			]), 'AIN');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(135);
		this.setTooltip("");
		this.setHelpUrl("");
	}
};

