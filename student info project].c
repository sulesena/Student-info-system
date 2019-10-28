#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct details {
	char firstname[20];
	char lastname[20];
	char department[30];
	char ID[10];
	char age[5];
	char status[20];
} student;

void freadline(void* destination, size_t size, size_t count, FILE* fptr);
void fwriteline(void* source, size_t size, size_t count, FILE* fptr);

int main()
{
	int k,con,menu,i,found, search;
	FILE *point,*pointhold, *datafile;
	char namecheck[20],idcheck[20],deletename[20],deletesurname[20];
	char *sis ="student_information.txt";
	char *replica = "replica.txt";
	char *data = "data.txt";
	char id_string[20];

	// Check for the last ID and number of students registered.
	int id, total;
	datafile = fopen(data, "r");
	if (fscanf(datafile, "%d %d", &id, &total) != 2)
	{
		id = 171103000;
		total = 0;
	}
	fclose(datafile);
	
	int regnumber;
	do
	{
		system("cls");
		printf("1.register student\n2.display all the students\n3.search student\n4.change status of student\n5.delete\n6.exit\n");
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:
				system("cls");
				point=fopen(sis,"ab");
				printf("enter the number of students to register");
				scanf("%d",&regnumber);
				total += regnumber;
				for (i=0;i<regnumber;i++)
				{
					// Clean up student.
					memset(&student, 0, sizeof(student));

					printf("enter the firstname ");
					scanf("%s",&student.firstname);
					printf("enter the lastname ");
					scanf("%s",&student.lastname);
					printf("enter the department ");
					scanf("%s",&student.department);
					printf("enter the age ");
					scanf("%s",&student.age);
					printf("enter the status ");
					scanf("%s",&student.status);
					
					id++; 
					sprintf(id_string, "%d", id);
					strcpy(student.ID, id_string);
					
					fwriteline(&student, 1, sizeof(student), point);
					system("cls");
				}
				
				datafile = fopen(data, "w");
				fprintf(datafile, "%d %d", id, total);
				fclose(datafile);
				
				fclose(point);
				break;
			case 2:
				system("cls");
				point=fopen(sis,"rb+");
				for (i=0; i<total; i++)
				{
					memset(&student, 0, sizeof(student));
					// Read the data from the file.
					freadline(&student, 1, sizeof(student), point);
					// Print it to the screen.
					if (strcmp(student.status, "studying") == 0)
					{
						fwriteline(&student, 1, sizeof(student), stdout);
					}
				}
				fclose(point);
				break;
			case 3:
				system("cls");
				memset(&student, 0, sizeof(student));
				point=fopen(sis,"rb");
				
				printf("1.search by firstname\t2.search by id_number\n");
				scanf("%d",&search);
				found = 0;
				if(search==1)
				{
					printf("enter the firstname of the student...\n");
					scanf("%s",&namecheck);
					for (i=0;i<total;i++)
					{
						freadline(&student, 1, sizeof(student), point);
						if(strcmp(namecheck,student.firstname)==0)
						{
							found = 1;
							fwriteline(&student, 1, sizeof(student), stdout);
						}
					}
					// If we've reached the end and haven't found anything
					if(found==0)
					{
						printf("the name %s was not found..\n",namecheck);
					}
				}
				if(search==2)
				{
					printf("enter the ID_number\n");
					scanf("%s",&idcheck);
					for(i=0;i<total;i++)
					{
						freadline(&student, 1, sizeof(student), point);
						if(strcmp(idcheck,student.ID)==0)
						{
							found = 1;
							fwriteline(&student, 1, sizeof(student), stdout);
							break;
						}
					}
					if(found==0)
					{
						printf("the id %s was not found\n",idcheck);
					}
				}
				fclose(point);
				break;
			case 4:
			// TODO:
			// Go through the file
			// Get each student's details and write to another file
			// When you find him,
			// 	Change his status through the struct
			//	To rewrite:
			//		Write the modified details to the second file
			//	Delete the old file and rename the new one
			// If you don't find him let the user know
				point = fopen(sis,"rb");
				pointhold = fopen(replica, "wb");
				printf("Enter the students id number: ");
				scanf("%s",&idcheck);
				found = 0;
				for (i = 0; i < total; i++)
				{
					freadline(&student, 1, sizeof(student), point);
					if (strcmp(student.ID, idcheck) == 0
						&& strcmp(student.status, "studying") == 0)
					{
						found = 1;
						memset(&student.status, 0, sizeof(student.status));
						strcpy(student.status, "not studying");
					}
					else if (strcmp(student.ID, idcheck) == 0
						&& strcmp(student.status, "not studying") == 0)
					{
						found = 1;
						memset(&student.status, 0, sizeof(student.status));
						strcpy(student.status, "studying");
					}
					fwriteline(&student, 1, sizeof(student), pointhold);
				}
				
				fclose(point);
				fclose(pointhold);
				remove(sis);
				rename(replica, sis);
				
				if (found = 0)
				{
					printf("There's no student with ID %s\n", idcheck);
				}
				else
				{
					printf("%s's status has been changed.\n", idcheck);
				}
				break;
				/*point=fopen(sis,"r+");
				point=fopen(sis,"w");
				printf("enter the students id number");
				scanf("%d",&search);
				for(i=0;!feof(point);i++)
				{
						fscanf(point,"%s\t%s\t%s\t%d\t%d\t%s\n",&sis[i].firstname,&sis[i].lastname,&sis[i].department,&sis[i].ID,&sis[i].age,&sis[i].status);
						if(search==sis[i].ID)
						{
							printf("1.not_studying\n2.studying\n");
							scanf("%d",&change);
							if(change==1)
							{ 
								strcpy(sis[i].status,"not_studying");
								printf("<<<<<<<<<the status of %s %s has successfully been changed>>>>>>>>>>>>>\n",sis[i].firstname,sis[i].lastname);
								break;
							}
							else
							{
								strcpy(sis[i].status,"studying");
								printf("<<<<<<<<<the status of %s %s has successfully been changed>>>>>>>>>>>>>\n",sis[i].firstname,sis[i].lastname);
								break;
							}
						}
						if(feof(point) && search!=sis[i].ID)
						{
							printf("!!!! the id %d does not exist or check for error!!\n",sis[i].ID);
							printf("..........................................................\n");
							break;
						}
				}
					break;*/
			case 5:
					printf("enter the name to delete\n");
					scanf("%s",&deletename);
					printf("enter the surname to delete\n");
					scanf("%s",&deletesurname);
					point=fopen(sis,"rb");
					pointhold=fopen(replica,"wb");
					found = 0;
					for(i=0;i<total;i++)
					{
						freadline(&student, 1, sizeof(student), point);
						if((strcmp(student.firstname,deletename)==0) && (strcmp(student.lastname,deletesurname)==0))
						{
							found = 1;
						}
						else
						{
							fwriteline(&student, 1, sizeof(student), pointhold);
						}
					}

					fclose(point);
					fclose(pointhold);
					// Delete the previous file.
					remove(sis);
					// Rename the new file.
					rename(replica, sis);

					// Let the user know if the student was deleted.
					if (found == 0)
					{
						printf("the name %s and surname %s is not in the file!!!\n", deletename, deletesurname);
					}
					else
					{
						printf("the name has been deleted\n");
						// After deleting, no of students should reduce.
						total--;
						datafile = fopen(data, "w");
						fprintf(datafile, "%d %d", id, total);
						fclose(datafile);
					}
					break;
			case 6:
				printf("<<<<<<<<<<<<<<<<<SEE YOU NEXT TIME>>>>>>>>>>>>>>\n");
				return 0;
					
			default:
				printf("===========no such menu choice exist's==================\n");
		}
			
		printf("do you want to continue(1.yes/2.no)");
		scanf("%d",&con);
		if(con==1)
		{
			k=1;
		}
		else
		{
			k=0;
		}
				
	}while(k==1);

	return 0;
	
	

	
}

//
// Write a line (including the newline character) to a file.
//
void fwriteline(void* source, size_t size, size_t count, FILE* fptr)
{
	fwrite(source, size, count, fptr);
	fwrite("\n", 1, sizeof(char), fptr);
}

//
// Read a line, (excluding the newline charcter) from a file
//	and move the cursor to next line.
void freadline(void* destination, size_t size, size_t count, FILE* fptr)
{
	fread(destination, size, count, fptr);
	fseek(fptr, 1*sizeof(char), SEEK_CUR);
}
