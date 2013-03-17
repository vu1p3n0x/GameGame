// FILE: inputobject.h
// DATE: 3/1/13
// DESC: declaraton of an object to manage external input

#ifndef INPUTOBJECT_H
#define INPUTOBJECT_H

#define DIRECTINPUT_VERSION 0x0800

#define INPUTOBJECT_KEYBOARD_MAX 256
#define INPUTOBJECT_MOUSE_MAX 4

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>
#include <exception>

class InputObject
{
private:
	HWND m_hwnd;
	int m_screenWidth;
	int m_screenHeight;

	IDirectInput8* m_directInput;

	IDirectInputDevice8* m_keyboard;
	unsigned char m_keyboardState[256];
	unsigned char m_prevKeyboardState[256];

	IDirectInputDevice8* m_mouse;
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_prevMouseState;
	bool m_mouseLocked;
	int m_mouseX;
	int m_mouseY;

	bool IsPrevKeyPressed(unsigned int key);
	bool IsPrevButtonPressed(unsigned int button);

public:
	InputObject();
	InputObject(const InputObject& inputobject);
	~InputObject();

	/// <summary> Initializes the InputClass by acquiring the mouse and keyboard devices </summary>
	/// <param name="instance"> The current application instance that will be tied to the input devices </param>
	/// <param name="windowHandle"> The handle of the application window </param>
	/// <param name="screenWidth"> The width of the screen </param>
	/// <param name="screemHeight"> The height of the screen </param>
	/// <exception cref="std::exception"> Thrown when initialization of device fails </exception>
	/// <remarks>
	/// Sets private variables and creates the direct input object. Uses that to create the keyboard and mouse.
	/// </remarks>
	bool Initialize(HINSTANCE instance, HWND windowHandle, int screenWidth, int screenHeight);
	/// <summary> Updates states of mouse and keyboard </summary>
	/// <exception cref="std::exception"> Thrown when either the keyboard or mouse is lost and cannot be reaquired </exception>
	/// <remarks>
	/// Sets previous state from current state and gets the current state of keyboard and mouse. Updates mouse position
	/// based on focus and clamps to window size
	/// </remarks>
	bool Update();
	/// <summary> Releases input objects and deletes them </summary>
	/// <remarks>
	/// Releases, deletes, and flags the mouse and keyboard objects as well as the direct input object. Note: keyboard
	/// keystrokes will still be detected when mouse is unfocused but only if the window is on top and focused
	/// </remarks>
	void Shutdown();

	/// <summary> Returns true when a keyboard key is first pressed </summary>
	/// <param name="key"> Index of the key to be returned </param>
	/// <exception cref="std::exception"> Thrown when key index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the current key-state is pressed and the previous key-state is not pressed
	/// </remarks>
	bool IsKeyTriggered(unsigned int key);
	/// <summary> Returns true while a keyboard key is pressed </summary>
	/// <param name="key"> Index of the key to be returned </param>
	/// <exception cref="std::exception"> Thrown when key index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the current key-state is pressed and ignores the previous key-state
	/// </remarks>
	bool IsKeyPressed(unsigned int key);
	/// <summary> Returns true when a keyboard key is released </summary>
	/// <param name="key"> Index of the key to be returned </param>
	/// <exception cref="std::exception"> Thrown when key index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the previous key-state is pressed and the current key-state is not pressed
	/// </remarks>
	bool IsKeyReleased(unsigned int key);

	/// <summary> Sets the variables passed to the current mouse position </summary>
	/// <param name="positionX"> Variable to be set to the mouse's X coordinate </param>
	/// <param name="positionY"> Variable to be set to the mouse's Y coordinate </param>
	/// <remarks>
	/// Sets the variables values based on the position of the virtual cursor in pixel units where the bottom left of the
	/// window is the origin. Value is clamped to be within the window
	/// </remarks>
	void GetMouseLocation(int& positionX, int& positionY);
	
	/// <summary> Returns true when a mouse button is first pressed </summary>
	/// <param name="button"> Index of the button to be returned </param>
	/// <exception cref="std::exception"> Thrown when button index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the current button-state is pressed and the previous button-state is not pressed
	/// </remarks>
	bool IsButtonTriggered(unsigned int button);
	/// <summary> Returns true while a mouse button is pressed </summary>
	/// <param name="button"> Index of the button to be returned </param>
	/// <exception cref="std::exception"> Thrown when button index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the current button-state is pressed and ignores the previous button-state
	/// </remarks>
	bool IsButtonPressed(unsigned int button);
	/// <summary> Returns true when a mouse button is released </summary>
	/// <param name="button"> Index of the button to be returned </param>
	/// <exception cref="std::exception"> Thrown when button index is out of bounds </exception>
	/// <remarks>
	/// Returns true when the previous button-state is pressed and the current button-state is not pressed
	/// </remarks>
	bool IsButtonReleased(unsigned int button);

	/// <summary> Returns true if the mouse is locked on the window </summary>
	/// <remarks>
	/// Returns true if the mouse is locked on the window
	/// </remarks>
	bool IsFocused();
	/// <summary> If the mouse is not locked on the screen, it is locked </summary>
	/// <remarks>
	/// Makes the cursor dissapear and locks the cursor on the window
	/// </remarks>
	void LockMouse();
	/// <summary> If the mouse is locked on the screen, it is unlocked </summary>
	/// <remarks>
	/// Makes the cursor reapear and unlocks the cursor on the window
	/// </remarks>
	void ReleaseMouse();
};

#endif