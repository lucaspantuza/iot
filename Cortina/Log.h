#ifndef LOG_H
#define LOG_H

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


// Display LCD
    LiquidCrystal_I2C lcd(0x27, 16, 2);

class Log {
private:

    

public:

    Log(int i) {
        lcd.begin();
        lcd.backlight();
    }

    void nada() {
        //start of loop Robojax code for LCD with I2C
        lcd.clear();
        lcd.print("Robojax");
        lcd.setCursor(0, 1); // go to start of 2nd line
        lcd.print("Hello World!");
        //lcd.print(millis() / 1000);
//        delay(500);
        //end of loopcode Robojax code for LCD with I2C
    }
};

#endif /* LOG_H */

