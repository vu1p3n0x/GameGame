// FILE: inputclass.h
// DATE: 2/22/13
// DESC: declaration of the input class to handle input messages

#ifndef INPUTCLASS_H
#define INPUTCLASS_H

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();
	void Shutdown();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};

#endif