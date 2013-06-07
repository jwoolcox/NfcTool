/* Copyright (c) 2012 Research In Motion Limited.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import bb.cascades 1.0

NavigationPane {
    id: nav
    objectName: "navPane"

    signal menuShowing()

    Page {
        id: menuListPage

        content: Container {
            background: Color.create("#262626")
            //preferredWidth: 768

            layout: DockLayout {
            }
            ImageToggleButton {
                imageSourceDefault: "asset:///images/inactive.png"
                imageSourceChecked: "asset:///images/active.png"
                id: imgtgbtn
                objectName: "imgtgbtn"
                imageSourcePressedUnchecked: "asset:///images/active.png"
                imageSourcePressedChecked: "asset:///images/inactive.png"
                verticalAlignment: VerticalAlignment.Center
                horizontalAlignment: HorizontalAlignment.Center
                checked: _mainMenu.getValueFor("autoActive", "false")
            }
            ImageButton {
                onClicked: {
                    showOptions()
                }
                defaultImageSource: "asset:///images/ico_bb_ea_gear.png"
                pressedImageSource: "asset:///images/ico_lb_da_gear.png"
                horizontalAlignment: HorizontalAlignment.Right

            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Label {
                    text: "Toggle value: "
                    textStyle.color: Color.Red
                    textStyle.textAlign: TextAlign.Center
                    textStyle.fontWeight: FontWeight.Bold
                }
                Label {
                    text: _mainMenu.getValueFor("autoActive", "false")
                    textStyle.color: Color.Red
                    textStyle.textAlign: TextAlign.Center
                    textStyle.fontWeight: FontWeight.Bold
                }
            }

        }

    }
    attachedObjects: [
        ComponentDefinition {
            id: optionsPage
            source: "optionsPage.qml"
        }
    ]
    function showOptions() {
        // show option page
        var newPage = optionsPage.createObject();
        nav.push(newPage);
    }
    onCreationCompleted: {
        // this slot is called when declarative scene is created
        // write post creation initialization here
        //console.log("NavigationPane - onCreationCompleted()")
        //if (_mainMenu.getValueFor("autoActive", "false") == "true") {
            //showOptions();
            //activatebtn.checked = "true"
            //activatebtn.checkedChanged()
            //_mainMenu.onButtonClicked(true)
            
    //}
        if (_mainMenu.getValueFor("autoActive", "false") == "true") {
            //activatebtn.checked = true;
            //signal activatebtn.checkedChanged(true);
            //imgtgbtn.checkedChanged(true)
        }

    }
    //signal checkedChanged()
}