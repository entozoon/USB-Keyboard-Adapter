//
// Mini Nano V3.0 ATmega328P
// (longass thirsty ass arduino)
// Had to install drivers: /CH341SER/CH341SER.inf manually
// Board: Arduino Nano
// Processor: ATmega328P (Old Bootloader) ***
//

#include <Arduino.h> // for the sake of vscode intellisense

const int columnsLength = 12;
const int rowsLength = 8;
int columns[columnsLength] = {
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
};
int rows[rowsLength] = {A0, A1, A2, A3, A4, A5, A6, A7};
// int columns[columnsLength] = {0, 13, A7, A6, A5, A4, A3, A2, A1, A0, 12, 11};
// int rows[rowsLength] = {10, 9, 8, 7, 6, 5, 4, 3};

int keyboardState[rowsLength][columnsLength];

// String characterMap[columnsLength][rowsLength] = {
//     // CHANGE THESE TO CHAR
//     // {"0a", "0b", "0c", "0d", "0e", "0f", "0g", "0h", "0i", "0j", "0k", "0l", "0m"},
//     // {"1a", "1b", "1c", "1d", "1e", "1f", "1g", "1h", "1i", "1j", "1k", "1l", "1m"},
//     // {"2a", "2b", "2c", "2d", "2e", "2f", "2g", "2h", "2i", "2j", "2k", "2l", "2m"},
//     // {"3a", "3b", "3c", "3d", "3e", "3f", "3g", "3h", "3i", "3j", "3k", "3l", "3m"},
//     // {"4a", "4b", "4c", "4d", "4e", "4f", "4g", "4h", "4i", "4j", "4k", "4l", "4m"},
//     // {"5a", "5b", "5c", "5d", "5e", "5f", "5g", "5h", "5i", "5j", "5k", "5l", "5m"},
//     // {"6a", "6b", "6c", "6d", "6e", "6f", "6g", "6h", "6i", "6j", "6k", "6l", "6m"},
//     // {"7a", "7b", "7c", "7d", "7e", "7f", "7g", "7h", "7i", "7j", "7k", "7l", "7m"}};
//     {"0a", "0b", "0c", "0d", "0e", "0f", "0g", "0h", "0i", "0j", "0k", "0l", "0m"},
//     {"1a", "1b", "1c", "1d", "1e", "1f", "1g", "1h", "1i", "1j", "1k", "1l", "1m"},
//     {"2a", "2b", "2c", "2d", "2e", "2f", "2g", "2h", "2i", "2j", "2k", "2l", "2m"},
//     {"3a", "3b", "3c", "3d", "3e", "3f", "3g", "3h", "3i", "3j", "3k", "3l", "3m"},
//     {"4a", "4b", "4c", "4d", "4e", "4f", "4g", "4h", "4i", "4j", "4k", "4l", "4m"},
//     {"5a", "5b", "5c", "5d", "5e", "5f", "5g", "5h", "5i", "5j", "5k", "5l", "5m"},
//     {"6a", "6b", "6c", "6d", "6e", "6f", "6g", "6h", "6i", "6j", "6k", "6l", "6m"},
//     {"7a", "7b", "7c", "7d", "7e", "7f", "7g", "7h", "7i", "7j", "7k", "7l", "7m"}};

#define allPinsLength 20
int allPins[allPinsLength] = {
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0, A0, A1, A2, A3, A4, A5, A6, A7};
// A6 and A7 CANNOT be used as digital pins! only analag. FFS
// https://forum.arduino.cc/index.php?topic=123176.0

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
  }
  // for (int c = 0; c < columnsLength; c++)
  // {
  //   pinMode(columns[c], INPUT_PULLUP);
  // }
  // for (int r = 0; r < rowsLength; r++)
  // {
  //   pinMode(rows[r], INPUT_PULLUP);
  // }

  for (int i = 0; i < allPinsLength; i++)
  {
    pinMode(allPins[i], INPUT_PULLUP);
    digitalWrite(allPins[i], HIGH);
  }

  delay(2000);
  Serial.println("\nLet's go");
  Serial.println("If you see solid rows, the pin is fucked");
  delay(2000);
}

void loop()
{
  delay(350);
  Serial.print("   ");
  for (int i = 0; i < allPinsLength; i++)
  {
    Serial.print(i % 10);
  }
  for (int i = 0; i < allPinsLength; i++)
  { // "Sense" pin
    pinMode(allPins[i], INPUT_PULLUP);
    // delay(1);
    Serial.println("");
    if (i < 10)
      Serial.print(" ");
    Serial.print(i);
    Serial.print(": ");
    for (int j = 0; j < allPinsLength; j++)
    {
      // pin is always connected to itself
      if (i == j)
        continue;

      // delay(1);
      pinMode(allPins[j], OUTPUT);
      digitalWrite(allPins[j], LOW);

      if (allPins[i] == A6 || allPins[i] == A7)
      {
        Serial.print(analogRead(allPins[i]) < 100 ? '0' : ' ');
      }
      else
      {
        Serial.print(digitalRead(allPins[i]) == LOW ? '0' : ' ');
      }
      // if (digitalRead(allPins[i]) == LOW && allPins[i] > allPins[j])
      // {

      //   while (digitalRead(allPins[i]) == LOW)
      //     ;
      // }
      digitalWrite(allPins[j], HIGH);
      // delay(1);
      // pinMode(allPins[j], INPUT_PULLUP);
    }
    // delay(1);
    // pinMode(allPins[i], INPUT_PULLUP);
  }
  Serial.println("");
}

// void loop()
// {
//   for (int c = 0; c < columnsLength; c++)
//   {
//     // Pull the column low
//     pinMode(columns[c], OUTPUT);
//     digitalWrite(columns[c], LOW);
//     // delay(5);

//     // Iterate over the rows, reading their state
//     for (int r = 0; r < rowsLength; r++)
//     {
//       int keyDown = (digitalRead(rows[r]) == LOW) ? 1 : 0;
//       if (keyDown != keyboardState[r][c])
//       {
//         // Serial.print(c);
//         // Serial.print(" ");
//         // Serial.print(r);
//         // Serial.print(" ");
//         //     // char character = characterMap[r][c]; // CHANGE TO THIS INNIT
//         //     String character = characterMap[r][c];
//         //     // Serial.print(keyDown ? " down " : "   up ");

//         //     if (keyDown)
//         //     {
//         //       Serial.print(character);
//         //       Serial.println("");
//         //     }

//         //     // if (character != HID_KEY_NONE)
//         //     // {
//         //     //   sendKey(character, keyDown);
//         keyboardState[r][c] = keyDown;
//         //     // }
//       }
//     }

//     pinMode(columns[c], INPUT_PULLUP);
//   }
//   printKeyboardState();
//   delay(400);
// }

// void printKeyboardState()
// {
//   Serial.print(' ');
//   Serial.print(' ');
//   for (int c = 0; c < columnsLength; c++)
//   {
//     Serial.print(c + 1);
//     Serial.print(' ');
//   }
//   Serial.println("");
//   for (int r = 0; r < rowsLength; r++)
//   {
//     Serial.print(r + 1);
//     Serial.print(' ');
//     for (int c = 0; c < columnsLength; c++)
//     {
//       Serial.print(keyboardState[r][c] ? 'X' : ' ');
//       Serial.print(' ');
//     }
//     Serial.println("");
//   }
//   Serial.println("");
// }