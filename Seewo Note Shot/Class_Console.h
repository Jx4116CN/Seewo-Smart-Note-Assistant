#pragma once
#include <iostream>
#include <Windows.h>

class Console
{
	bool Alloc;
    bool outDate;

    void OutDate();

public:
	Console();
	~Console();

	inline bool is_Alloc() { return this->Alloc; }

    inline void open_DateOut() { outDate = true; }
    inline void close_DateOut() { outDate = false; }

    template<typename T>
    Console& operator<<(const T& value)
    {
        if (outDate) this->OutDate();
        std::cout << value;
        return *this;
    }
    Console& operator<<(std::ostream& (*manipulator)(std::ostream&))
    {
        if (outDate) this->OutDate();
        std::cout << manipulator;
        return *this;
    }
};