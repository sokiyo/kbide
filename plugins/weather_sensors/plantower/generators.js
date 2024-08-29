Blockly.JavaScript['plantower.getpm2_5'] = function (block) {
	return [
		'DEV_IO.PLANTOWER(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_pm2_5()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['plantower.getpm10'] = function (block) {
	return [
		'DEV_IO.PLANTOWER(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_pm10()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['plantower.is_error'] = function (block) {
	return [
		'DEV_IO.PLANTOWER(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').is_error()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

// Blockly.JavaScript['plantower.get_error_count'] = function (block) {
// 	return [
// 		'DEV_IO.PLANTOWER(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_error_count()',
// 		Blockly.JavaScript.ORDER_ATOMIC
// 	];
// };

// Blockly.JavaScript['plantower.get_error_clear_count'] = function (block) {
// 	return [
// 		'DEV_IO.PLANTOWER(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_error_clear_count()',
// 		Blockly.JavaScript.ORDER_ATOMIC
// 	];
// };
