import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    // Переменная для отслеживания состояния виджета
    property bool isOpen: false

    // Панель, которая будет открываться и закрываться
    Rectangle {
        id: slider
        width: mainWindow.width / 3
        height: mainWindow.height
        color: "lightgray"
        anchors.top: parent.top
        // Изначально скрыт, устанавливаем x в закрытое состояние
        x: mainWindow.width

        // Кнопка внутри панели для закрытия
        Button {
            text: "Close"
            anchors.centerIn: parent
            onClicked: {
                console.log("Close button clicked")
                mainWindow.isOpen = false
                slideAnimation.to = mainWindow.width
                slideAnimation.start()
                triggerArea.visible = true
            }
        }
    }

    // Анимация для плавного перемещения
    NumberAnimation {
        id: slideAnimation
        target: slider
        property: "x"
        duration: 300
    }

    // Область для взаимодействия с пользователем
    Rectangle {
        id: triggerArea
        width: 40
        height: mainWindow.height
        color: "lightblue" // Временный цвет для видимости
        border.color: "darkblue" // Граница для видимости
        anchors.right: parent.right

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Trigger area clicked")
                triggerArea.visible = false
                mainWindow.isOpen = !mainWindow.isOpen

                if (mainWindow.isOpen) {
                    slideAnimation.to = mainWindow.width - slider.width
                } else {
                    slideAnimation.to = mainWindow.width
                }
                slideAnimation.start()
            }
        }
    }

    // Обновляем размеры и позицию `slider` при изменении размеров главного окна
    onWidthChanged: {
        slider.width = mainWindow.width / 3
        if (mainWindow.isOpen) {
            slideAnimation.to = mainWindow.width - slider.width
            slider.x = mainWindow.width - slider.width
        } else {
            slideAnimation.to = mainWindow.width
            slider.x = mainWindow.width
        }
    }

    onHeightChanged: {
        slider.height = mainWindow.height
        triggerArea.height = mainWindow.height
    }
}
