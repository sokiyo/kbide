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

Blockly.Blocks["ms_delay"] = {
	init: function() {
		// max 1 day delay = 86400 sec.
		this.appendDummyInput()
			.appendField(Blockly.Msg.PID_CON_MS_DELAY_TITLE)
			.appendField(new Blockly.FieldNumber(0.5, 0.001, 86400, 0.001), 'VALUE'); // default, min, max, step
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.PID_CON_MS_DELAY_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PID_CON_MS_DELAY_HELPURL);
	}
};

Blockly.Blocks["spec_math_number"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(0, -9999999, 9999999, 0.001), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.MATH_NUMBER_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MATH_NUMBER_HELPURL);
	}
};

Blockly.Blocks["ser_print"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PID_CON_SER_PRINT_TITLE);

		this.appendValueInput('STRING')
			.appendField(Blockly.Msg.PID_CON_SER_PRINT_STRING);
			
		this.appendValueInput('NUMBER')
			.appendField(Blockly.Msg.PID_CON_SER_PRINT_NUMBER)
			.setCheck('Number');
		
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.PID_CON_SER_PRINT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PID_CON_SER_PRINT__HELPURL);
	}
};

Blockly.Blocks["ser_print_1"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.PID_CON_SER_PRINT_TITLE);

		this.appendValueInput('NUMBER')
			.appendField(Blockly.Msg.PID_CON_SER_PRINT_NUMBER)
			.setCheck('Number');
		
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.PID_CON_SER_PRINT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.PID_CON_SER_PRINT__HELPURL);
	}
};

Blockly.Blocks['som_prints'] = {
	init: function () {
		this.jsonInit({
			"type": "",
			"message0": "Print graph %1 %2",
			"args0": [
				{
					"type": "input_dummy"
				},
				{
					"type": "input_statement",
					"name": "callback"
				}
			],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};