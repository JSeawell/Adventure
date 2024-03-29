# Adventure

> CS-344 (Operating Systems I) Program

An adventure-type game, written in C

## How to compile and run:
> 1. Copy/paste all the program code into a directory
> 2. In that directory, type the command: `chmod +x makeBoth` to make *makeBoth* executable
> 3. Type the command: `makeBoth` to run the makefile
> 4. Type the command: `buildrooms` to run the *buildrooms* program
> 5. Type the command: `adventure` to run the *adventure* program

## How the game works:
> The *buildrooms* program creates a new directory inside the working directory
> - Inside that directory, seven rooms are created
> - The name of each room is chosen randomly from a list of ten possible names
> - Each room has:  
>   - a Name (randomly chosen)  
>   - Between 3 and 6 random outbound connections (to other rooms)  
>   - a Type (start\[1\], end\[1\], or mid\[5\])  
> The *buildrooms* program will make all these connections
>
> The *adventure* program activates the game  
> - The player always starts in the START_ROOM  
> - The object of the game is to find the END_ROOM, by following the possible connections  
>   - If the user tries to go to an invalid room, they will find themself unsuccessful  
> - At any time, instead of choosing a new room, the user can type: `time`  
>   - This creates a new thread, which will display the current date and time, and write that timestamp to a new file, called `currentTime.txt`.  
> - When the game is over, the user will be shown his/her path to victory  

## Example run:
> `$ chmod +x makeBoth`  
> `$ makeBoth`  
> `$ buildrooms`  
> `$ adventure`  
> CURRENT LOCATION: Ktchn  
> POSSIBLE CONNECTIONS: Bsmt, Bdrm, Den.  
> WHERE TO ? \>`Bsmt`  
> CURRENT LOCATION: Bsmt  
> POSSIBLE CONNECTIONS: Attic, Bdrm, Ktchn, Garage.  
> WHERE TO? >`Attic`  
>  
> CURRENT LOCATION: Attic  
> POSSIBLE CONNECTIONS: Bsmt, Garage, Bdrm, Office.  
> WHERE TO? >`Office`  
>  
> CURRENT LOCATION: Office  
> POSSIBLE CONNECTIONS: Attic, Bdrm, Garage, Den.  
> WHERE TO? >`Den`  
>  
> YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!  
> YOU TOOK 4 STEPS. YOUR PATH TO VICTORY WAS:  
> Bsmt  
> Attic  
> Office  
> Den  
> `$`  

## Tech and/or concepts learned/used:
> - C language
> - Concurrency
> - Threads
> - Mutexes
> - File Access in C
> - C strings
> - Debugging with gdb and valgrind

