/**********************************
 * Name: Jake Seawell
 * Date: 7/13/19
 * Assignment: CS344-Program2-Buildrooms
 * Description: This program is for program2, and will create a new
 * directory in the curr dir, and add 7 room files into that new dir.
 * Each room file should contain one room with a name and a type.
 * Room names will be hard-coded into the program, and randomly assigned
 * to each new room created.
 *
 * *Many of the functions in this program 
 * were modified from instructor/course provided code*
 *
 * ******************************/

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Room struct definition
struct Room
{
    int roomID;
    char name[8];
    char typeOfRoom[11];
    int numConns;
    struct Room* conns[6];
};

//Used for start and end room assignment
int roomTypeCtr = 0;

//For incrementing room files
int fileNum = 1;

//Name pick switches
int officePicked = 0;
int garagePicked = 0;
int kitchenPicked = 0;
int bedroomPicked = 0;
int bathroomPicked = 0;
int basementPicked = 0;
int atticPicked = 0;
int denPicked = 0;
int hallwayPicked = 0;
int playroomPicked = 0;

//create file path buffer
char filePath[25];

//This function makes a new dir in curr dir
//to hold 7 rooms
void makeRoomDirectory()
{
    int pid = 0;   
    //Get process ID
    pid = getpid();
    
    //Append process ID to text and write to filename
    sprintf(filePath, "./seawellj.rooms.%d", pid);
    
    //Create new directory in current dir
    mkdir(filePath, 0777);
    //sprintf(fullFilePath, "./seawellj.rooms.%d", pid);
}

/*************************************/


// Returns 1 if all rooms have 3 or more connections, 0 otherwise
int IsGraphFull(struct Room** allRooms)
{
    int i=0;
    for (i=0; i<7; i++){
        if (allRooms[i]->numConns < 3)
            return 0;
    }
    return 1;
}

//Chooses a random name from 10 different room options
//Each name can only be selected once
void PickRandomName(struct Room *x)
{
	int namePicked = 0;

	while (namePicked == 0){

		int num = (rand() % 10) + 1;
		if (num == 1 && officePicked == 0){
			strcpy(x->name, "Office");
			officePicked = 1;
			namePicked = 1;
		}
		if (num == 2 && garagePicked == 0){
			strcpy(x->name, "Garage");
			garagePicked = 1;
			namePicked = 1;
		}
		if (num == 3 && kitchenPicked == 0){
			strcpy(x->name, "Ktchn");
			kitchenPicked = 1;
			namePicked = 1;
		}	
		if (num == 4 && bedroomPicked == 0){
			strcpy(x->name, "Bdrm");
			bedroomPicked = 1;
			namePicked = 1;
		}
		if (num == 5 && bedroomPicked == 0){
			strcpy(x->name, "Bthrm");
			bathroomPicked = 1;
			namePicked = 1;
		}
		if (num == 6 && basementPicked == 0){
			strcpy(x->name, "Bsmt");
			basementPicked = 1;
			namePicked = 1;
		}
		if (num == 7 && atticPicked == 0){
			strcpy(x->name, "Attic");
				atticPicked = 1;
				namePicked = 1;
		}
		if (num == 8 && denPicked == 0){
			strcpy(x->name, "Den");
			denPicked = 1;
			namePicked = 1;
		}
		if (num == 9 && hallwayPicked == 0){
			strcpy(x->name, "Hallway");
			hallwayPicked = 1;
			namePicked = 1;
		}
		if (num == 10 && playroomPicked == 0){
			strcpy(x->name, "Playrm");
			playroomPicked = 1;
			namePicked = 1;
		}	
	}
}

// Returns a random Room, 
// start and end are first 2 rooms assigned, to ensure they get assigned
struct Room GetRandomRoom(struct Room** allRooms)
{
    //Room to return from function
    struct Room returnRoom;
    
    //Generate random numbers
    int num = (rand() % 7) + 1;
    int typeNum = (rand() % 6) + 1;
    
    if (num == 1){
        returnRoom = *allRooms[0];
    }
    else if (num == 2){
        returnRoom = *allRooms[1];
    }
    else if (num == 3){
        returnRoom = *allRooms[2];
    }
    else if (num == 4){
        returnRoom = *allRooms[3];
    }
    else if (num == 5){
        returnRoom = *allRooms[4];
    }
    else if (num == 6){
        returnRoom = *allRooms[5];
    }
    else if (num == 7){
        returnRoom = *allRooms[6];
    }
   
    //Assign start room to first room
    //End room to next
    if (roomTypeCtr == 0){
        strcpy(allRooms[typeNum]->typeOfRoom, "START_ROOM");
        roomTypeCtr ++;
    }
    else if (roomTypeCtr == 1){
        strcpy(allRooms[typeNum]->typeOfRoom, "END_ROOM");
        roomTypeCtr ++;
    }

    return returnRoom;
}


// Returns 1 if Room x has < 6 outbound connections,
//0 otherwise
int CanAddConnectionFrom(struct Room x)
{
    if (x.numConns < 6)
        return 1;
    else
        return 0;
}


// Returns 1 if a connection from Room x to Room y already exists,
//0 otherwise
int ConnectionAlreadyExists(struct Room x, struct Room y)
{
    int i=0;
    for (i=0; i<6; i++){
        if (x.conns[i] != NULL)
            if (x.conns[i]->roomID == y.roomID)
                return 1;
    }
    return 0;
}



// Connects Room y to Room x
void ConnectRoom(struct Room *x, struct Room *y)
{
    //get numConns for index
    int xIndex = x->numConns;
    
    //assign y as connection to x
    x->conns[xIndex] = y;
    
    //increment numConns
    x->numConns ++;
}



// Returns 1 if Rooms x and y are the same Room, 0 otherwise
int IsSameRoom(struct Room x, struct Room y)
{
    if (x.roomID == y.roomID)
        return 1;
    else
        return 0;
}


// Adds a connection between two random rooms
void AddRandomConnection(struct Room** allRooms)
{
    struct Room A;
    struct Room B;
    
    //Get a random room that is not full (of connections)
    while(1)
    {
        A = GetRandomRoom(allRooms);
        
        if (CanAddConnectionFrom(A) == 1)
            break;
    }
    
    //Get a different random room that is not full (of connections),
    //and is not already connected to the first room
    do
    {
        B = GetRandomRoom(allRooms);
    }
    while(CanAddConnectionFrom(B) == 0 || IsSameRoom(A, B) == 1 || ConnectionAlreadyExists(A, B) == 1);
    
    //Connect the two rooms together
    int i=0;
    for (i=0; i<7; i++){
        int j=0;
	for (j=0; j<7; j++){
            
            if (allRooms[i]->roomID == A.roomID && allRooms[j]->roomID == B.roomID){
                ConnectRoom(allRooms[i], allRooms[j]);
                ConnectRoom(allRooms[j], allRooms[i]);
            }
        }
    }
}


//Print the contents of a room to console
void PrintRoom(struct Room A)
{
    printf("Room Name: %s\n", A.name);
    int i=0;
    for (i=0; i<6; i++){
        if (A.conns[i] != NULL)
            printf("Connection %d: %s\n", i+1, A.conns[i]->name);
    }
    printf("Room Type: %s\n\n", A.typeOfRoom);
}

//Print the contents of a room to unique file (incremented filenames)
void PrintRoomFile(struct Room A)
{
    FILE* fptr;
    
    //Create filename (incemented)
    char filename[256];
    sprintf (filename, "/RoomFile#%d", fileNum);
    fileNum++;
   
    //create full file path 
    char fullFilePath[256];
    memset(&fullFilePath, '\0', sizeof(fullFilePath));
    strcpy(fullFilePath, filePath);
    strcat(fullFilePath, filename);

    //Open file for writing
    fptr = fopen(fullFilePath, "w");

    //Print contents to file
    fprintf(fptr, "Room Name: %s\n", A.name);
    int i=0;
    for (i=0; i<6; i++){
        if (A.conns[i] != NULL)
            fprintf(fptr, "Connection %d: %s\n", i+1, A.conns[i]->name);
    }
    fprintf(fptr, "Room Type: %s\n", A.typeOfRoom);
    
    //Close file
    fclose(fptr);
}




/**********************************************/


int main()
{
    
    //Make room directory for room files
    makeRoomDirectory();

    //seed random number (do only once in program)
    srand(time(0));
    
    //create default room
    struct Room defaultRoom;
    defaultRoom.roomID = 0;
    strcpy(defaultRoom.name, "default");
    strcpy(defaultRoom.typeOfRoom, "MID_ROOM");
    defaultRoom.numConns = 0;
    defaultRoom.conns[0] = NULL;
    defaultRoom.conns[1] = NULL;
    defaultRoom.conns[2] = NULL;
    defaultRoom.conns[3] = NULL;
    defaultRoom.conns[4] = NULL;
    defaultRoom.conns[5] = NULL;
    
    //create 7 rooms
    struct Room room1, room2, room3, room4, room5;
    struct Room room6, room7;
    
    //Create array of room pointers
    struct Room* allRooms[7];   
 
    //Assign hard-coded values to rooms
    //Then assign random name to each
    room1 = defaultRoom;
    room1.roomID = 1;
    allRooms[0] = &room1;
    PickRandomName(&room1);
    
    room2 = defaultRoom;
    room2.roomID = 2;
    allRooms[1] = &room2;
    PickRandomName(&room2);

    room3 = defaultRoom;
    room3.roomID = 3;
    allRooms[2] = &room3;
    PickRandomName(&room3);

    room4 = defaultRoom;
    room4.roomID = 4;
    allRooms[3] = &room4;
    PickRandomName(&room4);

    room5 = defaultRoom;
    room5.roomID = 5;
    allRooms[4] = &room5;
    PickRandomName(&room5);

    room6 = defaultRoom;
    room6.roomID = 6;
    allRooms[5] = &room6;
    PickRandomName(&room6);

    room7 = defaultRoom;
    room7.roomID = 7;
    allRooms[6] = &room7;
    PickRandomName(&room7);
 
    // Create all connections in graph
    while (IsGraphFull(allRooms) == 0)
    {
        AddRandomConnection(allRooms);
    }
    
    //Print all room contents (either to console or file)
    int i=0;
    for (i=0; i<7; i++)
    {
	//Rooms to unique files
        PrintRoomFile(*allRooms[i]);
    }

    roomTypeCtr = 0;
    
    return 0;
}
