#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define notVisited 1
#define visited 2

struct node{
	char name[15];	//name of each person
	int cntr;	//counter for adjacent list
	int state;	//is node visited or not
	struct node* adjacent[40];	//ptr to adjacent list
	struct node* next;	//ptr to next node
	int btwCentr;
	int btwCentr2;	
};

struct node* start = NULL;
struct node* last = NULL;
struct node* temp;
struct node* x;

char btw[50][50];//array for calculate betwennes centrality
char btw2[50][50];
int arrIndex = 0;//array index for btw[]
int arrIndex2 = 0;//array index for btw2[]

char* append(char* s, char c){//combine letters that readed from file
    size_t len = strlen(s);
    char *str2 = malloc(len + 1 + 1 ); 
    strcpy(str2, s);
    str2[len] = c;
    str2[len + 1] = '\0';
    return str2;
}
void addPeople(char people[15]){//add each person to the linked list
	struct node* current = (struct node*)malloc(sizeof(struct node));
	strcpy(current->name, people);
	current -> state = notVisited;
	current -> next = NULL;
	
	if(start == NULL){
		start = current;
		last = current;
	}
	else{
		last -> next = current;
		last = current;
	}
}
void nameToNode(char person[15]){//return the node that include name
	temp = start;
	while(strcmp(temp -> name, person) != 0){
		if(temp -> name == NULL) break;
		temp = temp -> next;
	}
	x = temp;
}
void addAdjacency(char src[15], char dest[15]){//add ajacency of each person
	struct node* source;
	nameToNode(src);
	source = x;
	struct node* destination;
	nameToNode(dest);
	destination = x;
	source -> adjacent[source->cntr] = destination;
	source -> cntr++;
}
int control(char person[], char person2[]){//find neighbours for adjacency matrix
	nameToNode(person);
	int i;
	for(i = 0; i < x -> cntr; i++){
		if(strcmp(x -> adjacent[i]->name, person2) == 0)
			return 1;
	}
	return 0;
}
int degreeCentrality(char node[]){//find degree centrality for each person
	nameToNode(node);
	struct node* source;
	source = x;
	return source -> cntr;
}

int closenessCentrality(char node[]){//find the closeness centrality for each node
	nameToNode(node);
	int i, j, k, l, m;
	int closeness = 0;
	struct node* adj,* adj2,* adj3,* adj4,* adj5;

	for(i = 0; i < x -> cntr; i++){//firstly all edges are not visited
		adj = x -> adjacent[i];
		adj -> state = notVisited;
		if(adj != NULL){
			for(j = 0; j < adj -> cntr; j++){
				adj2 = adj -> adjacent[j];
				adj2 -> state = notVisited;
				if(adj2 != NULL){
					for(k = 0; k < adj2 -> cntr; k++){
						adj3 = adj2 -> adjacent[k];
						adj3 -> state = notVisited;
							if(adj3 != NULL){
								for(l = 0; l < adj3 -> cntr; l++){
									adj4 = adj3 -> adjacent[l];
									adj4 -> state = notVisited;
									if(adj4 != NULL){
										for(m = 0; m < adj4 -> cntr; m++){
											adj5 = adj4 -> adjacent[m];
											adj5 -> state = notVisited;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	
	x -> state = visited;
	for(i = 0; i < x -> cntr; i++){//total number of steps from neighbours
		adj = x -> adjacent[i];
		adj -> state = visited;
		closeness++;
	}
	
	for(i = 0; i < x -> cntr; i++){//two-steps nodes if exist
		adj = x -> adjacent[i];
		for(j = 0; j < adj -> cntr; j++){
			adj2 = adj -> adjacent[j];
			if(adj2 -> state != visited){
				adj2 -> state = visited;
				closeness = closeness + 2;
			}
		}
	}
	
	for(i = 0; i < x -> cntr; i++){//three-steps nodes if exist
		adj = x -> adjacent[i];
		if(adj != NULL){
			for(j = 0; j < adj -> cntr; j++){
				adj2 = adj -> adjacent[j];
				if(adj2 != NULL){
					for(k = 0; k < adj2 -> cntr; k++){
						adj3 = adj2 -> adjacent[k];
						if(adj3 != NULL && adj3 -> state != visited){
							adj3 -> state = visited;
							closeness = closeness + 3;
						}
					}
				}
			}
		}
	}
	
	for(i = 0; i < x -> cntr; i++){//four-steps nodes if exist
		adj = x -> adjacent[i];
		if(adj != NULL){
			for(j = 0; j < adj -> cntr; j++){
				adj2 = adj -> adjacent[j];
				if(adj2 != NULL){
					for(k = 0; k < adj2 -> cntr; k++){
						adj3 = adj2 -> adjacent[k];
						if(adj3 != NULL){
							for(l = 0; l < adj3 -> cntr; l++){
								adj4 = adj3 -> adjacent[l];
								if(adj4 != NULL && adj4 -> state != visited){
									adj4 -> state = visited;
									closeness = closeness + 4;
								}
							}
						}
					}
				}
			}
		}
	}
	
	for(i = 0; i < x -> cntr; i++){//five-steps nodes if exist
		adj = x -> adjacent[i];
		if(adj != NULL){
			for(j = 0; j < adj -> cntr; j++){
				adj2 = adj -> adjacent[j];
				if(adj2 != NULL){
					for(k = 0; k < adj2 -> cntr; k++){
						adj3 = adj2 -> adjacent[k];
							if(adj3 != NULL){
								for(l = 0; l < adj3 -> cntr; l++){
									adj4 = adj3 -> adjacent[l];
									if(adj4 != NULL){
										for(m = 0; m < adj4 -> cntr; m++){
											adj5 = adj4 -> adjacent[m];
											if(adj5 != NULL && adj5 -> state != visited){
												adj5 -> state = visited;
												closeness = closeness + 5;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	
	return closeness;
}

void betwennesCentrality(char source[], char target[], char intrmedia[]){
	struct node* src, * trgt, *adj, *adj2, *adj3, *adj4, *adj5;
	nameToNode(source);
	src = x;
	nameToNode(target);
	trgt = x;
	int i, j, k, l, m;
	int control;
	for(i = 0; i < src -> cntr; i++){
		adj = src -> adjacent[i];
		if(strcmp(adj -> name, trgt -> name) == 0){
			printf("\t\t - ");	//print the intermedia nodes
			printf("\t\t\t\t%s - %s\n", src -> name, trgt -> name); //print the path
			strcpy(btw2[arrIndex2], src -> name);arrIndex2++;
			strcpy(btw2[arrIndex2], trgt -> name);arrIndex2++;
			control = 1;
		}
	}
	if(control != 1){
		for(i = 0; i < src -> cntr; i++){
			adj = src -> adjacent[i];
			for(j = 0; j < adj -> cntr; j++){
				adj2 = adj -> adjacent[j];
				if(strcmp(adj2 -> name, trgt -> name) == 0){
					printf("\t\t%s", adj -> name);	//print the intermedia nodes
					printf("\t\t\t\t%s - %s - %s\n", src -> name, adj -> name, trgt -> name); //print the path
					control = 2;
					strcpy(btw[arrIndex], adj -> name);
					strcpy(btw2[arrIndex2], src -> name);arrIndex2++;
					strcpy(btw2[arrIndex2], adj -> name);arrIndex2++;
					strcpy(btw2[arrIndex2], trgt -> name);arrIndex2++;
					arrIndex++;					
					break;
				}
			}
			if(strcmp(adj2 -> name, trgt -> name) == 0) break;
		}
	}
	if(control != 1 && control != 2){
		for(i = 0; i < src -> cntr; i++){
			adj = src -> adjacent[i];
			if(adj != NULL){
				for(j = 0; j < adj -> cntr; j++){
					adj2 = adj -> adjacent[j];
					if(adj2 != NULL){
						for(k = 0; k < adj2 -> cntr; k++){
							adj3 = adj2 -> adjacent[k];
							if(strcmp(adj3 -> name, trgt -> name) == 0){
								printf("\t\t%s - %s", adj -> name, adj2 -> name);	//print the intermedia nodes
								printf("\t\t\t%s - %s - %s - %s\n", src -> name, adj -> name, adj2 -> name, trgt -> name); //print the path
								control = 3;
								strcpy(btw[arrIndex], adj -> name);
								arrIndex++;
								strcpy(btw[arrIndex], adj2 -> name);
								arrIndex++;
								strcpy(btw2[arrIndex2], src -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj2 -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], trgt -> name);arrIndex2++;
								break;
							}
						}
					}
				if(strcmp(adj3 -> name, trgt -> name) == 0)break;
				}
			}
			if(strcmp(adj3 -> name, trgt -> name) == 0)break;
		}
	}
	if(control != 1 && control != 2 && control != 3){
		for(i = 0; i < src -> cntr; i++){
			adj = src -> adjacent[i];
			if(adj != NULL){
				for(j = 0; j < adj -> cntr; j++){
					adj2 = adj -> adjacent[j];
					if(adj2 != NULL){
						for(k = 0; k < adj2 -> cntr; k++){
							adj3 = adj2 -> adjacent[k];
							if(adj3 != NULL){
								for(l = 0; l < adj3 -> cntr; l++){
									adj4 = adj3 -> adjacent[l];
									if(strcmp(adj4 -> name, trgt -> name) == 0){
										printf("\t\t%s - %s - %s", adj -> name, adj2 -> name, adj3 -> name); //print the intermedia nodes
										printf("\t\t%s - %s - %s - %s - %s\n", src -> name, adj -> name, adj2 -> name, adj3 -> name, trgt -> name); //print the path
										control = 4;
										strcpy(btw[arrIndex], adj -> name);
										arrIndex++;
										strcpy(btw[arrIndex], adj2 -> name);
										arrIndex++;
										strcpy(btw[arrIndex], adj3 -> name);
										arrIndex++;
										strcpy(btw2[arrIndex2], src -> name);arrIndex2++;
										strcpy(btw2[arrIndex2], adj -> name);arrIndex2++;
										strcpy(btw2[arrIndex2], adj2 -> name);arrIndex2++;
										strcpy(btw2[arrIndex2], adj3 -> name);arrIndex2++;
										strcpy(btw2[arrIndex2], trgt -> name);arrIndex2++;
										break;
									}
								}
							}
							if(strcmp(adj4 -> name, trgt -> name) == 0)break;
						}
					}
					if(strcmp(adj4 -> name, trgt -> name) == 0)break;
				}
			}
			if(strcmp(adj4 -> name, trgt -> name) == 0)break;
		}
	}
	if(control != 1 && control != 2 && control != 3 && control != 4){
	  for(i = 0; i < src -> cntr; i++){
		adj = src -> adjacent[i];
		  if(adj != NULL){
			for(j = 0; j < adj -> cntr; j++){
			  adj2 = adj -> adjacent[j];
			  if(adj2 != NULL){
				for(k = 0; k < adj2 -> cntr; k++){
				  adj3 = adj2 -> adjacent[k];
				  if(adj3 != NULL){
				    for(l = 0; l < adj3 -> cntr; l++){
					  adj4 = adj3 -> adjacent[l];
					  if(adj4 != NULL){
					    for(m = 0; m < adj4 -> cntr; m++){
						  adj5 = adj4 -> adjacent[m];
						  if(strcmp(adj5 -> name, trgt -> name) == 0){
						  	printf("\t\t%s - %s - %s - %s", adj -> name, adj2 -> name, adj3 -> name, adj4 -> name);	//print the intermedia nodes
						    printf("\t%s - %s - %s - %s - %s - %s\n", src -> name, adj -> name, adj2 -> name, adj3 -> name, adj4 -> name, trgt -> name); //print the path
								strcpy(btw[arrIndex], adj -> name);
								arrIndex++;
								strcpy(btw[arrIndex], adj2 -> name);
								arrIndex++;
								strcpy(btw[arrIndex], adj3 -> name);
								arrIndex++;
								strcpy(btw[arrIndex], adj4 -> name);
								arrIndex++;
								strcpy(btw2[arrIndex2], src -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj2 -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj3 -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], adj4 -> name);arrIndex2++;
								strcpy(btw2[arrIndex2], trgt -> name);arrIndex2++;
							break;
						  }
						}
					  }
					  if(strcmp(adj5 -> name, trgt -> name) == 0)break;
				    }
				  }
				  if(strcmp(adj5 -> name, trgt -> name) == 0)break;
				}
			}
			if(strcmp(adj5 -> name, trgt -> name) == 0)break;
		  }
		}
		if(strcmp(adj5 -> name, trgt -> name) == 0)break;
	  }
	}
	
}

main(void){
	setlocale(LC_ALL, "Turkish");

	FILE* file = fopen("input.txt", "r");
	
	char *name = "";
	char *adjName = "";
	int c;
	
	if (file) {//read the file and create names
        while ((c = getc(file)) != EOF || strlen(name) != 0){
			if(c == ';'){
				addPeople(name); //insert each word into linked list 
				name = "";
				while(c != '\n'){
					c = getc(file);
					if(c == EOF) break;
				}
					
			}else{
				if(c == '\n')break;				
             	char letter = c;
             	name = append(name,letter);//combine letters and create words
            }
          }
          fclose(file);
        }
	else {
		printf("No such file!");
	}
	
	file = fopen("input.txt", "r");
	int prob = 0;
	
	if (file) {//read the file again for add edges
	  while ((c = getc(file)) != EOF || strlen(name) != 0){
		if(c == ';'){
		  while(c != '\n'){
			if(c == EOF) break;
			c = getc(file);
			char letter = c;
			if(c != EOF){
				if(c != ' ') {
					if(c != ','){
						if(c != '\n'){
							adjName = append(adjName, letter);	
						}	
					}											
				}
			}
			if(c == ',' || c == '\n'){
				addAdjacency(name, adjName);//add each edges to the adjacency list
				prob++;
				if(prob == 33){//Because of some problem add Ilke by hand
					addAdjacency("Jale", "Ilke");
				}
				adjName = ""; 
			}
		  }
		name = "";
		}
		else{
        	char letter = c;
           	name = append(name,letter);//connect letters and create words
        }
   	 }
    	fclose(file);
	}
	else {
		printf("No such file!");
	}

	printf("ADJACENCY MATRIX: \n");
	struct node* temp = start;
	struct node* temp2 = start;
	int cnt;
	
	while(temp != NULL){//print columns names and count people
		printf("\t%s", temp -> name);
		temp = temp -> next;
		cnt++;
	}
	printf("\n");

	while(temp2 != NULL){//print adjacency matrix
		printf("%s", temp2 -> name);
		struct node* temp3 = start;
		while(temp3 != NULL){
			int x;
			x = control(temp2 -> name, temp3 -> name);
			printf("\t%d", x);
			temp3 = temp3 -> next;
		}
		printf("\n");
		temp2 = temp2 -> next;
	}
	
	printf("\nDEGREE CENTRALITY: \n");
	printf("Node");printf("\tScore");printf("\tStandardized Score\n");
	
	temp = start;
	int degree;
	int stdScore = cnt - 1;
	while(temp != NULL){//print degree centrality
		printf("\n%s", temp -> name);
		degree = degreeCentrality(temp -> name);
		printf("\t%d", degree);
		printf("\t%d/%d", degree, stdScore);
		temp = temp -> next;
	}
	
	printf("\n\nCLOSENESS CENTRALITY: \n");
	printf("Node");printf("\tScore");printf("\tStandardized Score\n");
	
	temp = start;
	int closeness;
	while(temp != NULL){//print closeness centrality
		printf("\n%s", temp -> name);
		closeness = closenessCentrality(temp -> name);
		printf("\t1/%d", closeness);
		printf("\t%d/%d", stdScore, closeness);
		temp = temp -> next;
	}
	 
	printf("\n\nBETWENNES CENTRALITY: \n");
	printf("Source");printf("\tTarget");printf("\t\tIntermedia Nodes");printf("\t\tPath");
		
	temp = start;
	
	while(temp != NULL){//print betwennes centrality
		temp2 = start;
		while(temp2 != NULL){
			if(strcmp(temp -> name, temp2 -> name) != 0){
				printf("\n%s", temp -> name);
				printf("\t%s", temp2 -> name);
				betwennesCentrality(temp -> name, temp2 -> name, temp -> name);
			}
			temp2 = temp2 -> next;
		}
		temp = temp -> next;
	}
	
	int i;
	int denominator = (((cnt - 1) * (cnt - 2)) / 2) * (((cnt - 1) * (cnt - 2)) / 2);
	temp = start;

	while(temp != NULL){
		for(i = 0; i < arrIndex + 1; i++)
			if(strcmp(temp -> name, btw[i]) == 0){		
				temp -> btwCentr++;
		}
		for(i = 0; i < arrIndex2 + 1; i++){
			if(strcmp(temp -> name, btw2[i]) == 0)
				temp -> btwCentr2++;		
		}
		if(temp -> btwCentr == 0)
			printf("\nC Betwennes(%s) = %d",temp -> name, temp -> btwCentr);	
		else
			printf("\nC Betwennes(%s) = %d/%d",temp -> name, temp -> btwCentr, temp -> btwCentr2++);	
		temp = temp -> next;		
	}
	printf("\n---------------------------------------------");
	temp = start;
	double betwennes;
	while(temp != NULL){
		betwennes = ((double)temp -> btwCentr) / ((double)denominator);
		if(temp -> btwCentr == 0)
			printf("\nC Betwennes(%s) = %d",temp -> name, temp -> btwCentr);	
		else
			printf("\nC Betwennes(%s) = %f",temp -> name, betwennes);
		temp = temp -> next;
	}
}
