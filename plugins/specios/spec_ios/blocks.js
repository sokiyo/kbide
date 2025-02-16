Blockly.Blocks["spec_ios.get_analog_raw"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SPEC_IOS_ANALOG_TITLE)
			.appendField(new Blockly.FieldDropdown([
				["I1", "32"],
				["I2", "33"],
				["I3", "34"],
				["I4", "35"],
				["VN", "39"]
			]), 'INPUT');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.SPEC_IOS_ANALOG_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SPEC_IOS_ANALOG_HELPURL);
	}
};

Blockly.Blocks["specialoutput_write"] = {
	init: function() {
		this.appendDummyInput()
			//.appendField(new Blockly.FieldImage("/icons/banana.png", 20, 20, "*"))
			.appendField(Blockly.Msg.SPEC_IOS_OUTPUT_TITLE)
			.appendField(new Blockly.FieldDropdown([
				["O1", "1"],
				["O2", "2"]
			]), 'OUTPUT')
			.appendField(Blockly.Msg.STATUS)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.STATUS_OFF, "0"],
				[Blockly.Msg.STATUS_ON, "1"]
			]), 'STATUS');
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.SPEC_IOS_OUTPUT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SPEC_IOS_OUTPUT_HELPURL);
	}
};

Blockly.Blocks["spec_ios.rd_digital"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.SPEC_IOS_DIGITAL_RD_TITLE)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "32"],
				["IN2", "33"],
				["IN3", "34"],
				["IN4", "35"],
				["VN", "39"],
				["OUT1", "26"],
				["OUT2", "27"]
			]), 'INPUT');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.SPEC_IOS_DIGITAL_RD_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.SPEC_IOS_DIGITAL_RD_HELPURL);
	}
};
