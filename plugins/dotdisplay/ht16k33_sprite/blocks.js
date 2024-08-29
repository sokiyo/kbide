Blockly.Blocks["basic_led16x8_sprite"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.BASIC_LED16X8_DOT_TITLE)
			.appendField("                                ")
			.appendField(new Blockly.FieldImage("/icons/shift_left_24px.svg", 24, 24, "*", function(e) {
				for (var y = 0; y < 8; y++) {
					for (var x = 0; x < 16; x++) {
						if (x != 15) {
							var val = e.sourceBlock_.getFieldValue('POS_X' + (x + 1) + '_Y' + y);
							e.sourceBlock_.setFieldValue(val, 'POS_X' + x + '_Y' + y);
						} else {
							e.sourceBlock_.setFieldValue('false', 'POS_X' + x + '_Y' + y);
						}
					}
				}
			}, true))
			.appendField(new Blockly.FieldImage("/icons/shift_right_24px.svg", 24, 24, "*", function(e) {
				for (var y = 0; y < 8; y++) {
					for (var x = 15; x >= 0; x--) {
						if (x != 0) {
							var val = e.sourceBlock_.getFieldValue('POS_X' + (x - 1) + '_Y' + y);
							e.sourceBlock_.setFieldValue(val, 'POS_X' + x + '_Y' + y);
						} else {
							e.sourceBlock_.setFieldValue('false', 'POS_X' + x + '_Y' + y);
						}
					}
				}
			}, true))
			.appendField(new Blockly.FieldImage("/icons/shift_up_24px.svg", 24, 24, "*", function(e) {
				for (var y = 7; y >= 0; y--) {
					for (var x = 0; x < 16; x++) {
						if (y != 0) {
							var val = e.sourceBlock_.getFieldValue('POS_X' + x + '_Y' + (y - 1));
							e.sourceBlock_.setFieldValue(val, 'POS_X' + x + '_Y' + y);
						} else {
							e.sourceBlock_.setFieldValue('false', 'POS_X' + x + '_Y' + y);
						}
					}
				}
			}, true))
			.appendField(new Blockly.FieldImage("/icons/shift_down_24px.svg", 24, 24, "*", function(e) {
				for (var y = 0; y < 8; y++) {
					for (var x = 0; x < 16; x++) {
						if (y != 7) {
							var val = e.sourceBlock_.getFieldValue('POS_X' + x + '_Y' + (y + 1));
							e.sourceBlock_.setFieldValue(val, 'POS_X' + x + '_Y' + y);
						} else {
							e.sourceBlock_.setFieldValue('false', 'POS_X' + x + '_Y' + y);
						}
					}
				}
			}, true));

		for (var y = 7; y >= 0; y--) {
			var line = this.appendDummyInput();
			for (var x = 0; x < 16; x++) {
				line.appendField(new Blockly.FieldCheckbox('false', null, true), 'POS_X' + x + '_Y' + y);
			}
		}
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(basic_colour);
		this.setTooltip(Blockly.Msg.BASIC_LED16X8_DOT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.BASIC_LED16X8_DOT_HELPURL);
	}
};

Blockly.Blocks["basic_led16x8_clr_sprite"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.BASIC_LED16X8_CLR_DOT_TITLE);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(basic_colour);
		this.setTooltip(Blockly.Msg.BASIC_LED16X8_CLR_DOT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.BASIC_LED16X8_CLR_DOT_HELPURL);
	}
};

Blockly.Blocks["led16x8.dot"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LED16X8_DOT_TITLE);

		var x = [];
		var y = [];
		for (var i = 0;i < 16; i++) {
			x.push([String(i), String(i)]);
		}
		for (var i = 0;i < 8; i++) {
			y.push([String(i), String(i)]);
		}
		this.appendDummyInput()
			.appendField("X=")
			.appendField(new Blockly.FieldDropdown(x), 'X');
		this.appendDummyInput()
			.appendField("Y=")
			.appendField(new Blockly.FieldDropdown(y), 'Y');

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TYPE_PLOT, "0"],
				[Blockly.Msg.TYPE_UNPLOT, "1"],
				[Blockly.Msg.TYPE_TOGGLE, "2"],
				[Blockly.Msg.TYPE_BAR, "3"]
			]), 'TYPE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.LED16X8_DOT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.LED16X8_DOT_HELPURL);
	}
};

Blockly.Blocks["led16x8.dot_var"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LED16X8_DOT_TITLE);
		this.appendDummyInput()
			.appendField("X=");
		this.appendValueInput('X')
					.setCheck('Number');
		this.appendDummyInput()
			.appendField("Y=");
		this.appendValueInput('Y')
					.setCheck('Number');

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TYPE_PLOT, "0"],
				[Blockly.Msg.TYPE_UNPLOT, "1"],
				[Blockly.Msg.TYPE_TOGGLE, "2"],
				[Blockly.Msg.TYPE_BAR, "3"]
			]), 'TYPE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.LED16X8_DOT_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.LED16X8_DOT_HELPURL);
	}
};

Blockly.Blocks["led16x8.dot_move"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LED16X8_MOVE_TITLE);

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TYPE_ROTATE, "0"],
				[Blockly.Msg.TYPE_SHIFT, "1"]
			]), 'MOVE');

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TYPE_RIGHT, "0"],
				[Blockly.Msg.TYPE_LEFT, "1"]
			]), 'TYPE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.LED16X8_MOVE_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.LED16X8_MOVE_HELPURL);
	}
};

Blockly.Blocks["led16x8.dot_stack"] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.LED16X8_DOT_STACK_TITLE);
		this.appendDummyInput()
			.appendField("X=");
		this.appendValueInput('X')
					.setCheck('Number');
		this.appendDummyInput()
			.appendField("Y=");
		this.appendValueInput('Y')
					.setCheck('Number');

		this.appendDummyInput()
			.appendField(Blockly.Msg.TYPE)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Msg.TYPE_PLOT, "0"],
				[Blockly.Msg.TYPE_UNPLOT, "1"],
			]), 'TYPE');

		this.setInputsInline(true);
		this.setPreviousStatement(true);
		this.setNextStatement(true);
		this.setColour(160);
		this.setTooltip(Blockly.Msg.LED16X8_DOT_STACK_TOOLTIP);
		this.setHelpUrl(Blockly.Msg.LED16X8_DOT_STACK_HELPURL);
	}
};
