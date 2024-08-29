Blockly.Blocks['openkb_digital_read'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_digital_read",
			"message0": Blockly.Msg.OPENKB_DIGITAL_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "IN1", "32" ],
					[ "IN2", "33" ],
					[ "IN3", "34" ],
					[ "IN4", "35" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
				 	[ "17", "17" ]
				]
			}],
			"output": [
			  "Number",
			  "Boolean"
			],
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_DIGITAL_READ_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	}
};

Blockly.Blocks['openkb_digital_write'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_digital_write",
			"message0": Blockly.Msg.OPENKB_DIGITAL_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}, {
				"type": "input_value",
				"name": "value",
				"check": [
					"Number",
					"Boolean"
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_DIGITAL_WRITE_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="openkb_digital_write">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['openkb_analog_read'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_analog_read",
			"message0": Blockly.Msg.OPENKB_ANALOG_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "IN1", "32" ],
					[ "IN2", "33" ],
					[ "IN3", "34" ],
					[ "IN4", "35" ]
				]
			}],
			"output": [
				"Number",
				"Boolean"
			],
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_ANALOG_READ_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		  });
	}
};

Blockly.Blocks['openkb_analog_write'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_analog_write",
			"message0": Blockly.Msg.OPENKB_ANALOG_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}, {
				"type": "input_value",
				"name": "value",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_ANALOG_WRITE_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="openkb_analog_write">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1023</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['openkb_servo'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_servo",
			"message0": Blockly.Msg.OPENKB_SERVO_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}, {
				"type": "input_value",
				"name": "angle",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_SERVO_TOOLTIP,
			"helpUrl": ""
		});
	},
	xmlToolbox: function() {
		return `
		<block type="openkb_servo">
		  	<value name="angle">
				<shadow type="math_number">
					<field name="VALUE">90</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['openkb_servo_calibrate'] = {
	init: function() {
		this.jsonInit({
			"type": "openkb_servo_calibrate",
			"message0": Blockly.Msg.OPENKB_SERVO_CALIBRATE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]
				]
			}, {
				"type": "field_number",
				"name": "min",
				"value": 0,
				"min": 0,
				"max": 20,
				"precision": 0
			}, {
				"type": "field_number",
				"name": "max",
				"value": 0,
				"min": 0,
				"max": 20,
				"precision": 0
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.OPENKB_SERVO_CALIBRATE_TOOLTIP,
			"helpUrl": ""
		});
	}
};
