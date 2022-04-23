/*==============================================================================
 Project: Intro-2-Variables
 Date:    March 1, 2022
 
 This example program demonstrates the use of byte (char) constants and
 variables to count button presses and trigger actions when a limit is reached.
  
 Additional program analysis and programming activities demonstrate using bit
 (Boolean, or bool) variables to store state for operations such as preventing 
 multiple counting of a singe button press during successive program loops.
 Additional activities include the creation of a two-player rapid-clicker game,
 simulating a real-world Prepressed button, and counting switch contact bounce.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP410.h"         // Include UBMP4.1 constant and function definitions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program constant definitions

#define pressed 0
#define notPressed 1

int main(void)
{
    // Configure oscillator and I/O ports. These functions run once at start-up.
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    // Code in this while loop runs repeatedly.
    while(1)
	{
        
      
      
      
        // Add a short delay to the main while loop.

        
        // Activate bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Program Analysis
 * 
 * 1. The 'SW2Count' variable is created within RAM as an 8-bit memory location
 *    by the declaration: 'unsigned char SW2Count = 0;'
 *    What is the the maximum value an 8-bit variable can store? What are some
 *    of the benefits and drawbacks of using 8-bit variables in an 8-bit
 *    microcontroller?
 * The max amount of 8-bit variable is 255. The benefits is that file is guarteed to work within the confines of the microcontroller.
 * The drawbacks is that the maximum value of 255 and can't go any higher.
 * 2. The constant 'maxCount' is defined using a declaration similar to that
 *    used for the SW2Count variable, but with the 'const' prefix added in the
 *    declaration. Can you think of some advantages of declaring a constant like
 *    this, using a separate statement above the main code, rather than just
 *    embedding the value of the constant where it is needed in the code?
 * Advantages of a constant is that the value will never change, and will be set the same as when it started.
 * embedding it outside of the main code allows you to use it outside of the main functons. 
 *
 * 3. This program should light LED D3 every time SW2 is pressed, and light
 *    LED D4 once the count reaches 50. Try it, and count how many times you
 *    have to press the button until LED D4 turns on. SW3 resets the count so
 *    you can perform repeated attempts.
 * 
 *
 *    Did your count reach 50? Can you describe what the program is doing?
 *    (Hint: try pressing and releasing the button at different rates of speed.)
 * The count did not reach 50 at all, this is because when im pressing it down for even a second, it counts all multiple presses at once.
 * That happens because the delay is only 10ms, so the whole code loops every 10ms, and I cannot press and let go of the button every 10ms.
 * 4. Modify the second 'if' structure to add the else block, as shown below:

        if(SW2Count >= maxCount)
        {
            LED4 = 1;
        }
        else
        {
            LED4 = 0;
        }

 *    Now, press and hold pushbutton SW2 for at least 10 seconds while watching
 *    LED D4. LED D4 should stay on continuously while the value of SW2Count is
 *    higher than maxCount. If LED D4 turns off, what can you infer about the
 *    value of the SW2Count variable? Can you explain what happens to the
 *    SW2Count variable as the SW2 button is held?
 * If the LED D4 turns off, then the value of SW2Count is less than the value of maxCount, or lower than 50. 
 * When the the value hits over 255, it resets back to 0, making it less than 50.
 * 5. We can set a limit on the SW2Count variable by encapsulating its increment
 *    statement inside a conditional statement. In your program, replace the
 *    line 'SW2Count = SW2Count + 1;' with the code, below:
 
            if(SW2Count < 255)
            {
                SW2Count += 1;
            }

 *    This code demonstrates the use of the assignment operator '+=' to shorten
 *    the statement 'SW2Count = SW2Count + 1;' The same operation is performed,
 *    but in a more compact form. After adding this code, what is the maximum
 *    value that the SW2Count variable will reach? How does this affect the
 *    operation of LED D4 when SW2 is held?
 * The maximum value SW2Count can reach is 255, after it will not anymore to the value.
 * This effects of this for the LED D4 is that SW2Count will no longer reset back to 0, so it will not turn off when held for a long period of time.
 * 6. The fundamental problem with this program is that pushbutton SW2 is sensed
 *    in each cycle of the loop, and if its state is read as pressed, another
 *    count is added to the SW2Count variable. The program needs to be made to
 *    respond only to each new press, rather than just switch state -- in other
 *    words, to a *change* of SW2 state, from not-pressed to pressed. Doing this
 *    requires the use of another variable to store the prior state of SW2, so
 *    that its current state can be evaluated as being the same, or different
 *    from its state in the previous loop. Replace the initial if-else condition 
 *    with the following two if conditions:

        // Count new SW2 button presses
        if(SW2 == 0 && SW2Pressed == false)
        {
            LED3 = 1;
            SW2Pressed = true;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
        }

        // Clear pressed state if released
        if(SW2 == 1)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 *    These two if conditions make use of the Boolean SW2Pressed variable to
 *    store the current state of SW2 for the next cycle of the main while loop.
 *    Boolean variables can store 0/false or 1/true, interchangeably. The first
 *    if condition, above, compares the current SW2 state with the previously
 *    stored SW2Pressed variable so that a new count is only added when the SW2
 *    button is pressed and SW2Pressed is false. In the if structure, SW2Pressed
 *    is set to true before a count is added. The following if structure resets
 *    SW2Pressed to false when the button is released. Try the code to verify
 *    that it works.
 * 
 *    The conditional statement in the first if condition can also be written:

        if(SW2 == 0 && !SW2Pressed)

 *    The '!SW2Pressed' expression is read as 'not SW2Pressed' and is equivalent
 *    to SW2Pressed being false. Similarly, using the variable name by itself
 *    (eg. SW2Pressed) in a condition is equivalent to SW2Pressed being true.
 * 
 * 7. A pushbutton's logic state can also be defined as a word in a similar way
 *    to a variable (eg. the way SW2Pressed represents 1 or 0, or true or false)
 *    which can help to make the code more readable. Add the following lines to
 *    the 'Program constant definitions' section at the top of the code:
 
 #define pressed 0
 #define notPressed 1

 *    Now, instead of comparing the state of the button to 0 or 1, the button
 *    input can be compared with the named definition for 0 or 1, making the
 *    program more readable at the expense of hiding the actual switch value in
 *    the definition statement instead of making it obvious in the if structure.
 *    Try it in your code, and modify the SW3 reset button to work with the same
 *    pressed and notPressed definitions.
        // Count new SW2 button presses
        if(SW2 == pressed && SW2Pressed == false)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }

        // Clear pressed state if released
        if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
        
 * 
 * Programming Activities
 * 
 * 1. Can you make a two-player rapid-clicker style game using this program as 
 *    a starting point? Let's use SW5 for the second player's pushbutton so that
 *    the two players can face each other from across the UBMP4 circuit board.
 *    Duplicate SW2Count and SW2Pressed to create SW5Count and SW5Pressed
 *    variables. Then, duplicate the required if condition structures and modify
 *    the variable names to represent the second player. LED D4 can still light
 *    if player 1 is the first to reach maxCount. Use LED D5 to show if the
 *    second player wins. Use a logical condition statement to reset the game
 *    by clearing the count and turning off the LEDs if either SW3 or SW4 is
 *    pressed.
 *   
  // Program variable definitions
const unsigned char maxCount = 25;
unsigned char SW2Count = 0;
bool SW2Pressed = false;
unsigned char SW5Count = 0;
bool SW5Pressed = false;
unsigned char P1Win = 0;
unsigned char P2Win = 0;
 //Switch 2 Button Press
    if(SW2 == pressed && SW2Pressed == false && P2Win == 0)
        {
            LED3 = 1;
            if(SW2Count < 255)
            {
                SW2Count = SW2Count + 1;
            }
            SW2Pressed = true;
        }
    // Clear pressed state if released
    if(SW2 == notPressed)
        {
            LED3 = 0;
            SW2Pressed = false;
        }
    //Indication of Victory (SW2)  
    if(SW2Count >= maxCount)
        {
            LED4 = 1;
            P1Win = 1;
        }
        else
        {
            LED4 = 0;
        }
    //Switch 5 Button Press
    if(SW5 == pressed && SW5Pressed == false && P1Win == 0)
        {
            LED6 = 1;
            if(SW5Count < 255)
            {
                SW5Count = SW5Count + 1;
            }
            SW5Pressed = true;
        }

    // Clear pressed state if released
    if(SW5 == notPressed)
        {
            LED6 = 0;
            SW5Pressed = false;
        }
    //Indication of Victory (SW5)  
    if(SW5Count >= maxCount)
        {
            LED5 = 1;
            P2Win = 1;
        }
        else
        {
            LED5 = 0;
        } 
    // Reset Game
    if(SW3 == pressed||SW4 == pressed)
        {
            LED4 = 0; 
            LED5 = 0;
            SW2Count = 0; SW5Count = 0;
            P1Win = 0; 
            P2Win = 0;
        }
 * 2. Use your knowledge of Boolean variables and logical conditions to simulate
 *    a Prepressed button. Each new press of the Prepressed button will 'Prepressed' an LED
 *    to its opposite state. (Prepressed buttons are commonly used as push-on, 
 *    push-off power buttons in digital devices.)
 *
//Program Variables
bool Prepressed = 0;
bool Toggle = 0;
  if(SW2 == 0 && Prepressed == false && Toggle == 0)
    {
        LED3 = 1;
        Toggle = 1;
    }
    if(SW2 == 1 && Prepressed == false && Toggle == 1)
    {
        Prepressed = true;
        Toggle = 0;
    }
    if(SW2 == 0 && Prepressed == true && Toggle == 0)
    {
        LED3 = 0;
        Toggle = 1;
    }
    if(SW2 == 1 && Prepressed == true && Toggle == 1)
    {
        Prepressed = false;
        Toggle = 0;
    }
 * 3. A multi-function button can be used to enable one action when pressed, and
 *    a second or alternate action when held. A variable that counts loop cycles
 *    can be used to determine how long a button is held (just as the first
 *    program unitentionally did, because of the loop structure). Make a
 *    multifunction button that lights one LED when a button is pressed, and
 *    lights a second LED after the button is held for more that one second.
    //Program Variables 
    unsigned char LoopCycle = 0;
    const unsigned char F2 = 100;
      //Single Press Function
        if(SW2 == pressed)
        {
            LED3 = 1;
            LoopCycle ++;
        }
        //Hold Function
        if(LoopCycle >= F2)
        {
            LED4 = 1;
        }
        //Reset Button
        if(SW3 == pressed)
        {
            LED3 = 0;
            LED4 = 0;
            LoopCycle = 0;
        }
 * 4. Do your pushbuttons bounce? Switch bounce is the term that describes
 *    switch contacts repeatedly closing and opening before settling in their
 *    final (usually closed) state. Switch bounce in a room's light switch is
 *    not a big concern, but switch bounce can be an issue in a Prepressed button
 *    because the speed of a microcontroller lets it see each bounce as a new,
 *    separate event. Use a variable to count the number of times a pushbutton
 *    is pressed and display the count on the LEDs. Use a separate pushbutton
 *    to reset the count and turn off the LEDs so that the test can be repeated.
 *    To determine if your switches bounce, try pressing them at various speeds
 *    and using different amounts of force.
 *  //Switch Bouncer Checker
//Variables
unsigned char SW2BounceCounter = 0;
unsigned char Held = 0;
      if(SW2 == pressed && Held == 0)
    {
        SW2BounceCounter ++;
        Held = 1;
    }
    if(SW2 == 1)
    {
        Held = 0;
    }
    //Display of Switch Bounce
      if(SW2BounceCounter == 4)
      {LED3 = 1;}
      if(SW2BounceCounter == 5)
      {LED4 = 1;}
      if(SW2BounceCounter == 6)
      {LED5 = 1;}
       if(SW2BounceCounter == 7)
      {LED6 = 1;}
     //Reset
      if(SW3 == pressed)
      {
          LED3 = 0;
          LED4 = 0;
          LED5 = 0;
          LED6 = 0;
          SW2BounceCounter = 0;
      }
 * 5. Did your pushbuttons bounce? Can you think of a technique similar to the
 *    multi-function button that could be implemented to make your program
 *    ignore switch bounces. Multiple switch activations within a 50ms time span
 *    might indicate switch bounce and can be safely ignored.
 *  Yes, my pushbuttons did bounce. A way to check for switch bounces that can ignore switch bounces is a checker.
 *  When a switch is pressed, a loopcycle actives for 50ms. During which, all inputs from the same switch will be ignored.
 *  After so, it will run the command the switch that was programmed to do.
 */
