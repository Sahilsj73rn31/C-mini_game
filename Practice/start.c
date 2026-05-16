#include<stdio.h>
#include<string.h>

/*
float max(float a, float b,float c){
    if (a>b && a>c){
        printf("A is greater than B and c");
    }
    else if(b>a && b>c){
        printf("B is greater than A and C");
    }
    else if(c>a && c>b){
        printf("C is greater than A and B");
    }
    else{
        printf("All are equal");
    }
    return 0;
}

int main()
{
    float a,b,c;
     printf("Enter the number A, B and C:\n");
     scanf("%f \n %f \n %f",&a,&b,&c);
     max(a,b,c);
     
     return 0;

} */

/*
struct Students
{
    char name[20];
    char degree[20];
    int age;
    int year;
};

int main()
{
    struct Students s1;
        s1.age=20;
        s1.year=2;
        strcpy(s1.name,"sahil");
        strcpy(s1.degree,"B.Tech");

        printf("Name: %s\n",s1.name);
        printf("Degree: %s\n",s1.degree);
        printf("Age: %d\n",s1.age);
        printf("Year: %d\n",s1.year);

        return 0;;
}
        */



//2-D array

/*
int main()
{
    int nums [3][2] = {{1,2},{3,4},{4,5}};

    printf("%d",nums[0][0]);


    return 0;
}*/


/*
int main()
{
    int nums [3][2] = {{1,2},{3,4},{4,5}};

    int i,j;
    for (i=0;i<3;i++){
        for(j=0;j<2;j++)
        {
            printf("%d",nums[i][j]);

        }
        printf("\n");
    }

    
    return 0;
}
    */



// var pointer and dereferencing
/*
    int main()
    {
        int age = 30;
        int *pAge = &age;
        double gpa = 3.5;
        double *pGpa = &gpa;
        char grade = 'A';
        char *pGrade = &grade;

        printf("age: %d\n gpa: %p\n grade: %p\n", *pAge, pGpa, pGrade);
    

        return 0;

    }
        */

    /*
    int main()
    {
     
        FILE * fpointer = fopen("C:\\Games\\sample.txt","w");

       fprintf(fpointer,"Sahil,developer.");
        

        FILE * fpointer = fopen("C:\\Games\\sample.txt","a");

        fprintf(fpointer,"\nShrawani, co-op.");



        char line[200];

        FILE * fpointer = fopen("C:\\Games\\sample.txt","r");

        fgets(line,200,fpointer);
        printf("%s",line);
        fgets(line,200,fpointer);
        printf("%s",line);


        fclose(fpointer);
        */

        /*
            r - read
            w - write
            a - append
       
    }
         */
