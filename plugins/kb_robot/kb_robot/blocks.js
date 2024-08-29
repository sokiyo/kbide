
Blockly.Blocks['kb_robot_motor'] = {
	init: function() {
	  	this.appendDummyInput()
			.appendField("Set Motor Speed % ")

	  	this.appendValueInput("M1")
			.setCheck("Number")
			.appendField("Motor 1");

	  	this.appendValueInput("M2")
			.setCheck("Number")
			.appendField("Motor 2");

		this.appendValueInput("M3")
			.setCheck("Number")
			.appendField("Motor 3");
		  
		this.appendValueInput("M4")
			.setCheck("Number")
			.appendField("Motor 4");

		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(135);
	this.setTooltip("number input range -100 to 100  center 0 ");
	this.setHelpUrl("");
	}
};

Blockly.Blocks['kb_robot_servo'] = {
	init: function() {
	  	this.appendDummyInput()
			.appendField("Set Servo microSecond")

	  	this.appendValueInput("M1")
			.setCheck("Number")
			.appendField("Servo 1");

	  	this.appendValueInput("M2")
			.setCheck("Number")
			.appendField("Servo 2");

		this.appendValueInput("M3")
			.setCheck("Number")
			.appendField("Servo 3");
		  
		this.appendValueInput("M4")
			.setCheck("Number")
			.appendField("Servo 4");

		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(135);
	this.setTooltip("number input range -100 to 100  center 0 ");
	this.setHelpUrl("");
	}
};

Blockly.Blocks['kb_robot_machanum'] = {
	init: function() {
	  	this.appendDummyInput()
			.appendField("Set Machanum Speed")

	  	this.appendValueInput("V1")
			.setCheck("Number")
			.appendField("Velocity X");

	  	this.appendValueInput("V2")
			.setCheck("Number")
			.appendField("Velocity Y");

		this.appendValueInput("V3")
			.setCheck("Number")
			.appendField("Velocity Z"); 

		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(135);
	this.setTooltip("number input range -100 to 100  center 0 ");
	this.setHelpUrl("");
	}
};

Blockly.Blocks['kb_robot_str'] = {
	init: function() {
		this.appendDummyInput()
			.appendField("Spit 6 Data From Text")
			
		this.appendValueInput("data")
			.setCheck("")
			.appendField("");

	  this.setInputsInline(true);
	  this.setPreviousStatement(true, null);
	  this.setNextStatement(true, null);
	  this.setColour(135);
   this.setTooltip("");
   this.setHelpUrl("");
	}
  };

  Blockly.Blocks['kb_robot_getdata'] = {
	init: function() {
		// adc channel
		this.appendDummyInput()
			.appendField(' Read data from Text')
			.appendField(new Blockly.FieldDropdown([
				["data 1", "0"],
				["data 2", "1"],
				["data 3", "2"],
				["data 4", "3"],
				["data 5", "4"],
				["data 6", "5"]
			]), 'AIN');

		this.setOutput(true, 'Number');
		this.setInputsInline(true);
		this.setPreviousStatement(false);
		this.setNextStatement(false);
		this.setColour(58);
   this.setTooltip("");
   this.setHelpUrl("");
	}
};