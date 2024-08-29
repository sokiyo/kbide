Blockly.Blocks["mjoystick.get_raw_position"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_GET_RAW_POSITION_TITLE)
			.appendField(Blockly.Msg.MJOYSTICK_GET_RAW_POSITION_AXIS)
			.appendField(new Blockly.FieldDropdown([
				["x", "0"],
				["y", "1"]
			]), 'AXIS')

		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MJOYSTICK_GET_RAW_POSITION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_GET_RAW_POSITION_HELPURL);
	}
};

Blockly.Blocks["mjoystick.get_position"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_GET_POSITION_TITLE)
			.appendField(Blockly.Msg.MJOYSTICK_GET_RAW_POSITION_AXIS)
			.appendField(new Blockly.FieldDropdown([
				["x", "0"],
				["y", "1"]
			]), 'AXIS')

		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MJOYSTICK_GET_POSITION_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_GET_POSITION_HELPURL);
	}
};



Blockly.Blocks["mjoystick.calibrate_set_x"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_X_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RAW);

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RELEASE);
		this.appendValueInput("RELEASE").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_LEFTMOST);
		this.appendValueInput("LEFTMOST").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RIGHTMOST);
		this.appendValueInput("RIGHTMOST").setCheck("Number");

		this.appendDummyInput()
		.appendField(Blockly.Msg.MJOYSTICK_RANGE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_LEFTMOST);
		this.appendValueInput("RANGE_LEFTMOST").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RIGHTMOST);
		this.appendValueInput("RANGE_RIGHTMOST").setCheck("Number");

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_X_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_X_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'mjoystick.calibrate_set_x'
		}).append('\
			<value name="RELEASE">\
				<shadow type="mjoystick.release_default">\
				</shadow>\
		   	</value>\
		   	<value name="LEFTMOST">\
				<shadow type="mjoystick.leftmost_default">\
				</shadow>\
		  	</value>\
		  	<value name="RIGHTMOST">\
				<shadow type="mjoystick.rightmost_default">\
				</shadow>\
			</value>\
			<value name="RANGE_LEFTMOST">\
				<shadow type="mjoystick.range_leftmost_default">\
				</shadow>\
	 		</value>\
	 		<value name="RANGE_RIGHTMOST">\
				<shadow type="mjoystick.range_rightmost_default">\
				</shadow>\
			</value>'
	   );
   }
};

Blockly.Blocks["mjoystick.calibrate_set_y"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_Y_TITLE);
		
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RAW);
		
		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RELEASE);
		this.appendValueInput("RELEASE").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_DOWNMOST);
		this.appendValueInput("DOWNMOST").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_UPMOST);
		this.appendValueInput("UPMOST").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_RANGE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_DOWNMOST);
		this.appendValueInput("RANGE_DOWNMOST").setCheck("Number");

		this.appendDummyInput()
			.appendField(Blockly.Msg.MJOYSTICK_UPMOST);
		this.appendValueInput("RANGE_UPMOST").setCheck("Number");

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_Y_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_CALIBRATE_SET_Y_HELPURL);
	},
	// custom xmlToolbox
	xmlToolbox: function() {
		return $(document.createElement('block')).attr({
			type: 'mjoystick.calibrate_set_y'
		}).append('\
			<value name="RELEASE">\
				<shadow type="mjoystick.release_default">\
				</shadow>\
		   	</value>\
		   	<value name="DOWNMOST">\
				<shadow type="mjoystick.downmost_default">\
				</shadow>\
		  	</value>\
		  	<value name="UPMOST">\
				<shadow type="mjoystick.upmost_default">\
				</shadow>\
		 	</value>\
			<value name="RANGE_DOWNMOST">\
				<shadow type="mjoystick.range_downmost_default">\
				</shadow>\
		   	</value>\
		   	<value name="RANGE_UPMOST">\
				<shadow type="mjoystick.range_upmost_default">\
				</shadow>\
		  	</value>'
	   );
   }
};

// hidden block (no generator defined), temporary used for shadow block
Blockly.Blocks["mjoystick.release_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(2047, 0, 4095, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_RELEASE_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_RELEASE_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.downmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(4095, 0, 4095, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_DOWNMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_DOWNMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.upmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(0, 0, 4095, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_UPMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_UPMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.leftmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(0, 0, 4095, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_LEFTMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_LEFTMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.rightmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(4095, 0, 4095, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_RIGHTMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_RIGHTMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.range_leftmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(0, 0, 180, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_LEFTMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_LEFTMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.range_rightmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(180, 0, 180, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_RIGHTMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_RIGHTMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.range_downmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(-100, -100, 100, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_DOWNMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_DOWNMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};

Blockly.Blocks["mjoystick.range_upmost_default"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(new Blockly.FieldNumber(100, -100, 100, 1), 'VALUE');
		this.setOutput(true, 'Number');
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(math_colour);
		this.setTooltip(Blockly.Msg.MJOYSTICK_UPMOST_DEFAULT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.MJOYSTICK_UPMOST_DEFAULT_HELPURL);
	},
	// custom xmlToolboxcolumn
	xmlToolbox: function() {
		return null; // hidden block
	}
};
