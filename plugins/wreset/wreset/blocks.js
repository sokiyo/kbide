Blockly.Blocks["wreset.start"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.WRESET_START_TITLE);
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(324);
		this.setTooltip(Blockly.Msg.WRESET_START_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.WRESET_START_HELPURL);
	}
};

Blockly.Blocks["wreset.startwdt"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.WRESET_STARTWDT_TITLE);
		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(209);
		this.setTooltip(Blockly.Msg.WRESET_STARTWDT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.WRESET_STARTWDT_HELPURL);
	}
};
