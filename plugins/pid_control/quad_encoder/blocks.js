Blockly.Blocks["quad_encoder.get_position"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_GET_POSITION_TITLE)
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');

		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_PULSES)
			.appendField(new Blockly.FieldNumber(100, 0, 100, 1), 'PULSES')
		
		this.setInputsInline(true);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.QUAD_ENCODER_GET_POSITION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.QUAD_ENCODER_GET_POSITION_HELPURL);
	}
};

Blockly.Blocks["quad_encoder.get_direction"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_GET_DIRECTION_TITLE)
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');

		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_PULSES)
			.appendField(new Blockly.FieldNumber(100, 0, 100, 1), 'PULSES')

		this.setInputsInline(true);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.QUAD_ENCODER_GET_DIRECTION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.QUAD_ENCODER_GET_DIRECTION_HELPURL);
	}
};

Blockly.Blocks["quad_encoder.get_speed"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_GET_SPEED_TITLE)
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEA)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEA')
			.appendField(Blockly.Msg.QUAD_ENCODER_PHASEB)
			.appendField(new Blockly.FieldDropdown([
				["IN1", "IN1_GPIO"],
				["IN2", "IN2_GPIO"],
				["IN3", "IN3_GPIO"],
				["IN4", "IN4_GPIO"]
			]), 'PHASEB');

		this.appendDummyInput()
			.appendField(Blockly.Msg.QUAD_ENCODER_PULSES)
			.appendField(new Blockly.FieldNumber(100, 0, 100, 1), 'PULSES')

		this.setInputsInline(true);
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(200);
		this.setTooltip(Blockly.Msg.QUAD_ENCODER_GET_SPEED_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.QUAD_ENCODER_GET_SPEED_HELPURL);
	}
};