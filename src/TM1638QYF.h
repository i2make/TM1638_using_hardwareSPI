/*
TM1638QYF.h - Library for TM1638.

Copyright (C) 2011 Ricardo Batista <rjbatista at gmail dot com>

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TM1638QYF_h
#define TM1638QYF_h

#define S01     0b0000000000000001
#define S02     0b0000000000000010
#define S03     0b0000000000000100
#define S04     0b0000000000001000
#define S05     0b0000000000010000
#define S06     0b0000000000100000
#define S07     0b0000000001000000
#define S08     0b0000000010000000
#define S09     0b0000000100000000
#define S10     0b0000001000000000
#define S11     0b0000010000000000
#define S12     0b0000100000000000
#define S13     0b0001000000000000
#define S14     0b0010000000000000
#define S15     0b0100000000000000
#define S16     0b1000000000000000

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "TM16XX.h"
#include "TM16XXFonts.h"

class TM1638QYF : public TM16XX
{
  public:
    /** Instantiate a tm1638 module specifying the display state, the starting intensity (0-7) data, clock and stobe pins. */
    TM1638QYF(byte strobePin, boolean activateDisplay = true, byte intensity = 7);

    /** Set the display to a unsigned hexadecimal number (with or without leading zeros) */
    void setDisplayToHexNumber(unsigned long number, byte dots, boolean leadingZeros = true,
		const byte numberFont[] = FONT_DEFAULT);
    /** Set the display to a unsigned decimal number (with or without leading zeros) */
    void setDisplayToDecNumber(unsigned long number, byte dots, boolean leadingZeros = true,
		const byte numberFont[] = FONT_DEFAULT);
    /** Set the display to a signed decimal number (with or without leading zeros) */
    void setDisplayToSignedDecNumber(signed long number, byte dots, boolean leadingZeros = true,
		const byte numberFont[] = FONT_DEFAULT);
    /** Set the display to a unsigned binary number */
    void setDisplayToBinNumber(byte number, byte dots,
		const byte numberFont[] = NUMBER_FONT);

	/** Clear the display */
	virtual void clearDisplay();
    /** Set the display to the String (defaults to built in font) - pos is ignored in common anode */
	virtual void setDisplayToString(const char* string, const word dots = 0, const byte pos = 0,
		const byte font[] = FONT_DEFAULT);
    /** Set the display to the String (defaults to built in font) - pos is ignored in common anode */
	virtual void setDisplayToString(String string, const word dots = 0, const byte pos = 0,
		const byte font[] = FONT_DEFAULT);

    /** Returns the pressed buttons as a bit set (left to right). */
    virtual word getButtons();

  protected:
	/** Set the display to the values (left to right) */
    virtual void setDisplay(const byte values[], unsigned int length = 8);

  private:
	// unsupported in common anode design
    virtual void setDisplayDigit(byte digit, byte pos, boolean dot, const byte numberFont[] = NUMBER_FONT) { setDisplayToError(); };
	// unsupported in common anode design
    virtual void clearDisplayDigit(byte pos, boolean dot) { setDisplayToError(); };
	// unsupported in common anode design
	virtual void sendChar(byte pos, byte data, boolean dot) { setDisplayToError(); }
};

#endif
