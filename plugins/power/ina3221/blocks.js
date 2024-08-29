Blockly.Blocks["ina3221.get_voltage"] = {
	init: function() {		
		this.appendDummyInput()	
			.appendField("INA3221");

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.ADDRESS)
			.appendField(new Blockly.FieldDropdown([
				["0x40", "64"],
				["0x41", "65"],
				["0x42", "66"],
				["0x43", "67"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.INA3221_GET_VOLTAGE_TITLE);

		// ina3221 channel
		this.appendDummyInput()
			.appendField(Blockly.Msg.INA3221_CH)
			.appendField(new Blockly.FieldDropdown([
				["1", "0"],
				["2", "1"],
				["3", "2"]
			]), 'INA3221_CH');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.INA3221_GET_VOLTAGE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.INA3221_GET_VOLTAGE_HELPURL);
	}
};

Blockly.Blocks["ina3221.get_current"] = {
	init: function() {
		this.appendDummyInput()
			.appendField('INA3221');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.ADDRESS)
			.appendField(new Blockly.FieldDropdown([
				["0x40", "64"],
				["0x41", "65"],
				["0x42", "66"],
				["0x43", "67"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.INA3221_GET_CURRENT_TITLE);

		// ina3221 channel
		this.appendDummyInput()
			.appendField(Blockly.Msg.INA3221_CH)
			.appendField(new Blockly.FieldDropdown([
				["1", "0"],
				["2", "1"],
				["3", "2"]
			]), 'INA3221_CH');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.INA3221_GET_CURRENT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.INA3221_GET_CURRENT_HELPURL);		
	}
};

Blockly.Blocks["ina3221.set_shunt_resistor"] = {
	init: function() {
		this.appendDummyInput()
			.appendField('INA3221');

		// device addess
		this.appendDummyInput()
			.appendField(Blockly.Msg.ADDRESS)
			.appendField(new Blockly.FieldDropdown([
				["0x40", "64"],
				["0x41", "65"],
				["0x42", "66"],
				["0x43", "67"]
			]), 'ADDRESS');

		this.appendDummyInput()
			.appendField(Blockly.Msg.INA3221_SHUNT_RESISTOR_TITLE)			
			.appendField(Blockly.Msg.INA3221_CH)
			.appendField(new Blockly.FieldDropdown([
				["1", "0"],
				["2", "1"],
				["3", "2"]
			]), 'INA3221_CH')
			.appendField(new Blockly.FieldNumber(100, 1, 1000, 1), 'SHUNT_RESISTOR') // default, min, max, step
			.appendField(Blockly.Msg.INA3221_MILLI_OHM_TITLE)

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(58);
		this.setTooltip(Blockly.Msg.INA3221_GET_CURRENT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.INA3221_GET_CURRENT_HELPURL);		
	}
};
