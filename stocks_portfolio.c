#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <math.h>

#define MAX_LEN 12

typedef struct STOCK
{
    int buy;
    int sell;
    int hold;
} STOCK;

typedef struct buyer
{
    char name[MAX_LEN];
    int quantity;
    char stock_name[MAX_LEN][MAX_LEN];
    STOCK trade;
} BUYER;
// colour functions
// =============colour functions start================
// red
void red()
{
    printf("\033[1;31m");
}
// function for yellow colour
void yellow()
{
    printf("\033[1;33m");
}
// function for reset
void reset()
{
    printf("\033[0m");
}
// green
void green()
{
    printf("\033[1;32m");
}
// cyan
void cyan()
{
    printf("\033[0;36m");
}
// blue
void blue()
{
    printf("\033[1;34m");
}
// purple
void purple()
{
    printf("\033[1;35m");
}
// white
void white()
{
    printf("\033[1;37m");
}
// ====================colour functions end====================
// end
// function prototypes

void MovingAvg(BUYER, float *);
float *GrabStockPrice(char *, float *);
void file(char *);
void users(BUYER, BUYER, BUYER, BUYER);
void markov(BUYER, float *);
float max(float arr[3][3], int n);
float maxNum(float, float, float);
int *mult(int array[3][3], int array2[3][3]);
void comparePrediction(BUYER, BUYER);


int main()
{
    BUYER user1, user2, user3, user4;

    fflush(stdin);

    strcpy(user1.name, "Yawar");
    // set user1 quantity to 3
    user1.quantity = 3;
    strcpy(user1.stock_name[0], "AAPL");
    strcpy(user1.stock_name[1], "GOOG");
    strcpy(user1.stock_name[2], "MSFT");

    //  create user 2
    strcpy(user2.name, "Iqbal");
    user2.quantity = 3;
    strcpy(user2.stock_name[0], "SBUX");
    strcpy(user2.stock_name[1], "ASUS");
    strcpy(user2.stock_name[2], "NFLX");

    // create user 3
    strcpy(user3.name, "Ms_Chandni_Sharma");
    user3.quantity = 4;
    strcpy(user3.stock_name[0], "INTC");
    strcpy(user3.stock_name[1], "SBUX");
    strcpy(user3.stock_name[2], "MSFT");
    strcpy(user3.stock_name[3], "AMZN");

    // create user 4
    strcpy(user4.name, "Yajas");

    user4.quantity = 5;
    strcpy(user4.stock_name[0], "AAPL");
    strcpy(user4.stock_name[1], "GOOG");
    strcpy(user4.stock_name[2], "MSFT");
    strcpy(user4.stock_name[3], "AMZN");
    strcpy(user4.stock_name[4], "FB2A");

    users(user1, user2, user3, user4);
    
    float stockHistory[12];
    markov(user1, stockHistory);
    markov(user2, stockHistory);
    markov(user3, stockHistory);
    markov(user4, stockHistory);

    MovingAvg(user1, stockHistory);
    MovingAvg(user2, stockHistory);
    MovingAvg(user3, stockHistory);
    MovingAvg(user4, stockHistory);

    return 0;
}

void file(char filename[])
{
    printf("\n\n\t\t%s's previous data\n\n", filename);
    strcat(filename, ".csv");
    FILE *fp = fopen(filename, "r");
    if (!fp)
        printf("Can't open file\n");

    else
    {
        char buffer[1024];

        int row = 0;
        int column = 0;

        while (fgets(buffer, 1024, fp))
        {
            column = 0;
            row++;

            if (row == 1)
                continue;

            // Splitting the data
            char *value = strtok(buffer, ", ");

            while (value)
            {
                // Column 1
                if (column == 0)
                {
                    printf("Date: ");
                }

                // Column 2
                if (column == 1)
                {
                    printf("\tOpen :");
                }

                // Column 3
                if (column == 2)
                {
                    printf("\tHigh :");
                }

                // Column 4
                if (column == 3)
                {
                    printf("\tLow :");
                }

                // Column 5
                if (column == 4)
                {
                    printf("\tClose :");
                }

                // Column 6
                if (column == 5)
                {
                    printf("\tAdj Close :");
                }

                // Column 7
                if (column == 6)
                {
                    printf("\tVolume :");
                }

                printf("%s", value);
                value = strtok(NULL, ", ");
                column++;
            }

            printf("\n");
        }

        fclose(fp);
    }
}

float *GrabStockPrice(char filename[], float stockHistory[])
{
    // float num[12];
    fflush(stdin);

    int i = 0;
    FILE *fp = fopen(filename, "r");
    // printf("test\n");
    if (!fp)
        printf("Can't open file\n");

    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%f", &stockHistory[i]);
            i++;
        }
    }
    fclose(fp);

    return stockHistory;
}

void users(BUYER user1, BUYER user2, BUYER user3, BUYER user4)
{
    red();
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2User Details\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("\nUser 1: %s\n", user1.name);
    reset();
    green();
    printf("Quantity of stocks bought : %d\n", user1.quantity);
    printf("Stock Name 1: %s\n", user1.stock_name[0]);
    printf("Stock Name 2: %s\n", user1.stock_name[1]);
    printf("Stock Name 3: %s\n", user1.stock_name[2]);
    printf("\n");
    red();
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("User 2: %s\n", user2.name);
    reset();
    green();
    printf("Quantity of stocks bought : %d\n", user2.quantity);
    printf("Stock Name 1: %s\n", user2.stock_name[0]);
    printf("Stock Name 2: %s\n", user2.stock_name[1]);
    printf("Stock Name 3: %s\n", user2.stock_name[2]);
    printf("\n");
    red();
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("User 3: %s\n", user3.name);
    green();
    printf("Quantity of stocks bought : %d\n", user3.quantity);
    printf("Stock Name 1: %s\n", user3.stock_name[0]);
    printf("Stock Name 2: %s\n", user3.stock_name[1]);
    printf("Stock Name 3: %s\n", user3.stock_name[2]);
    printf("Stock Name 4: %s\n", user3.stock_name[3]);
    printf("\n");
    red();
    printf("\n\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n");
    printf("User 4: %s\n", user4.name);
    green();
    printf("Quantity of stocks bought : %d\n", user4.quantity);
    printf("Stock Name 1: %s\n", user4.stock_name[0]);
    printf("Stock Name 2: %s\n", user4.stock_name[1]);
    printf("Stock Name 3: %s\n", user4.stock_name[2]);
    printf("Stock Name 4: %s\n", user4.stock_name[3]);
    printf("Stock Name 5: %s\n", user4.stock_name[4]);
    reset();
}

void markov(BUYER user, float stockHistory[])
{
    float buyProbab;
    float sellProbab;
    float holdProbab;
    float trMtrx[2][2];  // Transition Matrix not working
    float piMtrx1[0][3]; // Initial Probability Matrix
    float piMtrx2[0][3]; // Initial Probability Matrix
    float piMtrx3[0][3]; // Initial Probability Matrix
    float result1[0][3];
    float result2[0][3];
    float result3[0][3];
    float array[3]; // to store the probability of sell hold and buy
    int sell = 0, buy = 0, hold = 0;
    char stock_name[MAX_LEN];
    float stockhistory[MAX_LEN];
    for (int i = 0; i < user.quantity; i++)
    {

        strcpy(stock_name, user.stock_name[i]);
        strcat(stock_name, ".txt");
        GrabStockPrice(stock_name, stockHistory);
        for (int l = 0; l < 12; l++)
            stockhistory[l] = stockHistory[l];

        for (int j = 0; j < 12; j++)
        {
            if (round(stockhistory[0]) > round(stockhistory[j]))
            {
                buy++;
            }
            else if (round(stockhistory[0]) < round(stockhistory[j]))
            {
                sell++;
            }
            else
            {
                hold++;
            }
        }

        array[0] = (float)sell / (float)12; // probability of sell
        array[1] = (float)buy / (float)12;  // probability of buy
        array[2] = (float)hold / (float)12; // probability of hold
        // resetting the values
        sell = 0;
        buy = 0;
        hold = 0;

        float x1, x2, y0, y2, z0, z1;
        x1 = (1 - array[0]) / (float)2;
        // printf("x1 = %f\n", x1);
        x2 = (1 - array[0]) / (float)2;
        // printf("x2 = %f\n", x2);
        y0 = (1 - array[1]) / (float)2;
        // printf("y0 = %f\n", y0);
        y2 = (1 - array[1]) / (float)2;
        // printf("y2 = %f\n", y2);
        z0 = (1 - array[2]) / (float)2;
        // printf("z0 = %f\n", z0);
        z1 = (1 - array[2]) / (float)2;
        // printf("z1 = %f\n", z1);
        // printf("x1: %f, x2: %f, y0: %f, y2: %f, z0: %f, z1: %f, array[0]: %f, array[1]: %f, array[2]: %f\n", x1, x2, y0, y2, z0, z1, array[0], array[1], array[2]);
        // trMtrx = (float)malloc(sizeof(float));
        trMtrx[0][0] = array[0];
        trMtrx[0][1] = x1;
        trMtrx[0][2] = x2;
        trMtrx[1][0] = y0;
        trMtrx[1][1] = array[1];
        trMtrx[1][2] = y2;
        trMtrx[2][0] = z0;
        trMtrx[2][1] = z1;
        trMtrx[2][2] = array[2];

        x1 = 0, x2 = 0, y0 = 0, y2 = 0, z0 = 0, z1 = 0;
        for (int i = 0; i < 3; i++)
        {
            piMtrx1[0][i] = 0;
            piMtrx2[0][i] = 0;
            piMtrx3[0][i] = 0;
        }

        piMtrx1[0][0] = 0;
        piMtrx1[0][1] = 1;
        piMtrx1[0][2] = 0;

        piMtrx2[0][0] = 1;
        piMtrx2[0][1] = 0;
        piMtrx2[0][2] = 0;

        piMtrx3[0][0] = 0;
        piMtrx3[0][1] = 0;
        piMtrx3[0][2] = 1;

        for (int m = 0; m < 3; m++)
        {
            for (int n = 0; n < 3; n++)
            {
                result1[0][n] = 0;
                for (int p = 0; p < 3; p++)
                {
                    result1[0][n] += piMtrx1[0][p] * trMtrx[p][n];
                }
            }
        }

        sellProbab = max(result1, 3);

        for (int m = 0; m < 3; m++)
        {
            for (int n = 0; n < 3; n++)
            {
                result2[0][n] = 0;
                for (int p = 0; p < 3; p++)
                {
                    result2[0][n] += piMtrx2[0][p] * trMtrx[p][n];
                }
            }
        }
        buyProbab = max(result2, 3);

        for (int m = 0; m < 3; m++)
        {
            for (int n = 0; n < 3; n++)
            {
                result2[0][n] = 0;
                for (int p = 0; p < 3; p++)
                {
                    result2[0][n] += piMtrx3[0][n] * trMtrx[m][n];
                }
            }
        }

        holdProbab = max(result3, 3);

        // max of three float values
        float maxNum = 0;
        if (holdProbab > sellProbab && holdProbab > buyProbab)
        {
            maxNum = holdProbab;
        }
        else if (sellProbab > holdProbab && sellProbab > buyProbab)
        {
            maxNum = sellProbab;
        }
        else
        {
            maxNum = buyProbab;
        }

        if (maxNum == holdProbab)
        {
            user.trade.hold = 1;
        }
        else if (maxNum == sellProbab)
        {
            user.trade.sell = 1;
        }
        else if (maxNum == buyProbab)
        {
            user.trade.buy = 1;
        }

        // resetting the values
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                piMtrx1[j][k] = 0;
                piMtrx2[j][k] = 0;
                piMtrx3[j][k] = 0;
                array[j] = 0;
                result1[j][k] = 0;
                result2[j][k] = 0;
                result3[j][k] = 0;
                trMtrx[j][k] = 0;
                stockhistory[j] = 0;
            }
        }
    }
}

float max(float array[3][3], int n) // checkpoint
{
    float max = array[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (array[i][j] > max)
            {
                max = array[i][j];
            }
        }
    }
    return max;
}

float maxNum(float buy, float sell, float hold)
{
    float max = 0;
    if (buy > sell && buy > hold)
    {
        max = buy;
    }
    else if (sell > buy && sell > hold)
    {
        max = sell;
    }
    else
    {
        max = hold;
    }
    return max;
}

void MovingAvg(BUYER user, float stockHistory[])
{

    int n = 12;
    int i, sum = 0;
    char string[100];
    float arr[n], mov_avg = 0, yday_price = 0, perc_change;

    for (int j = 0; j < user.quantity; j++)
    {
        strcpy(string, user.stock_name[j]);
        strcat(string, ".txt");
        white();
        reset();
        GrabStockPrice(string, stockHistory);
        // copy the elements of stockHistory to arr
        for (i = 0; i < n; i++)
        {
            arr[i] = stockHistory[i];
        }
        // calculate the moving average
        for (i = 0; i < n; i++)
        {
            sum = sum + arr[i];
        }
        mov_avg = sum / n;
        yellow();
        printf("\n---->Moving average: %f\n", mov_avg);
        // calculate the yesterday's closing price
        yday_price = stockHistory[n - 1];
        green();
        printf("<<Yesterday's closing price: %f>>\n", yday_price);
        // calculate the percentage change
        float perc_change = ((mov_avg - yday_price) / yday_price) * 100;
        printf("\n");

        // reset the sum and mov_avg
        sum = 0;
        mov_avg = 0;

        // reset the array
        for (i = 0; i < n; i++)
        {
            arr[i] = 0;
        }

        // reset the stockHistory
        for (i = 0; i < n; i++)
        {
            stockHistory[i] = 0;
        }

        // reset the string
        strcpy(string, "");

        if (perc_change > 0)
        {
            red();

            printf("[%s should sell the stock %s]\n", user.name, user.stock_name);
            blue();
            printf(">>Percentage change: %f<<\n", perc_change);
            reset();
        }
        else if (perc_change < 0)
        {
            red();

            printf("[%s should buy the stock %s]\n", user.name, user.stock_name);
            blue();
            printf(">>Percentage change in the stock: %f<<\n", perc_change);
            reset();
        }
        else
        {
            red();

            printf("[%s should hold the stock %s]\n", user.name, user.stock_name);
            blue();
            printf(">>Percentage change: %f<<\n", perc_change);
            reset();
        }
    }
}