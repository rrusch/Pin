/**
 * This is the test program for the Pin library.
 *
 * @author Roland Rusch <roland@rusch.lu>
 */


#include <Arduino.h>
#include <Console.h>
#include "../../src/Pin.h"
#include "../../src/PinAnalogIn.h"
#include "../../src/PinPwmOut.h"
#include "../../src/PinDigitalOut.h"
#include "../../src/PinDigitalIn.h"



// Potentiometer pin
PinAnalogIn pinP1(A0);

// Button 1 pin
PinDigitalIn pinB1(4, PinDigitalIn::MODE_PULLUP);

// Button 2 pin
PinDigitalIn pinB2(5, PinDigitalIn::MODE_PULLUP);

// LED green pin
PinDigitalOut pinL1(7);

// LED blue pin
PinPwmOut pinL2(9);

// LED onboard pin
PinDigitalOut pinL3(13);




void b1PosEdge(Pin &pin)
{
	Console.println("Button 1 positive edge.");
}

void b1NegEdge(Pin &pin)
{
	Console.println("Button 1 negative edge.");
}

void b2Low(Pin &pin)
{
	pinL3.writeValue(Pin::VALUE_LOW);
//	Console.println("Button 2 low.");
}

void b2High(Pin &pin)
{
	pinL3.writeValue(Pin::VALUE_HIGH);
//	Console.println("Button 2 high.");
}

void p1Change(Pin &pin)
{
//	pinL2.writeValue(Pin::VALUE_HIGH);
	Console.print(pin.getName());
	Console.print(": ");
	Console.println(pin.getValue());
	pinL2.writeValue(pin.getValue() / 4);
}



//The setup function is called once at startup of the sketch
void setup()
{
	// initialize serial communication:
	Bridge.begin();
	Console.begin();
	
	
	pinP1.onChange(p1Change, 10);
	pinP1.setName("Potentiometer 1");
//	pinP1.calcAvg(20);
//	pinP1.calcDiv4();
	pinP1.setup();
	
	
	pinB1.onPosEdge(b1PosEdge);
	pinB1.onNegEdge(b1NegEdge);
	pinB1.setup();
	
	pinB2.onLow(b2Low);
	pinB2.onHigh(b2High);
	pinB2.setup();
	
	pinL1.setup();
	pinL2.setup();
	
	
}


bool consoleok=false;


// The loop function is called in an endless loop
void loop()
{
	pinP1.update();
	pinB1.update();
	pinB2.update();
	pinL1.update();
	pinL2.update();
	
	
	
	if(consoleok)
	{
		char c=Console.read();
		if(c == '1') pinL1.writeValue(Pin::VALUE_LOW);
		if(c == '2') pinL1.writeValue(Pin::VALUE_HIGH);
	}
	
	
	
	
	if( !consoleok && (Console.available() > 0) )
	{
		Console.println("You're connected to the Console!!!!");
		consoleok=true;
	}
}
