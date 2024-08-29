Blockly.Blocks["pwm_bldc.drive"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BLDC_DRIVE_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BLDC_DIRECTION)
			.appendField(new Blockly.FieldDropdown( [
				[Blockly.Msg.PWM_BLDC_CLOCKWISE, "0"],
				[Blockly.Msg.PWM_BLDC_COUNTERCLOCKWISE, "1"]
			]), 'DIRECTION');

		this.appendValueInput("SPEED")
			.appendField(Blockly.Msg.MOTOR_SPEED + '(%)')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(55);
		this.setTooltip(Blockly.Msg.PWM_BLDC_DRIVE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_BLDC_DRIVE_HELPURL);
	}
};

Blockly.Blocks["pwm_bldc.stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BLDC_STOP_TITLE);

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(55);
		this.setTooltip(Blockly.Msg.PWM_BLDC_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_BLDC_STOP_HELPURL);
	}
};

