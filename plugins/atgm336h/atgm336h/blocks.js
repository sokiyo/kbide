Blockly.Blocks["atgm336h.latitude"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_LATITUDE_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_LATITUDE_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_LATITUDE_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.longitude"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_LONGITUDE_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_LONGITUDE_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_LONGITUDE_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.year"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_YEAR_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_YEAR_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_YEAR_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.month"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_MONTH_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_MONTH_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_MONTH_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.day"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_DAY_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_DAY_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_DAY_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.hour"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_HOUR_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_HOUR_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_HOUR_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.minute"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_MINUTE_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_MINUTE_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_MINUTE_TEXT_HELPURL);
	}
};

Blockly.Blocks["atgm336h.second"] = {
	init: function () {
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_GET_SECOND_TEXT_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_TX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'TX');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.atgm336h_RX)
			.appendField(new Blockly.FieldDropdown([
				["IO18", "GPIO_NUM_18"],
				["IO19", "GPIO_NUM_19"]
			]), 'RX');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.atgm336h_GET_SECOND_TEXT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.atgm336h_GET_SECOND_TEXT_HELPURL);
	}
};
