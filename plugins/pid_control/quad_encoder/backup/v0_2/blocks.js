Blockly.Blocks["encoder.get_position"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.ENCODER_GET_POSITION_TITLE)
			.appendField(Blockly.Msg.ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.ENCODER_GET_POSITION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.ENCODER_GET_POSITION_HELPURL);
	}
};

Blockly.Blocks["encoder.get_direction"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.ENCODER_GET_DIRECTION_TITLE)
			.appendField(Blockly.Msg.ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.ENCODER_GET_DIRECTION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.ENCODER_GET_DIRECTION_HELPURL);
	}
};

Blockly.Blocks["encoder.get_speed"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.ENCODER_GET_SPEED_TITLE)
			.appendField(Blockly.Msg.ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.ENCODER_GET_SPEED_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.ENCODER_GET_SPEED_HELPURL);
	}
};