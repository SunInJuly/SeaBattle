import QtQuick 2.0

Rectangle {
	id: main
	width: parent.width
	height: parent.height
	color: "transparent"
	// сигналы для внешнего мира :)
	signal vsAiClicked()
	signal vsPlayerClicked()
	signal settingsClicked()
	signal quitClicked()

	function at(){
		console.log("signal from start Menu")
	}


	Component.onCompleted: {
		main.vsAiClicked.connect(at)
	}

	Menu {
		id: menu

		width: parent.width
		height: parent.height

		topShipButtonType: 0
		bottomShipButtonType: 1
		leftBombButtonType: 0
		rightBombButtonType: 1

		Component.onCompleted: {
			menu.topShipButton.clicked.connect(vsAiClicked)
			menu.bottomShipButton.clicked.connect(vsPlayerClicked)
			menu.leftBombButton.clicked.connect(settingsClicked)
			menu.rightBombButton.clicked.connect(quitClicked)
		}
	}

}
