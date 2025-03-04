Nodes for receiving data from a USB or Bluetooth Human Interface Device (HID) and for discovering available HIDs.

Some USB and Bluetooth devices (but not all of them) are [HIDs](https://en.wikipedia.org/wiki/USB_human_interface_device_class) — for example, your keyboard and mouse are HIDs, and joysticks, game pads, and other controllers may be HIDs.

The [Receive HID Controls](vuo-node://vuo.hid.receive) node receives values from HID **controls**.  A control is physical interface that provides a single data value.  For example, a typical 3-button mouse will have 6 controls: X, Y, Wheel, Button 1, Button 2, and Button 3.  Use the [Filter Control](vuo-node://vuo.hid.filter.control2) or [Filter and Scale Control](vuo-node://vuo.hid.scale.control2) node to narrow down the data to just the controls you're interested in.


## Troubleshooting

If you're not sure whether Vuo is detecting your HID:

   - Add a [Receive HID Controls](vuo-node://vuo.hid.receive) node to your composition. Double-click on its `Device` input port to bring up a menu of all connected HIDs. See if your device is in the list.
   - Check Vuo's Console window (Tools > Show Console) for any messages about HIDs.

If Vuo isn't detecting your device:

   - Make sure your composition is referring to the correct device. (Sometimes two devices of the same model can have different names.)
   - Make sure you've installed any necessary drivers for the device.
   - Make sure the device is securely plugged in.
   - Try plugging the device into a different port on your computer.

If Vuo detects your device, but doesn't seem to be receiving any data:

   - Make sure your composition is referring to the correct device, especially if you have multiple similar devices connected.
   - Make sure that another Vuo composition or application isn't already exclusively connected to the device. (Check Vuo's Console window (Tools > Show Console) for messages.)
   - Try unplugging the device and plugging it back in. (If another Vuo composition was using the device but isn't using it anymore, this will make your current composition retry connecting to the device.)
   - To exclusively read from a keyboard, macOS requires `root` access.
   - If you're using a 3Dconnexion SpaceMouse or SpaceNavigator, ensure that the 3DxWare drivers are _not_ installed, since 3DxWare prevents Vuo from receiving data from 3Dconnexion devices.
