Blockly.Blocks['hx711.read'] = {
  init: function () {
    this.appendDummyInput()
      .appendField(Blockly.Msg.READ);
    this.setOutput(true, null);
    this.setColour(160);
    this.setTooltip(Blockly.Msg.READ_TOOLTIP);
    this.setHelpUrl("");
  }
};

Blockly.Blocks['get_units'] = {
  init: function () {
    this.appendDummyInput()
      .appendField(Blockly.Msg.UNIT);
    this.setOutput(true, null);
    this.setColour(160);
    this.setTooltip(Blockly.Msg.UNIT_TOOLTIP);
    this.setHelpUrl("");
  }
};

Blockly.Blocks['set_weight'] = {
  init: function () {
    this.appendValueInput("number")
      .setCheck("Number")
      .appendField(Blockly.Msg.SET_WEIGHT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip(Blockly.Msg.SET_WEIGHT_TOOLTIP);
    this.setHelpUrl("");
  }
};

Blockly.Blocks['set_offset'] = {
  init: function () {
    this.appendValueInput("number")
      .setCheck("Number")
      .appendField(Blockly.Msg.OFFSET);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(230);
    this.setTooltip(Blockly.Msg.OFFSET_TOOLTIP);
    this.setHelpUrl("");
  }
};

Blockly.Blocks['tare'] = {
  init: function () {
    this.appendDummyInput()
      .appendField(Blockly.Msg.TARE);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(160);
    this.setTooltip(Blockly.Msg.TARE_TOOLTIP);
    this.setHelpUrl("");
  }
};

Blockly.Blocks['calibrate'] = {
  init: function () {
    this.appendDummyInput()
      .appendField(Blockly.Msg.CAL);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(160);
    this.setTooltip(Blockly.Msg.CAL_TOOLTIP);
    this.setHelpUrl("");
  }
};