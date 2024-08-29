Blockly.Blocks["l298n.speed"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.L298N_SPEED_TITLE);

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR)
			.appendField(new Blockly.FieldDropdown( [
				["1", "1"],
				["2", "2"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.L298N_DIRECTION)
			.appendField(new Blockly.FieldDropdown( [
				[Blockly.Msg.L298N_CLOCKWISE, "0"],
				[Blockly.Msg.L298N_COUNTERCLOCKWISE, "1"]
			]), 'DIRECTION');

		this.appendValueInput("SPEED")
			.appendField(Blockly.Msg.MOTOR_SPEED + '(%)')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(100);
		this.setTooltip(Blockly.Msg.L298N_SPEED_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.L298N_SPEED_HELPURL);
	}
};

Blockly.Blocks["l298n.stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.L298N_STOP_TITLE);

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR)
			.appendField(new Blockly.FieldDropdown( [
				["1", "1"],
				["2", "2"]
			]), 'ADDRESS');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(100);
		this.setTooltip(Blockly.Msg.L298N_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.L298N_STOP_HELPURL);
	}
};

