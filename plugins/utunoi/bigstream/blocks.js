Blockly.Blocks["bigstream"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.UTU_NOI_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.UTU_TYPE_F1, "pm10"],
				[Blockly.Msg.UTU_TYPE_F2, "pm2.5"],
				[Blockly.Msg.UTU_TYPE_F3, "temp"],
				[Blockly.Msg.UTU_TYPE_F4, "humid"],
				[Blockly.Msg.UTU_TYPE_F5, "wind_speed"],
				[Blockly.Msg.UTU_TYPE_F6, "wind_direct"],
				[Blockly.Msg.UTU_TYPE_F7, "rainfall"],
				[Blockly.Msg.UTU_TYPE_F8, "light"],
				[Blockly.Msg.UTU_TYPE_F9, "air_pressure"],
				[Blockly.Msg.UTU_TYPE_F10, "graph1"],
				[Blockly.Msg.UTU_TYPE_F11, "graph2"]
			]), 'TYPE');

		this.appendValueInput('value')
			.setCheck('Number');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.UTU_NOI_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.UTU_NOI_HELPURL);
	}
};

Blockly.Blocks["bigstream.is_error"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.UTU_NOI_ERROR_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.UTU_TYPE_F1, "pm10"],
				[Blockly.Msg.UTU_TYPE_F2, "pm2.5"],
				[Blockly.Msg.UTU_TYPE_F3, "temp"],
				[Blockly.Msg.UTU_TYPE_F4, "humid"],
				[Blockly.Msg.UTU_TYPE_F5, "wind_speed"],
				[Blockly.Msg.UTU_TYPE_F6, "wind_direct"],
				[Blockly.Msg.UTU_TYPE_F7, "rainfall"],
				[Blockly.Msg.UTU_TYPE_F8, "light"],
				[Blockly.Msg.UTU_TYPE_F9, "air_pressure"],
				[Blockly.Msg.UTU_TYPE_F10, "graph1"],
				[Blockly.Msg.UTU_TYPE_F11, "graph2"]
			]), 'TYPE');

		this.appendValueInput('value')
			.setCheck('Number');

		this.setOutput(true, 'Boolean');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.UTU_NOI_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.UTU_NOI_HELPURL);
	}
};

Blockly.Blocks["bigstream.location"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.UTU_NOI_LOCATION_TITLE);
		this.appendDummyInput()
			.appendField("Latitude=");
		this.appendValueInput('lat')
					.setCheck('Number');
		this.appendDummyInput()
			.appendField("Longitude=");
		this.appendValueInput('lng')
					.setCheck('Number');
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(300);
		this.setTooltip(Blockly.Msg.UTU_NOI_LOCATION_TOOLTIP);
		this.setHelpUrl(Blockly.MsgUTU_NOI_LOCATION_HELPURL);
	}
};