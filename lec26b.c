#include<stdio.h>
#include<stdlib.h>
// #include<process.h>

main(){
    struct students{
        char name[30];
        int age;
       
    }stud[2];

    FILE *fp; 
    int i, j=0, n;
    char str[15];
    printf("\nEnter the filename ");

    scanf("%s",str);
    fp=fopen(str,"w+b");
    if(fp==NULL){
        printf("\nFile not found");
        exit(0);
    }
    else{
        printf("\nEnter the number of students ");
        scanf("%d",&n);
        for(i=0;i<n;i++){
            printf("\nEnter the name and age of student %d ",i+1);
            scanf("%s %d",stud[i].name,&stud[i].age);
        }
        while (j<n)
        {
            fwrite(&stud[j],sizeof(stud[j]),1,fp);
            j++;
        }
        rewind(fp);
        while(j < n){
            fread(&stud[j],sizeof(stud[j]),1,fp);
            j++;
        }

        for(i=0;i<n;i++){
            printf("\nName: %s",stud[i].name);
            printf("\nAge: %d",stud[i].age);
        }
        fclose(fp);
    }

    return 0;
    
}

