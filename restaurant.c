// List of header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <limits.h>

#define V 17
 
int arr_quantity[30],arr_code[30],arr_profit[30];

char *food[]={"PLAIN DOSA","MASALA DOSA","IDLI","VEG MOMO","CHICKEN MOMO","MASALA PURI + SABJI","EGG TOAST","UPMA","POHA","MIXED FRUIT SALAD","ROTI + SABJI","ROTI + DUM ALOO","SNOW VIEW SPECIAL BREAKFAST","VEG THALI","SPECIAL VEG THALI","FISH THALI","CHICKEN THALI","MUTTON THALI","PANEER THALI","SNOW VIEW SPECIAL LUNCH","EGG ROLL","CHICKEN ROLL","EGG CHICKEN ROLL","MUTTON ROLL","EGG MUTTON ROLL","VEG ROLL","PANEER ROLL","CHICKEN PAKODA","DAHI VADA","SNOW VIEW SPECIAL DINNER"};  
int costPerPlate[]={60,75,60,65,85,45,50,40,40,85,45,55,120,135,150,180,200,265,165,300,65,80,100,155,170,45,55,125,50,300};
int profitPerPlate[]={15,12,15,20,30,10,15,10,12,25,10,15,45,30,35,55,60,80,50,90,20,35,45,60,70,20,25,55,25,100};

char *places[]={"DARJEELING","KALINGPONG","MIRIK","LEPCHAJAGOT","LOWER CHATAKPUR","SONADA","TINCHULEY","SITTONG","LAVA LOLEGAON","TRIVENI","SILIGURI","UPPER CHATAKPUR","NEW JALPAIGURI","GANGTOK","KURSEONG","SIMANA VIEW POINT","PELING"};

struct node
{
	int key;
	struct node *next;
};

// List of functions used in the program
struct node *createNode(int key);
void gotoxy(int x,int y);
void swap(int *a,int *b);
void heapify(int size,int i);
void heapSort();
int getMax();
void countingSort(int pos);
void radixSort();
int minDistance(int *SPT_set,int *shortestDistance);
void displayPath(int *parent,int v);
void Dijkstra(int sourceVertex);
void welcomePage_1();
void welcomePage_2();
void welcomePage_3();
void welcomePage_4();
void welcome();
void customer();
void physicalCustomer();
void onlineCustomer();
void onlineDeliveryTeam();
void cookingTeam();
void manager();
char identity();
void verefication(char choice);

int main()
{
	welcome();
	verification(identity());
	
	return 0;
}

// Function to create a node
struct node *createNode(int key)
{
	struct node *newNode=(struct node *)malloc(sizeof(struct node));
	
	newNode->key=key;
	newNode->next=NULL;
	
	return newNode;
}

// Function to set the position of the cursor
void gotoxy(int x,int y)
{
	COORD c;
	
	c.X=x;
	c.Y=y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);	
}

/* Function to perform swaping
   Swaping has been done in heap sort */
void swap(int *a,int *b)
{
   int temp;
   
   temp=*a;
   *a=*b;
   *b=temp; 
}

// Function to perfrom heapify
void heapify(int size,int i)
{
   int smallest,left,right,temp;
   
   smallest=i;
   left=2*i+1;
   right=2*i+2;
   
   if(left<size && arr_quantity[left]<arr_quantity[smallest])
      smallest=left;
    
   if(right<size && arr_quantity[right]<arr_quantity[smallest])
      smallest=right;  
   
   if(smallest!=i)
   {
      swap(&arr_quantity[i],&arr_quantity[smallest]);
      swap(&arr_code[i],&arr_code[smallest]);
   
      heapify(size,smallest);
   }
}

// Function to perform heap sort in descending order
void heapSort()
{
   int temp,i,size=30;
   
   // Build min heap
   for(i=size/2-1;i>=0;i--)
      heapify(size,i);
      
   // Perform heap sort
   for(i=size-1;i>=0;i--)
   {
      swap(&arr_quantity[0],&arr_quantity[i]);
      swap(&arr_code[0],&arr_code[i]);
      
      heapify(i,0);
   } 
}

/* Function to get the maximum element in a given array
   This has been used in radix sort */
int getMax()
{
    int max=arr_profit[0],i,n=30;
    
    for(i=1;i<n;i++)
    {
    	if(arr_profit[i]>max)
    	   max=arr_profit[i];
	}
    
	return max;    
}

/* Function to perform counting sort in ascending order
   This sorting technique has been used in radix sort */
void countingSort(int pos)
{
	int k=9,n=30,i,x,y;
	int count[k+1];
	
	for(i=0;i<=k;i++)
       count[i]=0;
	
	for(i=0;i<n;i++)
	{
		x=(arr_profit[i]/pos)%10;
		count[x]++;
	}
	
	for(i=1;i<=k;i++)
		count[i]=count[i]+count[i-1];
	   
	int aux1[n],aux2[n];
	
	for(i=n-1;i>=0;i--)
	{
		x=(arr_profit[i]/pos)%10;
		count[x]--;
		y=count[x];
		aux1[y]=arr_profit[i];
		aux2[y]=arr_code[i];	
	}
	
	for(i=0;i<n;i++)
	{
	    arr_profit[i]=aux1[i];
		arr_code[i]=aux2[i];
	}
}

// Function to perform radix sort in ascending order
void radixSort()
{
	int max,pos;
	
	max=getMax();
	
	for(pos=1;(max/pos)>0;pos*=10)
		countingSort(pos);
}

// Function to find out which vertex ( out of all the vertices that are not included in the Shortest Path Tree ) is at the minimum distance from a given source vertex
int minDistance(int *SPT_set,int *shortestDistance)
{
	int min_distance=INT_MAX,minVertex,i;
	
	for(i=0;i<V;i++)
	{
		if(SPT_set[i]==0 && shortestDistance[i]<=min_distance)
		{
		   min_distance=shortestDistance[i];
		   minVertex=i;
	    }
	}
	
	return minVertex;
}

// Function to display the shortest path obtained using Dijkstra's algorithm
void displayPath(int *parent,int v)
{
	// Base case
	if(parent[v]==-1)
	   return;
	   
	displayPath(parent,parent[v]);
	printf("--->%s",places[v]);
}

// Dijkstra's single source shortest path algorithm
void Dijkstra(int sourceVertex)
{
	int E=30,i,j,x,y,u,v;
	int distanceMatrix[V][V],SPT_set[V],shortestDistance[V],parent[V];
	int edgeArray[][2]={{0,3},{0,5},{0,7},{0,13},{0,16},{1,2},{1,6},{1,8},{1,9},{1,12},{1,14},{2,7},{2,12},{2,15},{3,5},{3,7},{3,8},{4,5},{4,11},{5,6},{6,7},{6,8},{6,15},{7,13},{7,15},{9,12},{10,12},{10,13},{12,14},{13,16}};
	int distance[]={45,35,31,17,30,75,24,22,20,12,19,29,8,17,40,100,70,23,5,76,50,30,7,28,6,10,3,150,15,25};
	bool flag=true;
	
	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
		{
			distanceMatrix[i][j]=0;
		}
	}
	
	for(i=0;i<E;i++)
	{
		x=edgeArray[i][0];
		y=edgeArray[i][1];
		
		distanceMatrix[x][y]=distance[i];
		distanceMatrix[y][x]=distance[i];
	}
	
	for(i=0;i<V;i++)
	{
		SPT_set[i]=0;
		shortestDistance[i]=INT_MAX;
		parent[i]=-1;
	}
	
	shortestDistance[sourceVertex]=0;
	
	while(flag)
	{
	   u = minDistance(SPT_set,shortestDistance);
	   SPT_set[u]=1;
	
	   for(v=0;v<V;v++)
	   {
		   if(distanceMatrix[u][v]!=0 && SPT_set[v]==0)
		   {
			   if(shortestDistance[u] + distanceMatrix[u][v] < shortestDistance[v])
			   {
		          shortestDistance[v] = shortestDistance[u] + distanceMatrix[u][v];
		          parent[v]=u;
		       }
		   }
	   }
	   
	   if(SPT_set[0]==1 && SPT_set[1]==1 && SPT_set[2]==1 && SPT_set[3]==1 && SPT_set[4]==1 && SPT_set[5]==1 && SPT_set[6]==1 && SPT_set[7]==1 && SPT_set[8]==1)
	      flag=false;
	}
	
	printf("\n\n\tPLACE\t\t\tSHORTEST DISTANCE FROM %s\t\t\tROUTE TO BE FOLLOWED",places[sourceVertex]);
	printf("\n\t      \t\t\t         (in kilometres)");
	
	for(i=0;i<=8;i++)
	{
		printf("\n\n\t%s\r\t\t\t\t\t\t%d\t\t\t%s",places[i],shortestDistance[i],places[sourceVertex]);
		displayPath(parent,i);
	}
	
	sleep(120);
}

void welcomePage_1()
{
	
	system("COLOR E4");
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t   WELCOME !!!!");
	printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      SNOW VIEW RESTAURANT");
	printf("\n\n\t\t\t\t\t\t\t\t\t    The pride of North Bengal");
	printf("\n\n\n\t\t\t\t\t\t\t\t   Enjoy your food in the lap of Kanchenjungha");
	
	sleep(5);
	system("cls");
}

void welcomePage_2()
{
	system("COLOR F0");
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tOUR BRANCHES");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t      1. DARJEELING");
	printf("\n\n\t\t\t\t\t\t\t\t\t      2. KALINGPONG");
	printf("\n\n\t\t\t\t\t\t\t\t\t      3. MIRIK");
	printf("\n\n\t\t\t\t\t\t\t\t\t      4. LEPCHAJAGOT");
	printf("\n\n\t\t\t\t\t\t\t\t\t      5.LOWER CHATAKPUR");
	printf("\n\n\t\t\t\t\t\t\t\t\t      6. SONADA");
	printf("\n\n\t\t\t\t\t\t\t\t\t      7. TINCHULEY");
	printf("\n\n\t\t\t\t\t\t\t\t\t      8. SITTONG");
	printf("\n\n\t\t\t\t\t\t\t\t\t      9. LAVA LOLEGAON");	
	
	sleep(5);
	system("cls");
}

void welcomePage_3()
{
	
	system("COLOR AF");
	
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t      OUR SERVICES");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t\t      1. BREAKFAST");
	printf("\n\n\t\t\t\t\t\t\t\t\t      2. LUNCH");
	printf("\n\n\t\t\t\t\t\t\t\t\t      2. SNACKS"); 
	printf("\n\n\t\t\t\t\t\t\t\t\t      2. DINNER");
	printf("\n\n\n\n\t\t\t\t\t\t\t\t   FREE DELIVERY TO NEARBY HOTELS");
	printf("\n\n\t\t\t\t\t\t\t    PREMIUM QUALITY DARJEELING TEA AND COFFEE AVAILABLE");
	printf("\n\n\t\t\t\t\t\t\t    WE ACCEPT ONLINE ORDERS THROUGH OUR OFFICIAL WEBSITE");
	printf("\n\n\t\t\t\t\t\tGET 500 g PREMIUM QUALITY DARJEELING TEA ONLY AT RS 199 ON ONLINE ORDERS ABOVE RS 5999");
    printf("\n\n\n\n\t\t\t\t\t     OUR RESTAURANT IS CENTRALLY AIR CONDITIONED WITH FREE ACCESS TO TIBETAN MUSIC WHILE EATING");
	
	sleep(5);
	system("cls");	
}

void welcomePage_4()
{
	system("COLOR DF");
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t   CONTACT US");
	printf("\n\n\n\n\t\t\t\t\t\t\t\tEmail ID: snowviewnbengal@gmail.com");
	printf("\n\n\t\t\t\t\t\t\tPHONE NUMBERS: +91 9874921262  9836820960 7980961137 6289389115");
	printf("\n\n\t\t\t\t\t\t\tVisit our OFFICIAL WEBSITE: https://www.snowviewservices.com ");
	
	sleep(5);
	system("cls");
}

// Function to display all the 4 welcome pages one by one
void welcome()
{
	struct node *one=NULL,*two=NULL,*three=NULL,*four=NULL,*head=NULL,*tail=NULL,*ptr=NULL;
	
	one=createNode(1);
	two=createNode(2);
	three=createNode(3);
	four=createNode(4);
	
	one->next=two;
	two->next=three;
	three->next=four;
	
	head=one;
	tail=four;
	
	tail->next=head;
	
	ptr=head;
	
	while(!kbhit())
	{
		switch(ptr->key)
		{
			case 1: welcomePage_1();
			        break;
			        
			case 2: welcomePage_2();
			        break;
			        
			case 3: welcomePage_3();
			        break;
			        
			case 4: welcomePage_4();
			        break;
		}
		
		ptr=ptr->next;
		
	}		
}

void customer()
{
	char choice;
	bool flag=true;
	
	system("cls");
	system("COLOR F0");
	
	printf("\n\n\n\tHELLO CUSTOMER, WE ARE GLAD THAT YOU HAVE SHOWN INTEREST IN US");
	printf("\n\n\tPRESS 1 IF YOU WISH TO ORDER FOOD ONLINE");
	printf("\n\tPRESS 2 IF YOU WISH TO PHYSICALLY VISIT OUR RESTAURANT");
	printf("\n\t[ WE RECOMMEND YOU TO VISIT OUR RESTAURANT PHYSICALLY WITH YOUR FAMILY AND FRIENDS ]");
	
	while(flag)
	{
		printf("\n\n\tENTER YOUR CHOICE: ");
		choice=getch();
		printf("%c",choice);
		
		switch(choice)
		{
			case '1': sleep(2);
			          onlineCustomer();
			          flag=false;
			          break;
			          
			case '2': sleep(2);
			          physicalCustomer();
			          flag=false;
			          break;
			          
			default : printf("\n\t\a\a\aSORRY!!! YOUR CHOICE IS INVALID");
			          printf("\n\tPLEASE TRY AGAIN"); 
		}
	}	
}

void physicalCustomer()
{
	int choice,*shortestDistance,i;
	
	system("cls");
	system("COLOR E0");
	
	printf("\n\n\tWE ARE GLAD UPON HEARING THAT YOU WANT TO PHYSICALLY VISIT OUR RESTAURANT");
	printf("\n\tWE HAVE A STRICT \"FIRST COME FIRST SERVE\" POLICY. THERE IS NO PROVISION FOR BOOKING YOUR SEAT ONLINE");
	
	printf("\n\n\tWE HAVE OUR BRANCHES OPERATING AT:");
	printf("\n\n\t1.DARJEELING");
	printf("\n\n\t2.KALINGPONG");
	printf("\n\n\t3.MIRIK");
	printf("\n\n\t4.LEPCHAJAGOT");
	printf("\n\n\t5.LOWER CHATAKPUR");
	printf("\n\n\t6.SONADA");
	printf("\n\n\t7.TINCHULEY");
	printf("\n\n\t8.SITTONG");
	printf("\n\n\t9.LAVA LOLEGAON");
	
	printf("\n\n\tIF YOU ARE AT ANY OF THESE PLACES, YOU CAN DIRECTLY VISIT OUR RESTAURANT");
	
	printf("\n\n\n\n\tALSO, IF YOU ARE AT ANY OF THE PLACES LISTED BELOW, WE CAN SUGGEST YOU THE SHORTEST ROUTE TO REACH ALL THE BRANCHES OF OUR RESTAURANT");
	printf("\n\n\t10.TRIVENI");
	printf("\n\n\t11.SILIGURI");
	printf("\n\n\t12.UPPER CHATAKPUR");
	printf("\n\n\t13.NEW JALPAIGURI");
	printf("\n\n\t14.GANGTOK");
	printf("\n\n\t15.KURSEONG");
	printf("\n\n\t16.SIMANA VIEW POINT");
	printf("\n\n\t17.PELING");
	
	printf("\n\n\tENTER AN APPROPRIATE CHOICE");
	printf("\n\t[ FOR EXAMPLE, IF YOU ARE AT TRIVENI, PRESS 10, IF YOU ARE AT GANGTOK, PRESS 14 AND SO ON..... ]   ");
	scanf("%d",&choice);
	
	choice--;
	
	Dijkstra(choice);
}

void onlineCustomer()
{
	FILE *fptr;
	char name[30],mobileNumber1[11],mobileNumber2[11],hotelName[30],roomNumber[10],location[20],landmark[20],order[40],code[3],quantity[2],entry;
	int i,totalCost,grandTotal=0;
	
	system("cls");
	system("COLOR F0");
	   
	printf("\n\n\tENTER YOUR NAME: ");
	scanf(" %[^\n]s",name);
	printf("\n\tENTER YOUR 10-DIGIT VALID MOBILE NUMBER SO THAT OUR DELIVERY AGENT CAN CONTACT YOU AT THE TIME OF DELIVERY: +91");
	scanf(" %[^\n]s",mobileNumber1);
	printf("\n\tENTER AN ALTERNATE VALID MOBILE NUMBER. THIS IS MANDATORY: +91");
	scanf(" %[^\n]s",mobileNumber2);
	printf("\n\n\tNOW, WE WILL COLLECT YOUR DELIVERY ADDRESS. THIS IS AN IMPORTANT INFORMATION. PLEASE GIVE THE ENTRIES CAREFULLY");
	printf("\n\n\tARE YOU A TOURIST STAYING AT A HOTEL/HOME STAY/GUEST HOUSE OR A LOCAL RESIDENT ?");
	printf("\n\tPRESS T IF YOU ARE A TOURIST. PRESS L OTHERWISE: ");
	scanf(" %c",&entry);
	
	if(entry=='T')
	{
		printf("\n\n\tHELLO TOURIST !!! A LOT OF THANKS FOR VISISTING NORTH BENGAL..... WE HOPE THAT YOU HAVE ENJOYED A LOT. NOW IT'S TIME TO QUENCH YOUR HUNGER");
		printf("\n\n\tENTER THE NAME OF THE HOTEL/HOME STAY/GUEST HOUSE: ");
		scanf(" %[^\n]s",hotelName);
		printf("\n\tENTER THE ROOM NUMBER: ");
		scanf(" %[^\n]s",roomNumber);	
	}
	
	printf("\n\tENTER YOUR LOCATION: ");
	scanf(" %[^\n]s",location);
	printf("\n\tMENTION THE NAME OF ANY NEARBY LANDMARK(THIS IS MANDATORY). THIS WILL HELP OUR DELIVERY AGENT TO REACH TO YOU WITH EASE: ");
	scanf(" %[^\n]s",landmark);
	
	printf("\n\n\tTHANK YOU !!! YOUR INFORMATION HAS BEEN COLLECTED SUCCESSFULLY");
	
	sleep(4);
	
	system("cls");
	system("COLOR E0");
	
	printf("\n\n\n\tPLEASE WAIT FOR SOME TIME WHILE THE MENU CHART IS BEING UPLOADED");
	
	for(i=0;i<8;i++)
	{
		sleep(1);
		printf(".");
	}
	
	system("cls");
	
	fptr=fopen("menu.txt","r");
	
	while(!feof(fptr))
	   putchar(fgetc(fptr));
	   
	fclose(fptr);
	
	printf("\n\n\tENTER THE UNIQUE FOOD CODE OF THE FOOD ITEMS THAT YOU WANT TO ORDER. MENTION THE QUANTITY WITHIN BRACKETS. THE QUANTITY OF EACH ITEM SHOULD NOT EXCEED 9.\n\tTHERE SHOULD BE A SPACE BETWEEN TWO SUCCESSIVE ENTRIES");
	printf("\n\t[ SAMPLE INPUT: SV00(3) SV08(1) SV15(2) ]");
	printf("\n\n\tGIVE THE INPUT NOW. PLEASE VERIFY THE FOOD CODES PROPERLY BEFORE GIVING THE INPUT: ");
	scanf(" %[^\n]s",order);
	
	fptr=fopen("customer_details.txt","a");
	
	if(entry=='T')
	   fprintf(fptr,"\n\n%s,%s,%s,%s,%s,%s,%s,%s",name,mobileNumber1,mobileNumber2,hotelName,roomNumber,location,landmark,order);
    else
	   fprintf(fptr,"\n\n%s,%s,%s,N/A,N/A,%s,%s,%s",name,mobileNumber1,mobileNumber2,location,landmark,order);
	
	fclose(fptr);
	
	fptr=fopen("order_details.txt","a");
	fprintf(fptr,"\n%s",order);
	fclose(fptr);
	
	system("cls");
	system("COLOR DF");
	
	printf("\n\n\n\tYOUR ORDER HAS BEEN SUCCESSFULLY PLACED");
	printf("\n\n\tPLEASE WAIT FOR SOME TIME WHILE THE BILL IS BEING GENERATED");
	
	for(i=0;i<8;i++)
	{
		sleep(1);
		printf(".");
	}
	
	system("cls");
	
	printf("\n\n\n\tNAME: %s",name);
	printf("\n\tCONTACT NUMBERS: %s  %s",mobileNumber1,mobileNumber2);
	printf("\n\tDELIVERY ADDRESS: %s",location);
	printf("\n\tLANDMARK: %s",landmark);
	
	if(entry=='T')
	{
	    printf("\n\n\tTOURIST: %s",location);
		printf("\n\tNAME OF THE HOTEL/HOME STAY/GUEST HOUSE: %s",hotelName);
		printf("\n\tROOM NUMBER: %s",roomNumber);	
	}
	
	else
	   printf("\n\n\tLOCAL RESIDENT");
	
	printf("\n\n\n\t                                                 ORDER DETAILS");  
	printf("\n\t______________________________________________________________________________________________________________________");
	printf("\n\tFOOD ITEM\t\t\t\tQUANTITY ORDERED(NO. OF PLATES)\t\tCOST PER PLATE(RS)\tTOTAL COST(RS)");
	printf("\n\t______________________________________________________________________________________________________________________");	
	
	i=0;
	
	while(order[i]!='\0')
	{
		if(order[i]=='V')
		{
			i++;
			
			if(order[i]=='0')
			{
				i++;
				
				code[0]=order[i];
				code[1]='\0';
			}
			
			else
			{
				code[0]=order[i];
				
			    i++;
			    
			    code[1]=order[i];
			    code[2]='\0';
			}
			
			i+=2;
			
			quantity[0]=order[i];
			quantity[1]='\0';
			
			printf("\n\t%s\r\t\t\t\t\t\t\t   %d\t\t\t\t       %d",food[atoi(code)],atoi(quantity),costPerPlate[atoi(code)]);
			
			totalCost = atoi(quantity) * costPerPlate[atoi(code)];
			grandTotal+=totalCost;
				
			printf("\t\t    %d",totalCost);	   
		}
		
		i++;
	}
	
	printf("\n\t______________________________________________________________________________________________________________________");	
	printf("\n\t\t\t\t\t\t\t\t\t\t\t\t    GRAND TOTAL: RS %d",grandTotal);
	
	sleep(8);
	
	int x=5,y=20;
	
	while(true)
	{
	   gotoxy(x,y);
	   
	   printf("THANK YOU!!! VISIT AGAIN !!!");
	   
	   usleep(500000);
	   system("cls");
	   x++;
    }
}

void onlineDeliveryTeam()
{
	system("cls");
	system("COLOR E0");
	
	FILE *fptr;
	fptr=fopen("customer_details.txt","r");
	
	while(!feof(fptr))
	   putchar(fgetc(fptr));
}

void cookingTeam()
{
	system("cls");
	system("COLOR A0");
	
	char code[3],quantity[2];
	int i;
	
	FILE *fptr;
	fptr=fopen("order_details.txt","r");
	
	while(!feof(fptr))
	{
	   	if(fgetc(fptr)=='V')
		{
			if(fgetc(fptr)=='0')
			{
				code[0]=fgetc(fptr);
				code[1]='\0';
			}
			
			else
			{
				fseek(fptr,-1,SEEK_CUR);
				
				code[0]=fgetc(fptr);
				code[1]=fgetc(fptr);
				code[2]='\0';
			}
			
			fseek(fptr,1,SEEK_CUR);
			
			quantity[0]=fgetc(fptr);
			quantity[1]='\0';
			
			arr_quantity[atoi(code)] += atoi(quantity);
		} 
	}
	
	printf("\n\n\n\t____________________________________________________________________");
	printf("\n\tFOOD ITEM\t\t\t\tQUANTITY ORDERED(NO. OF PLATES)");
	printf("\n\t____________________________________________________________________");
	
	for(i=0;i<30;i++)
	{
	   if(arr_quantity[i] != 0)	
	      printf("\n\n\t%s\r\t\t\t\t\t\t\t   %d",food[i],arr_quantity[i]);
	}
	
	printf("\n\t____________________________________________________________________");	   
	
	sleep(120);
}

void manager()
{
	FILE *fptr;
	fptr=fopen("order_details.txt","r");
	
	char code[3];
	char quantity[2];
	int i,totalProfit=0;
	
	for(i=0;i<30;i++)
	{
	   arr_quantity[i]=0;
	   arr_code[i]=i;
    }
	     
	while(!feof(fptr))
	{
		if(fgetc(fptr)=='V')
		{
			if(fgetc(fptr)=='0')
			{
				code[0]=fgetc(fptr);
				code[1]='\0';
			}
			
			else
			{
				fseek(fptr,-1,SEEK_CUR);
				
				code[0]=fgetc(fptr);
				code[1]=fgetc(fptr);
				code[2]='\0';
			}
			
			fseek(fptr,1,SEEK_CUR);
			
			quantity[0]=fgetc(fptr);
			quantity[1]='\0';
			
			arr_quantity[atoi(code)] += atoi(quantity);
		} 
	}
	
	for(i=0;i<30;i++)
	{
	    arr_profit[i]=arr_quantity[i]*profitPerPlate[i];
	    totalProfit+=arr_profit[i];
	}
	
	heapSort();
	
	system("cls");
	system("COLOR CF");
	
	printf("\n\n\n\tPLEASE WAIT FOR SOME TIME WHILE DATA MANIPULATION IS BEING DONE");
	
	for(i=0;i<8;i++)
	{
		sleep(1);
		printf(".");
	}
	
	system("cls");
	
	printf("\n\n\n\t____________________________________________________________________");
	printf("\n\tFOOD ITEM\t\t\t\tQUANTITY SOLD(NO. OF PLATES)");
	printf("\n\t____________________________________________________________________");
	
	for(i=0;i<30;i++)
	{
	   if(arr_quantity[i] != 0)	
	      printf("\n\n\t%s\r\t\t\t\t\t\t\t   %d",food[arr_code[i]],arr_quantity[i]);
    }
	
	printf("\n\t____________________________________________________________________");
	
	printf("\n\n\n\tMOST SOLD ITEM(S): %s    ",food[arr_code[0]]);
	
	i=1;
	
	while(arr_quantity[i] == arr_quantity[0])
	{
		printf("%s    ",food[arr_code[i]]);
		i++;
	}
		
	printf("\n\tQUANTITY SOLD : %d PLATES",arr_quantity[0]);
	
	for(i=0;i<30;i++)
		arr_code[i]=i;
		
	radixSort();
	
	printf("\n\n\n\n\t____________________________________________________________________");
	printf("\n\tFOOD ITEM\t\t\t\t   PROFIT EARNED(IN RS)");
	printf("\n\t____________________________________________________________________");
	
	for(i=29;i>=0;i--)
	{
	   if(arr_profit[i] != 0)	
	      printf("\n\n\t%s\r\t\t\t\t\t\t\t   %d",food[arr_code[i]],arr_profit[i]);
    }
    
    printf("\n\t____________________________________________________________________");
    
    printf("\n\n\n\tMOST PROFITABLE ITEM(S): %s    ",food[arr_code[29]]);
	
	i=28;
	
	while(arr_profit[i] == arr_profit[29])
	{
		printf("%s    ",food[arr_code[i]]);
		i--;
	}
		
	printf("\n\tPROFIT EARNED : RS %d",arr_profit[29]);
	printf("\n\n\tTOTAL PROFIT EARNED BY THE RESTAURANT FROM THE SELL OF ALL FOOD ITEMS: RS %d",totalProfit);	
}

char identity()
{
	char choice;
	bool flag=true;
	
    system("cls");
    system("COLOR F0");
    
    printf("\n\n\n\n\tLET US KNOW TO WHICH OF THE FOLLOWING CATEGORIES YOU BELONG TO.....");
    printf("\n\n\t1. CUSTOMER");
    printf("\n\n\t2. MEMBER OF ONLINE DELIVERY TEAM");
    printf("\n\n\t3. MEMBER OF COOKING TEAM");
    printf("\n\n\t4. MANAGER");
    
    printf("\n\n\tENTER AN APPROPRIATE CATEGORY:");
    
    while(flag)
    {
       choice=getch();
       printf("%c",choice);
	   
       if(choice=='1' || choice=='2' || choice=='3' || choice=='4')
           flag=false; 
       
       else
       {
       	   printf("\a\a\n\tOOPS!!! YOUR ENTRY IS INCORRECT");
       	   printf("\n\n\tNEVER MIND!!! ENTER AGAIN CAUTIOUSLY: ");
       }	
    } 
	
	sleep(2);
	return choice;  
}

void verification(char choice)
{
	int i,generated_otp,entered_otp;
	bool flag=true;
	char code[7];
	char code_onlineDeliveryTeam[]="SVRODT";
	char code_cookingTeam[]="SVRCKT";
	char code_manager[]="SVRMNG";
	
	system("cls");
	system("COLOR 5F");
	
	switch(choice)
	{
		case '1': printf("\n\n\n\n\tHELLO CUSTOMER, THANK YOU FOR CHOOSING SNOW VIEW SERVICES");
			      break;
			        
		case '2': printf("\n\n\n\tWELCOME MEMBER");
		          printf("\n\n\tENTER THE 6-DIGIT VERIFICATION CODE: ");
			         
			      while(flag)
			      {
			            for(i=0;i<6;i++)
			            {
			               code[i]=getch();
			               printf("*");
			            }
			         
			            code[6]='\0';
			         
			            if( strcmp(code,code_onlineDeliveryTeam) ==0 )
			            {
			         	   printf("\n\tVERIFICATION SUCCESSFUL !!!");
			         	   flag=false;
					    }
					    
					    else
					    {
					    	printf("\a\a\n\tINCORRECT CODE");
					    	printf("\n\n\tRE-ENTER CODE: ");
						}
				  }
				  
			      break;
			        
		case '3': printf("\n\n\n\tWELCOME MEMBER");
		          printf("\n\n\tENTER THE 6-DIGIT VERIFICATION CODE: ");
			         
			      while(flag)
			      {
			            for(i=0;i<6;i++)
			            {
			               code[i]=getch();
			               printf("*");
			            }
			         
			            code[6]='\0';
			         
			            if( strcmp(code,code_cookingTeam) ==0 )
			            {
			         	   printf("\n\tVERIFICATION SUCCESSFUL !!!");
			         	   flag=false;
					    }
					    
					    else
					    {
					    	printf("\a\a\n\tINCORRECT CODE");
					    	printf("\n\n\tRE-ENTER CODE: ");
						}
				  }
				  
			      break;
			        
		case '4': printf("\n\n\n\tWELCOME SIR");
		          printf("\n\n\tENTER THE 6-DIGIT VERIFICATION CODE: ");
			         
			      while(flag)
			      {
			            for(i=0;i<6;i++)
			            {
			               code[i]=getch();
			               printf("*");
			            }
			         
			            code[6]='\0';
			         
			            if( strcmp(code,code_manager) ==0 )
			            {
			         	   printf("\n\tVERIFICATION SUCCESSFUL !!!");
			         	   flag=false;
					    }
					    
					    else
					    {
					    	printf("\a\a\n\tINCORRECT CODE");
					    	printf("\n\n\tRE-ENTER CODE: ");
						}
				  }
				  
	} 
	
	sleep(3);
	
	printf("\n\n\tA 4-DIGIT OTP WILL BE GENERATED");
	printf("\n\tYOU WILL BE ASKED TO ENTER THE OTP FOR VERIFICATION");
	
	sleep(3);
	
	printf("\n\n\tPLEASE WAIT WHILE THE OTP IS BEING GENERATED");
	
	for(i=0;i<8;i++)
	{
		sleep(1);
		printf(".");
	}
	
	srand(time(0));
	
	flag=true;
	
	while(flag)
	{
	   generated_otp=rand()%9000+1000;
	
	   printf("\n\n\tYOUR 4-DIGIT OTP IS %d",generated_otp);
	   
	   sleep(2);
	   
	   printf("\n\tENTER THE OTP: ");
	   scanf("%d",&entered_otp);
	
	   if(generated_otp == entered_otp)
	   {
		  printf("\n\tCORRECT ENTRY");
		  flag=false;
	   }
	   
	   else
	   {
	   	  printf("\a\a\n\tWRONG ENTRY");
	   	  printf("\n\tPLEASE WAIT FOR SOME TIME BEFORE ANOTHER ATTEMPT");
	   	  sleep(5);
	   }
    }
    
    switch(choice)
    {
    	case '1': customer();
    	          break;
    	          
    	case '2': onlineDeliveryTeam();
    	          break;
    	          
    	case '3': cookingTeam();
    	          break;
    	          
    	case '4': manager(); 
    	          	
	}  
}


