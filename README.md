# Client-Server Communication 
Small project where we tried to learn some basics on how communication with server actually works. Server is waiting for some bites from us. After we sent them, server recieves them and send more bites back. 
If we are able to read those bites we can see the message with task server wants from us. After we send him correct answer, we are ready to move on the next one. Task should be harder and harder each time.

Server is active only around 2 months every year and then it is turned off so most likely you will not be able to run this. Website with instructions is also turned off the whole year but with WayBackMachine you can get some old saves and I was able to download the whole page. 
The first idea I had was to post `index.html` so everyone could see the page I saw when I was doing this school project but because of some possible copyright issues in school I decided not to. So then I wanted to post WayBackMachine link to the page becasue that could go well but I have a strong feeling they could track me in some linking pages list. 

**I found an image of how it looked when I tried to fix text alignment:**

![First](https://i.imgur.com/1lpFbaT.png)

**After some consideration I decided to post only screenshot from the website...**
![Second](https://i.imgur.com/WmPf1Wp.png)



**Whole Communication and keys to get through tasks**
```
Sent: Hi
Received: Wake up Neo...  The Matrix has you...  (You're connected to Morpheus' server. Send me your ID to proceed.)

Sent: MYAISID
Received: Hello MYNAME I need you to do something for me...

Sent: MYNAME
Received: Please disconnect, then reprogram your software to display your name  including diacritics using the function SetConsoleOutputCP(CP_UTF8).
          Display messages from me one letter at a time (wait a few milliseconds after each letter).Then reconnect and after reading this message send me the code 844848.

Sent: 844848
Received: You sent me the correct code. Now disconnect and reprogram your software to show all my messages in green
          color and all your messages in blue color.If you don't know how, check the documentation for excercise 2.5.1. Then reconnect and send me the code 753422.

Sent: 753422
Received: You sent me the correct code. Now send me the result of the following. Compute the sum of first 5 digits of your student ID,
          then divide it by the fifth digit and send me the remainder of the division. The operation must be programed using a function using the ID as an argument.
          It can't be hard-coded. WARNING - If the fifth digit is zero, use 9 instead. The result must be computed by your software! 

Sent: 0
Received: You sent the correct remainder, now reprogram your software so that your messages will be displayed on the
          left side of the screen and mine on the right side of the screen. If you need advice check the documentation for excercise 2.5.2.
          MAKE SURE OF THIS - your messages must end before the half of the screen, mine start after it. No word can be divided across lines.
          After finishing reconnect and send me this code 333222334.

Sent: 333222334
Received: You sent the correct code. In the next message send me the code 123; then I'll send you a cipher of length 148 created by XOR 55.
          Decipher it and follow the orders! If you need advice check the documentation for excercise 2.3.2.

Sent: 123
Received: dRTERCZRDDVPRYX

Sent: Mt Everest
Received: Trinity is endangered by Agent Smith! Send me the integral part of the first coordinate from previous ciphered message

Sent: 27
Received: Correct coordinate. Send me the integral part of the second coordinate from previous ciphered message

Sent: 86
Received: Correct. Send me the abbreviation of the detected object defined by the GPS coordinates in format X.Y. (all letters as capital letters)

Sent: M.E.
Received: Yes, Trinity was near the Mount Everest, but agent Smith kidnapped her. Now, send me the string PRIMENUMBER.
          Then, you will receive a noisy message. Take every character on prime number letter positions (2,3,5...), and put these characters
          together to form a string and send me this string. ALERT! The string can not be hardcoded in your software, you must invent an algorithm
          for this to sharpen your analytical abilities in order to fight enemy agents better.

Sent: PRIMENUMBER
Received: XLOZGP.R.ACLHCOGAGTER

Sent: LOG.CHAT
Received: Correct. It is crucial to record all our communication and send it to Sion. Therefore, re-code your software to store all our
          communication to a file. It must be clear from the log who sent what. Then send me the string Trinity.

Sent: Trinity
Received: Now you need to study the ship manuals to be able to save Trinity. The questions are in a foreign language. Post the correct
          reply as an answer. But must also be able to explain the topic and your answer! Here is the first one:
          Akym terminom oznacujeme pocet zmien urovne signalu za sekundu [2 slova]? (prednaska 9)

Sent: baud rate
Received: Good one! Here is another one: Aky je maximalny pocet pripojenych zariadeni na rozhrani rs485? (prednaska 9)

Sent: 32
Received: Good answer, great job! For now, this is enough; if you've got this far and accomplished
          all the tasks you will have full score.  DO NOT SHARE YOUR CODE! EVERY YEAR THERE ARE AT LEAST 5
          PLAGIARISTS DETECTED AND EXECUTED AS TRAITORS ON THIS MISSION (BLOCK 3). IF YOU WANT A BONUS MISSION FOR EXTRA POINTS SEND ME THE WORD BONUS. (omg)

Sent: BONUS
Received: Here is the bonus task. Write a C program that simulates the fetch stage of the instruction cycle.
          Your program should consist of the following components: Define an array to represent the memory of the simulated computer.
          Assume a simple memory layout with a fixed size (e.g., 64 words). Implement a function named fetchInstruction that takes the program counter (PC) as an argument,
          fetches the instruction located at the specified memory address, and displays it. Write a separate function that initializes the memory with sample instructions,
          simulates the fetch stage by repeatedly fetching instructions from memory based on the program counter, and displays each fetched instruction. Hints:
          Use a loop to repeatedly fetch instructions until a halt condition is met (e.g., reaching the end of the program). You can use simple instructions such as NOP (no operation)
          or MOV (move data) for demonstration purposes. Ensure error handling for cases where the program counter exceeds the memory size.

Collapse
```
