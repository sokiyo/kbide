Blockly.JavaScript['atgm336h.latitude'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_lat()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.longitude'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_lng()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.year'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_year()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.month'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_month()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.day'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_day()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.hour'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_hour()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.minute'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_minute()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};

Blockly.JavaScript['atgm336h.second'] = function (block) {
	return [
		'DEV_IO.atgm336h(' + block.getFieldValue('TX') + ', ' + block.getFieldValue('RX') + ').get_second()',
		Blockly.JavaScript.ORDER_ATOMIC
	];
};