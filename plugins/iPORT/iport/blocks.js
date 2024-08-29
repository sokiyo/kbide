Blockly.Blocks['iport_digital_write'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_digital_write",
			"message0": Blockly.Msg.IPORT_DIGITAL_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					/* [ "DAC1", "25" ], */
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					/* [ "17", "17" ] */
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
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_DIGITAL_WRITE_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="iport_digital_write">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['iport_digital_read'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_digital_read",
			"message0": Blockly.Msg.IPORT_DIGITAL_READ_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "IN1", "32" ],
					[ "IN2", "33" ],
					[ "IN3", "34" ],
					[ "IN4", "35" ],
					/* [ "DAC1", "25" ], */
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
				 	/* [ "17", "17" ] */
				]
			}],
			"output": [
			  "Number",
			  "Boolean"
			],
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_DIGITAL_READ_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	}
};

Blockly.Blocks['iport_analog_read'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_analog_read",
			"message0": Blockly.Msg.IPORT_ANALOG_READ_MESSAGE,
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
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_ANALOG_READ_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		  });
	}
};

Blockly.Blocks['iport_analog_write'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_analog_write",
			"message0": Blockly.Msg.IPORT_ANALOG_WRITE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					/* [ "DAC1", "25" ], */
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					/* [ "17", "17" ] */
				]
			}, {
				"type": "input_value",
				"name": "value",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_ANALOG_WRITE_TOOLTIP,
			"helpUrl": "https://www.inex.co.th/"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="iport_analog_write">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1023</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['iport_servo'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_servo",
			"message0": Blockly.Msg.IPORT_SERVO_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "SERVO1", "15" ],
					[ "SERVO2", "17" ],
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					/*[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]*/
				]
			}, {
				"type": "input_value",
				"name": "angle",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_SERVO_TOOLTIP,
			"helpUrl": ""
		});
	},
	xmlToolbox: function() {
		return `
		<block type="iport_servo">
		  	<value name="angle">
				<shadow type="math_number">
					<field name="VALUE">90</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['iport_servo_calibrate'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_servo_calibrate",
			"message0": Blockly.Msg.IPORT_SERVO_CALIBRATE_MESSAGE,
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "SERVO1", "15" ],
					[ "SERVO2", "17" ],
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					/*[ "DAC1", "25" ],
					[ "18", "18" ],
					[ "19", "19" ],
					[ "23", "23" ],
					[ "17", "17" ]*/
				]
			}, {
				"type": "field_number",
				"name": "min",
				"value": 0.5,
				"min": 0,
				"max": 20,
				"precision": 0
			}, {
				"type": "field_number",
				"name": "max",
				"value": 2.5,
				"min": 0,
				"max": 20,
				"precision": 0
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_SERVO_CALIBRATE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['iport_write_usb'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_write_usb",
			"message0": Blockly.Msg.IPORT_USB_WRITE_MESSAGE,
			"args0": [
			  {
				"type": "field_dropdown",
				"name": "value",
				"options": [
				  [
					Blockly.Msg.IPORT_USB_WRITE_ON_MESSAGE,
					"1"
				  ],
				  [
					Blockly.Msg.IPORT_USB_WRITE_OFF_MESSAGE,
					"0"
				  ]
				]
			  }
			],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_USB_WRITE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['iport_toggle_usb'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_toggle_usb",
			"message0": Blockly.Msg.IPORT_USB_TOGGLE_MESSAGE,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_USB_TOGGLE_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['iport_read_usb'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_read_usb",
			"message0": Blockly.Msg.IPORT_USB_READ_MESSAGE,
			"output": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_USB_READ_TOOLTIP,
			"helpUrl": ""
		});
	}
};

Blockly.Blocks['iport_analog_write_usb'] = {
	init: function() {
		this.jsonInit({
			"type": "iport_analog_write_usb",
			"message0": Blockly.Msg.IPORT_USB_ANALOG_WRITE_MESSAGE,
			"args0": [
			  {
				"type": "input_value",
				"name": "value",
				"check": "Number"
			  }
			],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 120,
			"tooltip": Blockly.Msg.IPORT_USB_ANALOG_WRITE_TOOLTIP,
			"helpUrl": ""
		});
	},
	xmlToolbox: function() {
		return `
		<block type="iport_analog_write_usb">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1023</field>
				</shadow>
			</value>
		</block>
		`;
	}
};