// FILE: inputclass.cpp
// DATE: 2/22/13
// DESC: implementation of the input class to handle input messages

#include "inputclass.h"

InputClass::InputClass()
{

}
InputClass::InputClass(const InputClass& inputclass)
{

}
InputClass::~InputClass()
{
	
}

void InputClass::Initialize()
{
	for (unsigned int i = 0; i < 256; i++)
		m_keys[i] = false;
}
void InputClass::Shutdown()
{

}

void InputClass::KeyDown(unsigned int key)
{
	m_keys[key] = true;
}
void InputClass::KeyUp(unsigned int key)
{
	m_keys[key] = false;
}
bool InputClass::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}