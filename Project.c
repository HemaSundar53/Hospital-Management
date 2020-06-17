#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int id_exist(char*);
int quit();
void create_record(char*);
void display_record(char*);
void add_record(char*);
int file_lines(char*);
void update_details(char*);
void appoint();


struct Patient_details{
    char name[20];
    int age;
    char parent_name[20];
    char description[500];
    int date;
    int month;
    int year;
    char address[100];
};


int main(){

    // PATIENT ID
    char p_id[20];
    printf("Enter the patient ID: ");
    scanf("%s",p_id);
    strcat(p_id,".txt");


    //CHECK FOR OLD OR NEW PATIENT
    if(id_exist(p_id)){
        goto old_patient;
    }
    else{
        goto new_patient;
    }


    //OLD PATIENT
    old_patient:
        while(1){
            printf("\n\n\t1.Update previously entered record\n");
            printf("\t2.Get an Appointment\n");
            printf("\t3.Enter details of a new visit\n");
            printf("\t4.View your details\n");
            printf("\t5.QUIT\n");
            printf("press the number corresponding to the action to proceed: ");
            int choose;
            scanf("%d",&choose);
            switch(choose)
            {
            case 1:
                //UPDATE RECORDS
                update_details(p_id);
                break;
            case 2:
                //GET AN APPOINTMENT
                appoint();
                break;
            case 3:
                //ENTER DETAILS OF NEW VISIT
                add_record(p_id);
                break;
            case 4:
                //DISPLAY DETAILS
                display_record(p_id);
                printf("\n");
                break;
            case 5:
                //QUIT
                if(quit()==0)
                    goto end;
                break;
            default:
                printf("\nInvalid Choice...\n");
            }
        }


    // NEW PATIENT
    new_patient:
        create_record(p_id);
        //QUIT
        here:
        if(quit()==0)
            goto end;
        printf("Do you want to Update the Record(Yes/No): ");
        char c_[10];
        fflush(stdin);
        gets(c_);
        if(strcmp(c_,"YES")==0||strcmp(c_,"Yes")==0||strcmp(c_,"yes")==0)
            update_details(p_id);

        goto here;


    printf("\n\tTHIS SHOULD NOT BE PRINTED.\n");

    end:
    return 0;

}


// CHECK IF ID EXISTS
int id_exist(char* file_name){
    FILE *f;
    if(f = fopen(file_name,"r")){
        fclose(f);
        return 1;
    }
    return 0;
}


// QUIT THE PROGRAM
int quit(){
    printf("Do you want to Quit(Yes/No): ");
    char in[10];
    fflush(stdin);
    gets(in);
    if(strcmp(in,"YES")==0||strcmp(in,"Yes")==0||strcmp(in,"yes")==0)
        return 0;
    else
        return 1;
}


// NEW PATIENT DETAILS
void create_record(char* id){
    FILE *fp;
    fp = fopen(id,"w");
    struct Patient_details p_d;
    printf("\n");

    if(fp == NULL){
        printf("ERROR!\n");
    }
    else{
        printf("Patient's name:");
        fflush(stdin);
        gets(p_d.name);
        fprintf(fp,"Name: %s\n",p_d.name);
        printf("Enter Patient's age:");
        scanf("%d",&p_d.age);
        fprintf(fp,"Age: %d\n",p_d.age);
        printf("Enter Patient's Father/Mother's name:");
        fflush(stdin);
        gets(p_d.parent_name);
        fprintf(fp,"Father/Mother's name: %s\n",p_d.parent_name);
        printf("Enter Patient's Address:");
        fflush(stdin);
        gets(p_d.address);
        fprintf(fp,"Address: %s\n\n",p_d.address);
        redo:
        printf("Visiting Date(dd-mm-yyyy):");
        scanf("%d-%d-%d",&p_d.date,&p_d.month,&p_d.year);
        if(p_d.date>31||p_d.date<1||p_d.month>12||p_d.month<1){
            printf("\nWrong value of date entered, Please enter again.\n");
            goto redo;
        }
        fprintf(fp,"Date of Visit: %d-%d-%d\n",p_d.date,p_d.month,p_d.year);
        printf("Enter Patient's disease description:");
        fflush(stdin);
        gets(p_d.description);
        fprintf(fp,"Disease description: %s\n\n",p_d.description);
    }

    fclose(fp);
}


//VIEW DETAILS
void display_record(char* id){
    FILE *fp;
    fp = fopen(id,"r");
    printf("\n|| PATIENT DETAILS ||\n\n");

    if(fp==NULL){
        printf("ERROR!\n");
    }
    else{
        char c = getc(fp);
        while(c!=EOF){
            printf("%c",c);
            c = getc(fp);
        }
    }

    fclose(fp);
}


//NEW VISIT
void add_record(char* id){
    FILE *fp;
    fp = fopen(id,"a");
    struct Patient_details p_d;

    if(fp==NULL){
        printf("ERROR!\n");
    }
    else{
        printf("Enter details of the New Visit,\n");
        printf("Visiting Date(dd-mm-yyyy):");
        scanf("%d-%d-%d",&p_d.date,&p_d.month,&p_d.year);
        fprintf(fp,"Date of Visit: %d-%d-%d\n",p_d.date,p_d.month,p_d.year);
        printf("Enter Patient's disease description:");
        fflush(stdin);
        gets(p_d.description);
        fprintf(fp,"Disease description: %s\n\n",p_d.description);
    }

    fclose(fp);
}


//Length of File
int file_lines(char* id){
    FILE *fp_;
    fp_ = fopen(id,"r");
    char line[256];
    int i=0;
    while (!feof(fp_)){
        i++;
        fgets(line, sizeof(line), fp_);
    }
    fclose(fp_);
    return i;
}

//UPDATE DETAILS
void update_details(char* id){
    FILE *fp;

    display_record(id);
    int i = file_lines(id);

    fp = fopen(id,"r+");
    struct Patient_details p_d;

    if(fp==NULL){
        printf("ERROR!\n");
    }
    else{
        printf("\nUpdate details thus checking from above displayed list of details:\n");
        printf("Enter Patient's name:");
        fflush(stdin);
        gets(p_d.name);
        fprintf(fp,"Name: %s\n",p_d.name);
        printf("Enter Patient's age:");
        scanf("%d",&p_d.age);
        fprintf(fp,"Age: %d\n",p_d.age);
        printf("Enter Patient's Father/Mother's name:");
        fflush(stdin);
        gets(p_d.parent_name);
        fprintf(fp,"Father/Mother's name: %s\n",p_d.parent_name);
        printf("Enter Patient's Address:");
        fflush(stdin);
        gets(p_d.address);
        fprintf(fp,"Address: %s\n\n",p_d.address);
        i-=5;
        while(i>0){
            printf("Visiting Date(dd-mm-yyyy):");
            scanf("%d-%d-%d",&p_d.date,&p_d.month,&p_d.year);
            fprintf(fp,"Date of Visit: %d-%d-%d\n",p_d.date,p_d.month,p_d.year);
            printf("Enter Patient's disease description:");
            fflush(stdin);
            gets(p_d.description);
            fprintf(fp,"Disease description: %s\n\n",p_d.description);
            i-=4;
        }
    }

    fclose(fp);
}


//DOCTOR APPOINTMENT
void appoint(){
    int d,m,y;
    d = (rand()%31)+1;
    m = (rand()%12)+1;
    y = (rand()%5)+2016;
    printf("\nYour Appointment is made on %d-%d-%d\n",d,m,y);
}

