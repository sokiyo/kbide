Blockly.Blocks["pwm_spec.speed"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_SPEC_SPEED_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_SPEC_DIRECTION)
			.appendField(new Blockly.FieldDropdown( [
				[Blockly.Msg.PWM_SPEC_CLOCKWISE, "0"],
				[Blockly.Msg.PWM_SPEC_COUNTERCLOCKWISE, "1"]
			]), 'DIRECTION');

		this.appendValueInput("SPEED")
			.appendField(Blockly.Msg.MOTOR_SPEED + '(%)')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(30);
		this.setTooltip(Blockly.Msg.PWM_SPEC_SPEED_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_SPEC_SPEED_HELPURL);
	}
};

Blockly.Blocks["pwm_spec.stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_SPEC_STOP_TITLE);

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(30);
		this.setTooltip(Blockly.Msg.PWM_SPEC_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_SPEC_STOP_HELPURL);
	}
};

