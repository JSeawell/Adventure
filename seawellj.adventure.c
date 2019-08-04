/**********************************
 * Name: Jake Seawell
 * Date: 7/13/19
 * Assignment: CS344-Program2-Adventure
 * Description: This program runs a game called adventure. 
 * This prgram needs to be run after running buildrooms,
 * which creates the roomfiles needed to play the game.
 * Once the game begins, the user will start in a room,
 * and the object of the game is to find the end room.
 * Each room is connected to other rooms, so you can move
 * through the rooms that are connected. The user can also
 * type "time", instead of a room, which will diplay the 
 * current time and date, and write/overwrite that data 
 * to a new file called currentTime. 
 *
 * ******************************/

//Include libraries
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int main()
{
    /************************************************************/
    //  This section of code is a modification of code provided
    //  by the professor/course
    /***********************************************************/ 

    int newestDirTime = -1; // Modified timestamp of newest subdir examined
    char targetDirPrefix[32] = "seawellj.rooms."; // Prefix we're looking for
    char newestDirName[256]; // Holds the name of the newest dir that contains prefix
    memset(newestDirName, '\0', sizeof(newestDirName));
    
    DIR* dirToCheck; // Holds the directory we're starting in
    struct dirent *fileInDir; // Holds the current subdir of the starting dir
    struct stat dirAttributes; // Holds information we've gained about subdir
    
    dirToCheck = opendir("."); // Open up the directory this program was run in
    
    if (dirToCheck > 0) // Make sure the current directory could be opened
    {
        while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
        {
            if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
            {
                //printf("Found the prefex: %s\n", fileInDir->d_name);
                stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry
                
                if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
                {
                    newestDirTime = (int)dirAttributes.st_mtime;
                    memset(newestDirName, '\0', sizeof(newestDirName));
                    strcpy(newestDirName, fileInDir->d_name);
                    //printf("Newer subdir: %s, new time: %d\n", fileInDir->d_name, newestDirTime);
                }
            }
        }
    }
    
    closedir(dirToCheck); // Close the directory we opened
    
    //printf("Newest directory found: %s\n", newestDirName);
    

    //  End of professor/course provided/modified code
    /******************************************************/

    //Struct to store rooms from files
    struct RoomFF
    {
        int roomID;
        char name[8];
        char typeOfRoom[11];
        int numConns;
        char conns[6][8];
    };

    //create 7 rooms
    struct RoomFF roomFF1, roomFF2, roomFF3, roomFF4, roomFF5, roomFF6, roomFF7;

    //Array of room pointers, each assigned to one
    //of the new rooms created above
    struct RoomFF* roomsFromFiles[7];
	roomsFromFiles[0] = &roomFF1;
	roomsFromFiles[1] = &roomFF2;
	roomsFromFiles[2] = &roomFF3;
	roomsFromFiles[3] = &roomFF4;
	roomsFromFiles[4] = &roomFF5;
	roomsFromFiles[5] = &roomFF6;
	roomsFromFiles[6] = &roomFF7;

    int roomNum = 1;
    
    DIR* dirToReadFrom;
    dirToReadFrom = opendir(newestDirName);

    //If directory exists
    if (dirToReadFrom > 0){
	//printf("Directory opened for reading\n");


	//Create new filename to be opened
	FILE* fptr;
        char charInFile;
        char filename[50];
        char temp[13];
        
        int i = 1;
        for (i = 1; i < 8; i++)
        {
            sprintf(temp, "/RoomFile#%d", i);
            
            strcpy(filename, newestDirName);
            strcat(filename, temp);
            
            //Open file for reading
            fptr = fopen(filename, "r");

	/***************************************************/
	// READ FILE AND STORE CONTENTS IN STRUCT/VARIABLES

            char roomName[8];
            char connection[8];
            char connections[6][8];
            char roomType[11];

            int linesInFile = 0;
            int numberOfConnections = 0;

	    //While file can be read, count # of lines
            while((charInFile = fgetc(fptr)) != EOF){
                if (charInFile == '\n')
                    linesInFile++;
            }
            //Number of connections in room
	    numberOfConnections = linesInFile - 2;

	    //Reset pointer to beginning of file
            fseek(fptr, 0, SEEK_SET);

	    //Store contents of each line in variables
            char* line_buff = NULL;
            size_t line_buff_size = 0;
            int line_count = 0;
            ssize_t line_size;
            
            int connNum = 0;
            line_size = getline(&line_buff, &line_buff_size, fptr);
            while (line_size >= 0){
                line_count++;
                if (line_count == 1){
                    sscanf(line_buff, "%*s %*s %s", roomName);
                }
                else if (line_count < linesInFile){
                    sscanf(line_buff, "%*s %*s %s", connection);
                    strcpy(connections[connNum], connection);
                    connNum++;
                }
                else
                    sscanf(line_buff, "%*s %*s %s", roomType);
                //printf("%s\n", line_buff);
                line_size = getline(&line_buff, &line_buff_size, fptr);
            }
            //Free line_buff
            line_buff = NULL;
            
	    //Assign values to room in room pointer array
	    roomsFromFiles[i - 1]->roomID = i;
	    strcpy(roomsFromFiles[i - 1]->name, roomName);
	    roomsFromFiles[i - 1]->numConns = 0;
	    int j = 0;
            for (j = 0; j < numberOfConnections; j++){
                strcpy(roomsFromFiles[i - 1]->conns[j], connections[j]);
                roomsFromFiles[i - 1]->numConns ++;
            }
            strcpy(roomsFromFiles[i - 1]->typeOfRoom, roomType);

         //PRINT ALL ROOMS AND INFO
         /*        
            printf("Room Name: %s\n", roomsFromFiles[i - 1]->name);
            int k=0;
            for (k=0; k<numberOfConnections; k++)
                printf("Connection #%d: %s\n", k+1, roomsFromFiles[i - 1]->conns[k]);
            printf("Room Type: %s\n", roomsFromFiles[i - 1]->typeOfRoom);
	*/
            
	    //Next room
	    roomNum++;

	    //close file        
            fclose(fptr);
    
        }
	roomNum = 0;
	int currentRoomIndex = -1;	

	//Find START_ROOM and print details
        int l=0;
        for (l=0; l<7; l++){
         	if (strcmp(roomsFromFiles[l]->typeOfRoom, "START_ROOM") == 0){
         		currentRoomIndex = l;
			printf("CURRENT LOCATION: %s\n", roomsFromFiles[l]->name);
         		printf("POSSIBLE CONNECTIONS: ");
         		int m = 0;
         		for (m = 0; m < roomsFromFiles[l]->numConns; m++){
         			if (m < (roomsFromFiles[l]->numConns - 1))
         				printf("%s, ", roomsFromFiles[l]->conns[m]);
         			else
         				printf("%s.\n", roomsFromFiles[l]->conns[m]);
			}
         		//printf("Room Type: %s\n", roomsFromFiles[l]->typeOfRoom);
        	} 
   	}
        
	size_t bufferSize = 0;
        char* lineEntered = NULL;
	char newString[8];        

	int stepCounter = 1;
	int endOfGame = 0;
	char roomsVisited[8][256];
	int roomsVisitedIndex = 0;

	//Until game is over (END_ROOM found)
	while (endOfGame == 0){

	//Display where to prompt
	printf("WHERE TO? >");

	//get user input
        getline(&lineEntered, &bufferSize, stdin);
        printf("\n");

	strcpy(newString, lineEntered);
	strtok(newString, "\n");      
	
	//Unless user enters "time"
	while (strcmp(newString, "time") != 0){
		//If user input doesn't match any of the room names
		if (strcmp(roomsFromFiles[0]->name, newString) != 0 && strcmp(roomsFromFiles[1]->name, newString) != 0 && strcmp(roomsFromFiles[2]->name, newString) != 0 && strcmp(roomsFromFiles[3]->name, newString) != 0 && strcmp(roomsFromFiles[4]->name, newString) != 0 && strcmp(roomsFromFiles[5]->name, newString) != 0 && strcmp(roomsFromFiles[6]->name, newString) != 0){
			//Display error msg
			printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
			
			//Reprint current room
			printf("CURRENT LOCATION: %s\n", roomsFromFiles[currentRoomIndex]->name);
         		printf("POSSIBLE CONNECTIONS: ");
         		int p=0;
         		for (p=0; p < roomsFromFiles[currentRoomIndex]->numConns; p++){
         			if (p < (roomsFromFiles[currentRoomIndex]->numConns - 1))
         				printf("%s, ", roomsFromFiles[currentRoomIndex]->conns[p]);
         			else
         				printf("%s.\n", roomsFromFiles[currentRoomIndex]->conns[p]);
			}

			//Reprompt for next room
			printf("WHERE TO? >");

			//get user input
        		getline(&lineEntered, &bufferSize, stdin);
        		printf("\n");

			strcpy(newString, lineEntered);
			strtok(newString, "\n");

		}	
		else
			break; //If it does match a room, break and dont check with other rooms
	}

	int n=0;	
	for (n=0; n<7; n++){
		//If user entered valid room OR "time"
		if (strcmp(roomsFromFiles[n]->name, newString) == 0){
			//If user entered valid room and it is the END_ROOM
			if (strcmp(roomsFromFiles[n]->typeOfRoom, "END_ROOM") == 0){
				strcpy(roomsVisited[roomsVisitedIndex], roomsFromFiles[n]->name);
				roomsVisitedIndex++;
				printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
				printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", stepCounter);
				int t=0;
				for (t=0; t < roomsVisitedIndex; t++){
					printf("%s\n", roomsVisited[t]);
				}
				//End game
				endOfGame = 1;
			}	
         		//If it's a valid room, but not the end room
			else{
				//Display room details
				currentRoomIndex = n;
				stepCounter ++;
				strcpy(roomsVisited[roomsVisitedIndex], roomsFromFiles[n]->name);
				roomsVisitedIndex++;
				printf("CURRENT LOCATION: %s\n", roomsFromFiles[n]->name);
         			printf("POSSIBLE CONNECTIONS: ");
         			int p=0;
         			for (p=0; p < roomsFromFiles[n]->numConns; p++){
         				if (p < (roomsFromFiles[n]->numConns - 1))
         					printf("%s, ", roomsFromFiles[n]->conns[p]);
         				else
         					printf("%s.\n", roomsFromFiles[n]->conns[p]);
				}
         			//printf("Room Type: %s\n", roomsFromFiles[n]->typeOfRoom);
        			break;
			}
		}
		//If user enters "time" instead of room name
		else if (strcmp("time", newString) == 0){

			char timeString[100];
			time_t timeNow;
  			struct tm * timeStruct;

			//Format time
  			time (&timeNow);
  			timeStruct = localtime (&timeNow);
			strftime(timeString, sizeof (timeString), "%l:%M%P, %A, %B %d, %Y", timeStruct);
			
			FILE* fptr2;

			char timeFilename[256];
    			strcpy (timeFilename, "currentTime.txt");    	

			//Open file for writing
    			fptr2 = fopen(timeFilename, "w");	

    			//Print contents to file
    			fprintf (fptr2, "%s\n", timeString);
    
    			//Close file
    			fclose(fptr2);
		
			//Print time to console/screen
			printf("%s\n\n", timeString);
			break; //break from loop and don't search rooms
		}
	}

	}//end of game while
    

    }
    //Directory does not exist, or failed to be opened
    else
        printf("Directory failed\n");

    return 0;
}
