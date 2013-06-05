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
    Page {
        id: optionsPage

        content: Container {
            //background: Color.create("#262626")
            //preferredWidth: 768

            layout: StackLayout {

            }
            topMargin: 0.0
            leftPadding: 20.0
            topPadding: 20.0
            bottomPadding: 20.0
            rightPadding: 20.0
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight

                }
                Label {
                    text: "Activate on launch"

                }
                ToggleButton {
                    id: autoActive
                objectName: "autoActive"
                checked: _mainMenu.getValueFor(objectName, "false")
                onCheckedChanged: {
                    _mainMenu.saveValueFor(autoActive.objectName, checked)
                }
            }

            }
            Divider {

            }
//            Container {
//                Label {
//                    text: "Keys"
//
//                }
//                Container {
//                    layout: StackLayout {
//                        orientation: LayoutOrientation.LeftToRight
//
//                    }
//                    Label {
//                        text: "House"
//
//                    }
//                    Label {
//                        text: "070802002112"
//                    }
//                    Button {
//                        text: "Generate"
//
//                    }
//
//                }
//                ListView {
//                    listItemComponents: [
//                        ListItemComponent {
//
//                        }
//                    ]
//
//                }
//
//            }
        }

    }
