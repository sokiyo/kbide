Blockly.Blocks["pid_con.run"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PID_CON_RUN_TITLE);

		this.appendValueInput('KP')
		.appendField('Kp =')
		.setCheck('Number');

		this.appendValueInput('KI')
		.appendField(', Ki =')
		.setCheck('Number');

		this.appendValueInput('KD')
		.appendField(', Kd =')
		.setCheck('Number');

		this.appendValueInput('SETPOINT')
		.appendField(', Set Point =')
		.setCheck('Number');

		this.appendValueInput('SENSOR')
		.appendField(', Sensor Input =')
		.setCheck('Number');

		this.setInputsInline(true);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.PID_CON_RUN_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PID_CON_RUN_HELPURL);
	}
};