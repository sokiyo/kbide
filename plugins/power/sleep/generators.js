Blockly.JavaScript['sleep.deep_wakeup'] = function(block) {
	var button_wakeup_checkbox = block.getFieldValue('BUTTON_WAKEUP_CHECKBOX');
	var timeout_wakeup_checkbox = block.getFieldValue('TIMEOUT_WAKEUP_CHECKBOX');
	var wakeup_gpio = block.getFieldValue('WAKEUP_GPIO');
	var wakeup_timeout = parseInt(1000 * parseFloat(block.getFieldValue('WAKEUP_TIMEOUT')));

	console.log(button_wakeup_checkbox);
	console.log(timeout_wakeup_checkbox);

	if ((button_wakeup_checkbox == 'TRUE') && (timeout_wakeup_checkbox == 'TRUE')) {
		return 'DEV_IO.SLEEP().deep_gpio_timeout(' + wakeup_gpio + ', ' + wakeup_timeout + ');\n';
	}
	else
	if (button_wakeup_checkbox == 'TRUE') {
		return 'DEV_IO.SLEEP().deep_gpio(' + wakeup_gpio + ');\n';
	}
	else
	if (timeout_wakeup_checkbox == 'TRUE') {
		return 'DEV_IO.SLEEP().deep_timeout(' + wakeup_timeout + ');\n';
	}	
	
	return '\n';
};
