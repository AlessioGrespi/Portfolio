#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

float maintenance, base, salary, growth, loan, payment, ipm, paid, taxable, ppm, interest, percent;
float matrix[6][360]; //declare array for writing data horizontally
int ygraduation, years, yentry;
int mgraduation = 07;
char placement;

FILE *pfile; //declare file pointer

//declares functions
void userInput(void);
void baseCost(void);
void printData(void);
void paymentCalculation(void);
void printCSV(void);

int main()
{
    //calls functions
    userInput();
    baseCost();
    printData();
    paymentCalculation();
    printCSV();

    fclose(pfile); //closes file operations
    scanf("%*s");
}

void userInput() // gathers data for calculation
{
    printf("Length of course: ");
    scanf(" %d", &years);
    printf("Maintenance: ");
    scanf(" %f", &maintenance);
    printf("placement Y/N? ");
    scanf(" %c", &placement);
    printf("Salary: ");
    scanf(" %f", &salary);
    printf("Salary growth in percent per year: ");
    scanf(" %f", &growth);
    printf("Year of entry: (yyyy): ");
    scanf(" %d", &yentry);

    ygraduation = yentry + years;

    if ((placement == 'Y') || (placement == 'y')) //placement year
    {
        ygraduation = ygraduation + 1;
    }

    growth = growth / 100; //converts percent to a multipliable factor
}

void printData() //prints Appendix data to a .txt
{
    pfile = fopen("loancalc.txt", "w"); //creates file
    fclose(pfile);
    pfile = fopen("loancalc.txt", "a"); //edits file

    //prints data to .txt
    fprintf(pfile, "Length of degree: %d ", years);
    if ((placement == 'Y') || (placement == 'y')) /*placement year*/
    {
        fprintf(pfile, "+ 1");
    }
    fprintf(pfile, "\n");
    fprintf(pfile, "Loan: %f \n", loan);
    fprintf(pfile, "Maintenance: %f \n", maintenance);
    fprintf(pfile, "Placement: %c \n", placement);
    fprintf(pfile, "Salary: %f \n", salary);
    fprintf(pfile, "Date of Entry: 09/%d \n", yentry);
    fprintf(pfile, "Date of Graduation: 0%d/%d \n", mgraduation, ygraduation);
    fprintf(pfile, "End of loan payment: 04/%d \n", ygraduation + 31);

    fclose(pfile);

    //prints relevant data to screen
    printf("\n  ------------------------------------  \n \n");
    printf("Length of degree: %d ", years);
    if ((placement == 'Y') || (placement == 'y')) /*placement year*/
    {
        printf("+ 1");
    }
    printf("\n");
    printf("Loan: %f \n", loan);
    printf("Maintenance: %f \n", maintenance);
    printf("Placement: %c \n", placement);
    printf("Salary: %f \n", salary);
    printf("Date of Entry: 09/%d \n", yentry);
    printf("Date of Graduation: 0%d/%d \n", mgraduation, ygraduation);
    printf("End of loan payment: 04/%d \n", ygraduation + 31);
}

void baseCost() //calculates size of loan before end of uni
{
    base = (9250 + maintenance);
    loan = (base)*1.033; //year 1
    loan = (loan + base)*1.033; //year 2

    if ((placement == 'Y') || (placement == 'y')) //placement year
    {
        loan = (loan + ((9250 + maintenance)*0.2))*1.033;
    }

    loan = (loan + base)*1.033; //year3

    if (years == 4) //year 4
    {
        loan = (loan + base)*1.033;
    }

    int p=1; //interest between end of degree and April following year (6 months)
    for(p=0;p<=6;p++) // = loan*1.033^6
    {
        loan = loan+loan*(0.033/6);
    }
}

void paymentCalculation() //Calculates data to put into array
{
    paid = 0;
    int month = 0;

    while (month <= 359) //one month per loop
    {
        month++; /* increment the month counter*/

        if (salary > 25000) //Finding Loan interest, Monthly Repayment & Salary above threshold
        {
            taxable = salary - 25000; //Salary above threshold
            ppm = (taxable * 0.09) / 12; //Monthly Repayment

            if (salary > 45000) //Interest rate
            {
                interest = 6.3;
            }
            else
            {
                interest = ((taxable / 20000) * 3) + 3.3;
            }
        }
        else
        {
            interest = 3;
        }

        percent = interest / 100; //convert from percentage to multipliable number

        ipm = loan * percent; //Monthly Interest
        loan = loan + (loan*percent); //Balance
        paid = ppm + paid;

        /* Subtract the monthly payment */
        loan = loan - ppm;

        //writing data to an Array so as to print horizontally
        matrix[0][month-1] = salary;
        matrix[1][month-1] = taxable;
        matrix[2][month-1] = interest;
        matrix[3][month-1] = ipm;
        matrix[4][month-1] = ppm;
        matrix[5][month-1] = loan;

        salary = salary + ((salary*growth) / 12);
    }
}

void printCSV() //Prints from Array to CSV
{
    int y, x, mm;
    ygraduation = ygraduation + 1;
    mm=4;

    pfile = fopen("loancalc.csv", "w");
    fclose(pfile);
    pfile = fopen("loancalc.csv", "a");

    for(x=0;x<31;x++) //Prints date to CSV
    {
        while(mm<=12)
        {
            int n;
            int count = 0;
            n = mm;

            while(n != 0)
            {
                n /= 10;
                ++count;
            }


            if(count==1) //adds on a 0 when reguired so as to fullfil mm/yyyy format
            {
                fprintf(pfile, "0");
            }

            fprintf(pfile, "%d/%d, ", mm, ygraduation + x); //prints month and year to CSV
            mm++;
            if(x == 30 && mm == 4)
            {
                mm=13;
                x=31;
            }
        }
        years++;
        mm=1;
    }

    fprintf(pfile,"\n");

    y=0;
    while(y<=5)
    {
        for(x=0;x<360;x++)
        {
            fprintf(pfile, "%f, ", matrix[y][x]); //Prints remaining data to CSV
        }
        fprintf(pfile,"\n");
        y++;
    }
    fclose(pfile);
}
