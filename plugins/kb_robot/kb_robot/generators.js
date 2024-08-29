
Blockly.JavaScript['kb_robot_motor'] = function (block) {
	var value_m1 = Blockly.JavaScript.valueToCode(block, 'M1', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m2 = Blockly.JavaScript.valueToCode(block, 'M2', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m3 = Blockly.JavaScript.valueToCode(block, 'M3', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m4 = Blockly.JavaScript.valueToCode(block, 'M4', Blockly.JavaScript.ORDER_ATOMIC);
	// TODO: Assemble JavaScript into code variable.
	var code = `
	{
		DEV_I2C1.KB_ROBOT(0, 0).robot_mode = 0;
		DEV_I2C1.KB_ROBOT(0, 0).wdt_feed();
		DEV_I2C1.KB_ROBOT(0, 0).motor[0] = (${value_m1});
		DEV_I2C1.KB_ROBOT(0, 0).motor[1] = (${value_m2});
		DEV_I2C1.KB_ROBOT(0, 0).motor[2] = (${value_m3});
		DEV_I2C1.KB_ROBOT(0, 0).motor[3] = (${value_m4});
	}
      \n
      `;
	return code;
};

Blockly.JavaScript['kb_robot_servo'] = function (block) {
	var value_m1 = Blockly.JavaScript.valueToCode(block, 'M1', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m2 = Blockly.JavaScript.valueToCode(block, 'M2', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m3 = Blockly.JavaScript.valueToCode(block, 'M3', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m4 = Blockly.JavaScript.valueToCode(block, 'M4', Blockly.JavaScript.ORDER_ATOMIC);
	// TODO: Assemble JavaScript into code variable.
	var code = `
	{
		DEV_I2C1.KB_ROBOT(0, 0).robot_mode = 0;
		DEV_I2C1.KB_ROBOT(0, 0).wdt_feed();
		DEV_I2C1.KB_ROBOT(0, 0).servo[0] = (${value_m1});
		DEV_I2C1.KB_ROBOT(0, 0).servo[1] = (${value_m2});
		DEV_I2C1.KB_ROBOT(0, 0).servo[2] = (${value_m3});
		DEV_I2C1.KB_ROBOT(0, 0).servo[3] = (${value_m4});
	}
      \n
      `;
	return code;
};

Blockly.JavaScript['kb_robot_machanum'] = function (block) {
	var value_m1 = Blockly.JavaScript.valueToCode(block, 'V1', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m2 = Blockly.JavaScript.valueToCode(block, 'V2', Blockly.JavaScript.ORDER_ATOMIC);
	var value_m3 = Blockly.JavaScript.valueToCode(block, 'V3', Blockly.JavaScript.ORDER_ATOMIC);
	// TODO: Assemble JavaScript into code variable.
	var code = `
	{
		DEV_I2C1.KB_ROBOT(0, 0).robot_mode = 1;
		DEV_I2C1.KB_ROBOT(0, 0).wdt_feed();
		DEV_I2C1.KB_ROBOT(0, 0).mac_v[0] = (${value_m1});
		DEV_I2C1.KB_ROBOT(0, 0).mac_v[1] = (${value_m2});
		DEV_I2C1.KB_ROBOT(0, 0).mac_v[2] = (${value_m3});
	}
      \n
      `;
	return code;
};

Blockly.JavaScript['kb_robot_str'] = function (block) {
	var value = Blockly.JavaScript.valueToCode(block, 'data', Blockly.JavaScript.ORDER_ATOMIC);

	// TODO: Assemble JavaScript into code variable.
	var code = `
		DEV_I2C1.KB_ROBOT(0, 0).spit_data(${value});
      \n
      `;
	return code;
};

Blockly.JavaScript['kb_robot_getdata'] = function (block) {
	
	var value = block.getFieldValue('AIN');

	// TODO: Assemble JavaScript into code variable.
	var code = 'DEV_I2C1.KB_ROBOT(0, 0).data['+value+']';
	return [code,Blockly.JavaScript.ORDER_ATOMIC];
};
