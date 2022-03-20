# Gamepad Phoenix

Gamepad Phoenix is a tool for Windows to play any game (old or new) with any gamepad (old or new).

## Screenshot
[<img src="https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkwLnBuZw==/347x500/VkH6Ti.png">](https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkwLnBuZw==/original/xE6hld.png)|[<img src="https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkxLnBuZw==/347x500/xDOkKI.png">](https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkxLnBuZw==/original/PSmpx%2F.png)|[<img src="https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkzLnBuZw==/347x500/gGcSni.png">](https://img.itch.zone/aW1hZ2UvMTA0MTc1OS82MDkwODkzLnBuZw==/original/lkV56E.png)
:---:|:---:|:---:
Map Controller|Setup Games|More

## Features
- Create a unified button and axis mapping for up to 4 controllers
- Supports XInput, DirectInput and Wii controllers
- Manage and launch games through the tool
- Emulates XInput, DirectInput (any version) and WinMM APIs
- Automatic detection of API, no configuration/file copying needed
- Supports both DRM free games and games with launchers/stores
- Create controller presets, load one by pressing a single button
- Easy reordering of controllers
- Tool can be navigated by gamepad
- Borderless fullscreen for any game

## Download
You can download the latest version of Gamepad Phoenix for free (donations welcome!) on [itch.io](https://schelling.itch.io/gamepad-phoenix).  
Just extract the ZIP file and then run GamepadPhoenix.exe.

## Donations
Tips and donations are welcome, either through the [itch.io page](https://schelling.itch.io/gamepad-phoenix)
or the Sponsor button at the top of the [GitHub repository](https://github.com/schellingb/GamepadPhoenix).

Thanks for your consideration!

## Usage

### Map Controllers
To map an entire emulated controller, just click the "Assign All Buttons/Axes" button in the top-right of the window and press the buttons and stick directions in order as prompted.
If a button or axis is not available on the real controller, you can click the "Clear" button to skip assignment.
Individual parts of the gamepad can be remapped by clicking them either on the graphic in the center or by clicking a specific part in the lists on the sides of the window.

- To avoid input from a XInput gamepad getting misrecognized, you can set the drop-down selection to "Assign only from XInput".
- To clear all mappings of a controller, right click the controller tab and select "Clear All Assignments".
- To add another emulated gamepad, click on the '+' tab between the last controller tab and the "Launch Game" tab.
- Up to 4 emulated controllers can be defined.

### Manage Presets
You can load and save controller mapping presets using the two buttons in the top-left of the window.

While loading a preset, if you press L1 on a controller and a matching preset exists, it will be loaded automatically.

### Setup Games
On the "Launch Game" tab, press "New" to create a new game launch configuration.
Next, click "Select Game EXE" to browse for the executable of the game to launch through Gamepad Phoenix.  
Selecting the game .EXE will automatically fill out the fields 'Name', 'Target' and 'Start In'.
You can modify them afterwards as needed and define optional launch command line arguments as well.

Don't forget to click the "Save" button to store it in the games list.

The games list can be re-ordered by dragging items with the mouse.

#### Launch Game Options
The following per-game options can be toggled by clicking on the Options box in the game details.

- __Map D-Pad to Left Stick__  
  Will make the D-Pad on all emulated controllers also control the left analog stick.

- __Swap A and B Buttons__  
  Switch the A and B button on all emulated controllers.

- __Swap L1/R1 and L2/R2__  
  Switch the upper shoulder/bumper buttons with the lower triggers.

- __DirectInput: Map Triggers to Buttons instead of Analog Axis__  
  Modifies the analog triggers to be regular digital buttons (required for some older games)

- __DirectInput: Map D-Pad to Buttons instead of Point of View Hat__  
  Modifies the D-Pad to be 4 separate digital instead of a POV hat (required for some older games)

- __Use Indirect Loading (Prepare redirector DLL to allow external stores/launchers)__  
  See section on [indirect loading](#indirect-loading) below.

- __Disable XInput (return no connected controllers)__  
  When set, the game will find no connected XInput controllers and will have to use other interfaces (most commonly DirectInput) to access the gamepads. 

- __Disable DirectInput (return no joystick or only fake XInput gamepads)__  
  When set, Gamepad Phoenix will not return DirectInput specific gamepads (with separate axis for the two triggers) but instead return only controllers when XInput is also used.

- __Disable MMSys (return no joystick or only fake XInput gamepads)__  
  When set, Gamepad Phoenix will not return MMSys specific gamepads (with separate axis for the two triggers) but instead return only controllers when XInput is also used.

- __Force game window to borderless fullscreen__
  Will resize the game window to fill the entire screen. Useful for games that don't support this natively.

#### Indirect Loading
The game option 'Use Indirect Loading' can be required for some games that refuse to run directly by launching the .EXE file.  
Things like launchers, updaters or game stores can make the direct loading method not work.  
Check the log view below the game details for how a game behaves when launched and try this option when the gamepad emulation does not work.

When enabled, two additional buttons "Prepare" and "Restore" will appear next to the "Launch" button.  
Use the "Prepare" button to analyze the game and setup an appropriate redirector DLL automatically.

After preparing, the game can be launched through the tool or directly through its launcher or store.

### Connect Wii Controllers
Gamepad Phoenix supports communication with Bluetooth powered Wii Remote Controllers and using them just like regular Windows controllers.

Buttons and axes from the main controller and extensions can be mapped. Motion controls are not supported.
Supported extensions are Classic Controller (including Pro and NES/SNES Classic Mini variants), Nunchuk and the WiiU Pro Controller.

To connect to a controller, make sure the PC has a Bluetooth module installed (can be either built-in or a USB dongle).
Then switch to the "More" tab in Gamepad Phoenix and click the "Connect New Controller" in the "Wii Controllers" section.

Next, press the red SYNC button behind the battery cover of the Wii Remote Controller. After a few seconds, the status info text should
switch from "Searching For Wii Controller" to "Registering HID Service" and finally to "Found New Controller".

Once the controller has been connected, the LEDs pattern can be set with the four checkboxes in the Wii Controller list.
The buttons and axes can be mapped to any of the gamepads in the "Controller" tabs like a regular controller.

The controller will not be paired to the PC and needs to be connected again once the it loses power or the sync button gets pressed.

### Gamepad Controls
The tool itself can be navigated with the mapped controllers.

- While holding select/back, L and R switch tabs
- While holding select/back, A/B/X/Y jump to the "Launch Game" tab
- While holding select/back, Left/Right swaps the gamepad order
- On the "Launch Game" tab, Up/Down selects the previous/next game
- On the "Launch Game" tab, Left/Right scrolls the game list by 10
- On the "Launch Game" tab, Start/A/B/X/Y launches the selected game

## License
Gamepad Phoenix is available under the [GPL-3.0 license](https://choosealicense.com/licenses/gpl-3.0/).  
If you are interested in parts of this program under a more permissive or public domain license, feel free to contact me.
