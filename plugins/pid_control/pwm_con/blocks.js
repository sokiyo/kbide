Blockly.Blocks["pwm_con.drive"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_CON_DRIVE_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_CON_DIRECTION)
			.appendField(new Blockly.FieldDropdown( [
				[Blockly.Msg.PWM_CON_CLOCKWISE, "0"],
				[Blockly.Msg.PWM_CON_COUNTERCLOCKWISE, "1"]
			]), 'DIRECTION');

		this.appendValueInput("SPEED")
			.appendField(Blockly.Msg.MOTOR_SPEED + '(%)')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(55);
		this.setTooltip(Blockly.Msg.PWM_CON_DRIVE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_CON_DRIVE_HELPURL);
	}
};

Blockly.Blocks["pwm_con.stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_CON_STOP_TITLE);

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(55);
		this.setTooltip(Blockly.Msg.PWM_CON_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_CON_STOP_HELPURL);
	}
};

