# Adventure

> CS-344 (Operating Systems I) Program

An adventure-type game, written in C

## How to compile and run:
> 1. Copy/paste all the program code into a directory
> 2. In that directory, type the command: `chmod +x makeBoth` to make *makeBoth* executable
> 3. Type the command: `makeBoth` to run the makefile
> 4. Type the command: `buildrooms` to run the *buildrooms* program
> 5. Type the command: `adventure` to run the *adventure* program
> 6. Find the End Room to win the game

## How the game works:
> - buildrooms creates a new directory inside the working directory
> - Inside that directory, seven rooms are created
> - The name of each room is chosen randomly from a list of ten possible names
> - Each room has:
> - - Name
> - - Type (start, end, or mid)
> - - Between 3 and 6 outbound connections (to other rooms)

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

## Concepts learned:
> hfkdhfdhk

