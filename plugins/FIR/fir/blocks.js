var firebase_icon = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAACXBIWXMAAAsTAAALEwEAmpwYAAAFN2lUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNS42LWMxNDAgNzkuMTYwNDUxLCAyMDE3LzA1LzA2LTAxOjA4OjIxICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp0aWZmPSJodHRwOi8vbnMuYWRvYmUuY29tL3RpZmYvMS4wLyIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0RXZ0PSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VFdmVudCMiIHRpZmY6T3JpZW50YXRpb249IjEiIHhtcDpDcmVhdGVEYXRlPSIyMDE5LTA5LTA0VDIyOjI4KzA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAxOS0wOS0wNFQyMjoyOTowNSswNzowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAxOS0wOS0wNFQyMjoyOTowNSswNzowMCIgZGM6Zm9ybWF0PSJpbWFnZS9wbmciIHBob3Rvc2hvcDpDb2xvck1vZGU9IjMiIHBob3Rvc2hvcDpJQ0NQcm9maWxlPSJzUkdCIElFQzYxOTY2LTIuMSIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo2MTgz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"
var key_firebase_icon = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAYAAABzenr0AAAACXBIWXMAAAsTAAALEwEAmpwYAAAFOmlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNS42LWMxNDAgNzkuMTYwNDUxLCAyMDE3LzA1LzA2LTAxOjA4OjIxICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp0aWZmPSJodHRwOi8vbnMuYWRvYmUuY29tL3RpZmYvMS4wLyIgeG1sbnM6eG1wPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvIiB4bWxuczpkYz0iaHR0cDovL3B1cmwub3JnL2RjL2VsZW1lbnRzLzEuMS8iIHhtbG5zOnBob3Rvc2hvcD0iaHR0cDovL25zLmFkb2JlLmNvbS9waG90b3Nob3AvMS4wLyIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0RXZ0PSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VFdmVudCMiIHRpZmY6T3JpZW50YXRpb249IjEiIHhtcDpDcmVhdGVEYXRlPSIyMDE5LTA4LTMwVDE3OjMwOjI3KzA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAxOS0wOS0wNFQyMjoyNjo0MCswNzowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAxOS0wOS0wNFQyMjoyNjo0MCswNzowMCIgZGM6Zm9ybWF0PSJpbWFnZS9wbmciIHBob3Rvc2hvcDpDb2xvck1vZGU9IjMiIHBob3Rvc2hvcDpJQ0NQcm9maWxlPSJzUkdCIElFQzYxOTY2LTIuMSIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDo1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";

// https://www.shareicon.net/download/2016/07/08/117547_developer.ico
// http://www.myiconfinder.com/uploads/iconsets/256-256-87cc0576629f9e533cd1d331fd98d8bc.png

Blockly.Blocks['FIR.begin'] = {
    init: function () {
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "firebase_icon"));
        this.appendDummyInput()
            .appendField(Blockly.Msg.FIR_TEXT_CONNECT);
        this.appendDummyInput()
            .appendField(new Blockly.FieldTextInput("https://DATABASE_NAME.firebaseio.com/"), "HOST");
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(key_firebase_icon, 20, 20, "key_icon"));
        this.appendDummyInput()
            .appendField(new Blockly.FieldTextInput("SECRET_KEY"), "KEY");
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_CONNECT_TOOLTIP);
        this.setHelpUrl("");
    }
};

Blockly.Blocks['FIR.get_string'] = {
    init: function () {
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"));
        this.appendDummyInput()
            .appendField(Blockly.Msg.FIR_TEXT_GET);
        this.appendValueInput("PATH")
            .setCheck("String");
        this.setInputsInline(true);
        this.setOutput(true, "String");
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_GET_TOOLTIP);
        this.setHelpUrl("");
    },
    xmlToolbox: function () {
        return $(document.createElement('block')).attr({
            type: 'FIR.get_string'
        }).append('\
		<value name="PATH">\
			<shadow type="basic_string">\
				<field name="VALUE">PATH</field>\
			</shadow>\
		</value>\
		');
    }
};

Blockly.Blocks['FIR.set'] = {
    init: function () {
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"));
        this.appendDummyInput()
            .appendField(Blockly.Msg.FIR_TEXT_SET_ONE);
        this.appendDummyInput()
        this.appendValueInput("DATA")
        this.appendValueInput("PATH")
            .appendField(Blockly.Msg.FIR_TEXT_SET_TWO)
            .setCheck("String");
        // .setCheck("String");
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_SET_TOOLTIP);
        this.setHelpUrl("");
    },
    xmlToolbox: function () {
        return $(document.createElement('block')).attr({
            type: 'FIR.set'
        }).append('\
		<value name="PATH">\
			<shadow type="basic_string">\
				<field name="VALUE">PATH</field>\
			</shadow>\
		</value>\
		');
    }
};

Blockly.Blocks['FIR.delete'] = {
    init: function () {
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"));
        this.appendDummyInput()
            .appendField(Blockly.Msg.FIR_TEXT_DELETE);
        this.appendValueInput("PATH")
            .setCheck("String");
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_DELETE_TOOLTIP);
        this.setHelpUrl("");
    },
    xmlToolbox: function () {
        return $(document.createElement('block')).attr({
            type: 'FIR.delete'
        }).append('\
		<value name="PATH">\
			<shadow type="basic_string">\
				<field name="VALUE">PATH</field>\
			</shadow>\
		</value>\
		');
    }
};

// Blockly.Blocks['FIR.stream'] = {
//   init: function() {
//     this.appendDummyInput()
//         .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"));
//     this.appendDummyInput()
//         .appendField("Steam text at");
//     this.appendValueInput("PATH")
//         .setCheck("String");
//     this.setInputsInline(true);
//     this.setPreviousStatement(true, null);
//     this.setNextStatement(true, null);
//     this.setColour(0);
//  this.setTooltip("");
//  this.setHelpUrl("");
//   }
// };

Blockly.Blocks["FIR.onvalue"] = {
    init: function () {
        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"))
            .appendField(Blockly.Msg.FIR_TEXT_ON_CHANGE_ONE);

        this.appendDummyInput()
            .appendField(new Blockly.FieldTextInput("PATH"), "PATH");

        this.appendStatementInput("DO")
            .appendField(Blockly.Msg.FIR_TEXT_ON_CHANGE_TWO);

        this.setInputsInline(true);
        this.setPreviousStatement(false);
        this.setNextStatement(false);
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_ON_CHANGE_TOOLTIP);
        this.setHelpUrl("");
    }
};

Blockly.Blocks["FIR.value_text"] = {
    init: function () {

        this.appendDummyInput()
            .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"))
            .appendField(Blockly.Msg.FIR_TEXT_CACHED)

        this.appendValueInput("PATH")
            .setCheck("String");

        this.setOutput(true, 'String');
        this.setInputsInline(true);
        this.setPreviousStatement(false);
        this.setNextStatement(false);
        this.setColour(0);
        this.setTooltip(Blockly.Msg.FIR_TEXT_CACHED_TOOLTIP);
        this.setHelpUrl("");
    },
    xmlToolbox: function () {
        return $(document.createElement('block')).attr({
            type: 'FIR.value_text'
        }).append('\
		<value name="PATH">\
			<shadow type="basic_string">\
				<field name="VALUE">PATH</field>\
			</shadow>\
		</value>\
		');
    }
};

Blockly.Blocks["FIR.convert"] = {
    init: function () {

        this.appendDummyInput()
            // .appendField(new Blockly.FieldImage(firebase_icon, 20, 20, "*"))
            .appendField(Blockly.Msg.FIR_TEXT_CONVERT_ONE)
        this.appendValueInput("DATA")
            .setCheck("String");
        this.appendDummyInput()
            .appendField(Blockly.Msg.FIR_TEXT_CONVERT_TWO)


        this.setOutput(true, 'Number');
        this.setInputsInline(true);
        this.setPreviousStatement(false);
        this.setNextStatement(false);
        this.setColour(10);
        this.setTooltip(Blockly.Msg.FIR_TEXT_CONVERT_TOOLTIP);
        this.setHelpUrl("");
    },
    // xmlToolbox: function() {
    // 	return $(document.createElement('block')).attr({
    // 	type: 'FIR.convert'
    // }).append('\
    // <value name="DATA">\
    // 	<shadow type="basic_string">\
    // 	</shadow>\
    // </value>\
    // ');
    // }
};

Blockly.Blocks['FIR.concat'] = {
    init: function () {
        this.appendValueInput("LEFT")
            .setCheck(null);
        this.appendDummyInput()
            .appendField("+");
        this.appendValueInput("RIGHT")
            .setCheck(null);
        this.setInputsInline(true);
        this.setOutput(true, "String");
        this.setColour(135);
        this.setTooltip(Blockly.Msg.FIR_TEXT_CONCAT_TOOLTIP);
        this.setHelpUrl("");
    },
    xmlToolbox: function () {
        return $(document.createElement('block')).attr({
            type: 'FIR.concat'
        }).append('\
		<value name="LEFT">\
			<shadow type="basic_string">\
			</shadow>\
		</value>\
		<value name="RIGHT">\
			<shadow type="basic_string">\
			</shadow>\
		</value>\
		');
    }
};
