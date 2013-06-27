// Default empty project template
import bb.cascades 1.0

// creates one page with a label
Page {
    Container {
        leftPadding: 20
        rightPadding: 20
        layout: StackLayout {
            orientation: LayoutOrientation.TopToBottom
        }
        Label {
            text: qsTr("Encoding tester")
            textStyle.base: SystemDefaults.TextStyles.BigText
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
        }
        DropDown {
            id: linkField
            objectName: "linkField"
            layoutProperties: StackLayoutProperties {
                spaceQuota: 3
            }
            Option {
                text: "http://beread.azurewebsites.net/?url=http://fr.m.wikipedia.org/wiki/Seconde_Guerre_mondiale"
                value: "http://beread.azurewebsites.net/?url=http://fr.m.wikipedia.org/wiki/Seconde_Guerre_mondiale"
                selected: true
            }
            Option {
                text: "http://www.citroen.fr/home/"
                value: "http://www.citroen.fr/home/"
            }
            Option {
                text: "http://www.china-airlines.co.jp"
                value: "http://www.china-airlines.co.jp"
            }
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            Label {
                text: "Encoding: "
                verticalAlignment: VerticalAlignment.Center
            }
            DropDown {
                id: encodingField
                objectName: "encodingField"
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 2
                }
                Option {
                    text: "UTF8"
                    value: "UTF8"
                    selected: true
                }
                Option {
                    text: "ASCII"
                    value: "ASCII"
                }
                Option {
                    text: "UCS4"
                    value: "UCS4"
                }
                Option {
                    text: "UFT16"
                    value: "UFT16"
                }
                Option {
                    text: "Latin1"
                    value: "Latin1"
                }
                Option {
                    text: "Local 8bit"
                    value: "Local 8bit"
                }
            }
            Button {
                id: goButton
                objectName: "goButton"
                text: "Go!"
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                onClicked: {
                    goButton.setVisible(false)
                    activityIndicator.setRunning(true)
                    activityIndicator.setVisible(true)
                    Qt._app.fetch(linkField.selectedValue, encodingField.selectedValue)
                }
            }
            ActivityIndicator {
                id: activityIndicator
                objectName: "activityIndicator"
                running: false
                visible: false
                verticalAlignment: VerticalAlignment.Center
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
            }
        }
        Divider {}
        Container {
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
        }
        ScrollView {
        	id: contentScrollView
        	objectName: "contentScrollView"
        	visible: false
        	content: Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.TopToBottom
                }
                Label {
                    text: "Header:"
                    textStyle.base: SystemDefaults.TextStyles.TitleText
                }
                TextArea {
                    id: headerText
                    objectName: "headerText"
                    editable: false
                }
                Divider {
                }
                Label {
                    text: "Content:"
                    textStyle.base: SystemDefaults.TextStyles.TitleText
                }
                TextArea {
                    id: contentText
                    objectName: "contentText"
                	editable: false
                }
                Divider {}
            }
        }
    }
    onCreationCompleted: {
        Qt._app = _app;
    }
}

