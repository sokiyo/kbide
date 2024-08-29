Blockly.Blocks["pwm_bdc.speed"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BDC_SPEED_TITLE);

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.MOTOR)
			.appendField(new Blockly.FieldDropdown( [
				["1", "1"],
				["2", "2"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BDC_DIRECTION)
			.appendField(new Blockly.FieldDropdown( [
				[Blockly.Msg.PWM_BDC_CLOCKWISE, "0"],
				[Blockly.Msg.PWM_BDC_COUNTERCLOCKWISE, "1"]
			]), 'DIRECTION');

		this.appendValueInput("SPEED")
			.appendField(Blockly.Msg.MOTOR_SPEED + '(%)')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(100);
		this.setTooltip(Blockly.Msg.PWM_BDC_SPEED_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_BDC_SPEED_HELPURL);
	}
};

Blockly.Blocks["pwm_bdc.stop"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PWM_BDC_STOP_TITLE);

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
		this.setTooltip(Blockly.Msg.PWM_BDC_STOP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PWM_BDC_STOP_HELPURL);
	}
};

