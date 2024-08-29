Blockly.Blocks["sleep.deep_wakeup"] = {
	SLEEP_DEEP_GPIO_WAKEUP: function() {
		return [
			// ***gpio16 can not be used as external interrupt
			//[Blockly.Msg.SLEEP_DEEP_WAKEUP_SW1, "BUTTON1_GPIO"],
			[Blockly.Msg.SLEEP_DEEP_WAKEUP_SW2, "BUTTON2_GPIO"]
		];
	},
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SLEEP_DEEP_WAKEUP_TITLE);

		this.appendDummyInput('WAKEUP_SW_DUMMY')
			.appendField(new Blockly.FieldCheckbox(true), 'BUTTON_WAKEUP_CHECKBOX')
			.appendField(Blockly.Msg.SLEEP_DEEP_WAKEUP_SW_PRESSED)
			.appendField(new Blockly.FieldDropdown(this.SLEEP_DEEP_GPIO_WAKEUP()), 'WAKEUP_GPIO');

		this.appendDummyInput()
			.appendField(Blockly.Msg.SLEEP_DEEP_WAKEUP_OR);

		this.appendDummyInput('WAKEUP_TIMEOUT_DUMMY')
			.appendField(new Blockly.FieldCheckbox(true), 'TIMEOUT_WAKEUP_CHECKBOX')
			.appendField(Blockly.Msg.SLEEP_DEEP_WAKEUP_TIMEOUT)				
			.appendField(new Blockly.FieldNumber(1, 1, 86400, 0.1), 'WAKEUP_TIMEOUT'); // default, min, max, step

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.SLEEP_DEEP_WAKEUP_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SLEEP_DEEP_WAKEUP_HELPURL);

		// set validators
		// https://groups.google.com/g/blockly/c/kw8M4THfS-I/m/Gj7WxidJAQAJ
		// https://developers.google.com/blockly/guides/create-custom-blocks/fields/built-in-fields/checkbox#creating_a_checkbox_validator
		this.getField('BUTTON_WAKEUP_CHECKBOX').setValidator(this.button_wakeup_validate.bind(this));
		this.getField('TIMEOUT_WAKEUP_CHECKBOX').setValidator(this.timeout_wakeup_validate.bind(this));
	},
	button_wakeup_validate: function() {		
		var input = this.getInput('WAKEUP_SW_DUMMY');
		if (!this.getField('WAKEUP_GPIO')) {
			input.appendField(new Blockly.FieldDropdown(this.SLEEP_DEEP_GPIO_WAKEUP()), 'WAKEUP_GPIO');
		}
		else {
			input.removeField('WAKEUP_GPIO');
		}
	},
	timeout_wakeup_validate: function() {
		var input = this.getInput('WAKEUP_TIMEOUT_DUMMY');
		if (!this.getField('WAKEUP_TIMEOUT')) {
			input.appendField(new Blockly.FieldNumber(1, 1, 86400, 0.1), 'WAKEUP_TIMEOUT');
		}
		else {
			input.removeField('WAKEUP_TIMEOUT');
		}
	}
};
