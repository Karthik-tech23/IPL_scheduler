#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct team{
    char team_name[5];
    char homeground[20];
    int homeplay;
    int won;
    int lost;
    int pld;
    int draws;
    int points;
    float NRR;
} Team;

// Function for Data input 
void Input(int n, Team teams[n]){
    int i;
    printf("\nEnter teams in Preferential Order:");
    printf("\n");
    for (i = 0; i < n; i++){
        printf("Team-%d: ", (i+1));
        scanf("%s", teams[i].team_name);
        char ground[20];
        printf("Enter %s's Homeground: ", teams[i].team_name);
        scanf("%s", teams[i].homeground);
    }
}

// Function for Date and Time updation 
// Date format: dd-mm-yyyy & Time format: hr:min
void DateAndTime(int dates[3], char time[6]){
    int date, month, year;
    date = dates[0];
    month = dates[1];
    year = dates[2];
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
        if (date == 31){
            if (month == 12){
                date = 1;
                month = 1;
                year=year+1;
            }
            else {
                date = 1;
                month=month+1;
            }
        }
        else {
            date=date+1;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11){
        if (date == 30){
            date = 1;
            month=month+1;
        }
        else {
            date=date+1;
        }
    }
    else if (month == 2){
        if (date == 28){
            if (year % 4 == 0){
                date=date+1;
            }
            else {
                date = 1;
                month=month+1;
            }
        }
        else if (date == 29){
            date = 1;
            month=month+1;
        }
    }
    dates[0] = date; dates[1] = month; dates[2] = year;
    printf("%d-%d-%d, %s\n", dates[0], dates[1], dates[2], time);
}

// Function for determining the venue of match
void Venue(char hg1[20], char hg2[20], int hp1, int hp2, int n, Team teams[n], int first, int second){
    if (hp1 > hp2){
        printf("%s\n", hg2);
        teams[second].homeplay++;
    }
    else if (hp1 < hp2){
        printf("%s\n", hg1);
        teams[first].homeplay++;
    }
    else {
        printf("%s\n", hg2);
        teams[second].homeplay++;
    }
}

// This function used only in auto-generated mode
void Score(int n, Team teams[n], int first, int second, int op){
    int t1_score, t2_score;
    if (op == 1){
        printf("Enter score of %s:", teams[first].team_name);
        scanf("%d", t1_score);
        printf("Enter score of %s:", teams[second].team_name);
        scanf("%d", t2_score);
    }
    else {
        t1_score = rand() % 250;
        printf("Score of %s: %d\n", teams[first].team_name, t1_score);
        t2_score = rand() % 250;
        if ((t2_score - t1_score) > 7){
            t2_score = t1_score+(rand()%5 +1);
        }
        printf("Score of %s: %d\n", teams[second].team_name, t2_score);
    }
    printf("RunRate of %s is %.2f\n", teams[first].team_name, (t1_score/20.0));
    printf("RunRate of %s is %.2f\n", teams[second].team_name, (t2_score/20.0));
    if (t1_score > t2_score){
        teams[first].won++;
        teams[second].lost++;
    }
    else if (t1_score < t2_score){
        teams[first].lost++;
        teams[second].won++;
    }
    else {
        teams[first].draws++;
        teams[second].draws++;
    }
    teams[first].NRR = (t1_score/20.0)-(t2_score/20.0);
    teams[second].NRR = (t2_score/20.0)-(t1_score/20.0);
}

void Arrange(int n, int fixtures[n]){
    int i, temp;
    for (i = 1; i < n-1; i ++){
        temp = fixtures[i];
        fixtures[i] = fixtures[i+1];
        fixtures[i+1] = temp;
    }
}

void Schedule(int num, Team teams[num], int op){
    int round, i, j, match = 1;
    int d, m, y;
    int fixtures[num];
    for (i = 0; i < num; i++){
        fixtures[i] = i;
    }
    int date[3];
    printf("\nEnter tournament's start date:");
    scanf("%d-%d-%d", &date[0], &date[1], &date[2]);
    char time[6];
    printf("Enter time:");
    scanf("%s", time);

    for (round = 1; round <= (num-1); round++){
        for (i = 0, j = (num-1); i < (num/2), j >= 1; i++, j -= 2){
            printf("\nMATCH-%d\n", match);
            DateAndTime(date, time);
            int first, second;
            first = fixtures[i];
            second = fixtures[i+j];
            Venue(teams[first].homeground, teams[second].homeground, teams[first].homeplay, teams[second].homeplay, num, teams, first, second);
            printf("%s vs. %s\n", teams[first].team_name, teams[second].team_name);
            teams[first].pld++;
            teams[second].pld++;
            Score(num, teams, first, second, op);
            if (i == (num/2)-1){
                Arrange(num, fixtures);
            }
            match++;
        }
    }
}

int SuperOver(char team1[4], char team2[2]){
    int t1_score, t2_score;
    printf("Enter score of %s in Super-over: ", team1);
    scanf("%d", &t1_score);
    printf("Enter score of %s in Super-over: ", team2);
    scanf("%d", &t2_score);
    if (t1_score > t2_score){
        return 1;
    }
    else {
        return 2;
    }
}

int WinningDecider(char team1[4], char team2[4], int team1_score, int team2_score){
    if (team1_score > team2_score){
        return 1;
    }
    else if (team1_score < team2_score){
        return 2;
    }
    else {
        int won_team = SuperOver(team1, team2);
        if (won_team == 1){
            return 1;
        }
        else {
            return 2;
        }
    }
}

void Qualifier(int n, Team teams[n], int position[n]){
    char qualified1[4], qualified2[4], finalist1[4], finalist2[4];
    int won_team = 0;
    printf("\n--------------QUALIFIERS-----------------\n");
    
    printf("Qualifiers-1\n");
    printf("%s vs %s", teams[position[0]].team_name, teams[position[1]].team_name);
    int team1_score, team2_score;
    printf("\nEnter score of %s: ", teams[position[0]].team_name);
    scanf("%d", &team1_score);
    printf("Enter score of %s: ", teams[position[1]].team_name);
    scanf("%d", &team2_score);
    won_team = WinningDecider(teams[position[0]].team_name, teams[position[1]].team_name, team1_score, team2_score);
    if (won_team == 1){
        strcpy(finalist1, teams[position[0]].team_name);
        strcpy(qualified1, teams[position[1]].team_name);
    }
    else {
        strcpy(finalist1, teams[position[1]].team_name);
        strcpy(qualified1, teams[position[0]].team_name);
    }

    printf("\nEliminator\n");
    printf("%s vs %s\n", teams[position[2]].team_name, teams[position[3]].team_name);
    team1_score = team2_score = 0;
    printf("Enter score of %s: ", teams[position[2]].team_name);
    scanf("%d", &team1_score);
    printf("Enter score of %s: ", teams[position[3]].team_name);
    scanf("%d", &team2_score);
    won_team = WinningDecider(teams[position[0]].team_name, teams[position[1]].team_name, team1_score, team2_score);
    if (won_team == 1){
        strcpy(qualified2, teams[position[2]].team_name);
        printf("%s is Eliminated.\n", teams[position[3]].team_name);
    }
    else {
        strcpy(qualified2, teams[position[3]].team_name);
        printf("%s is Eliminated.", teams[position[2]].team_name);
    }
    
    printf("\n\nQualifier-2\n");
    printf("%s vs %s", qualified1, qualified2);
    team1_score = team2_score = 0;
    printf("Enter score of %s: ", qualified1);
    scanf("%d", &team1_score);
    printf("Enter score of %s: ", qualified2);
    scanf("%d", &team2_score);
    won_team = WinningDecider(qualified1, qualified2, team1_score, team2_score);
    if (won_team == 1){
        strcpy(finalist2, qualified1);
        printf("%s is Eliminated.\n", qualified2);
    }
    else {
        strcpy(finalist2, qualified2);
        printf("%s is Eliminated.\n", qualified1);
    }
    
    printf("\nFinal\n");
    printf("%s vs. %s", finalist1, finalist2);
    team1_score = team2_score = 0;
    printf("\nEnter score of %s: ", finalist1);
    scanf("%d", &team1_score);
    printf("Enter score of %s: ", finalist2);
    scanf("%d", &team2_score);
    won_team = WinningDecider(finalist1, finalist2, team1_score, team2_score);
    if (won_team == 1){
        printf("\n\t%s IS THE IPL TITLE WINNER.\n", finalist1);
    }
    else {
        printf("\n\t%s IS THE IPL TITLE WINNER.\n", finalist2);
    }
}

void PointsTable(int n, Team teams[n]){
    int i, j, temp;
    int points[n], position[n];
    for (i = 0; i < n; i++){
        teams[i].points = (2*teams[i].won)+(teams[i].draws);
        points[i] = teams[i].points;
        position[i] = i;
    }
    
    for (i = 0; i < n; i++){
        for (j = 0; j < n-i-1; j++){
            if (points[j] < points[j+1]){
                temp = points[j+1];
                points[j+1] = points[j];
                points[j] = temp;
                temp = position[j];
                position[j] = position[j+1];
                position[j+1] = temp;
            }
        }
    }
    printf("\n---------------POINTS TABLE -------------------");
    printf("\n\nTeam\tPlayed\tWon\tLost\tDraws\tNet RR\tPoints\n");
    for (i = 0; i < n; i++){
        printf("%s\t%d\t%d\t%d\t%d\t%.2f\t%d\n", teams[position[i]].team_name, teams[position[i]].pld, teams[position[i]].won, teams[position[i]].lost, teams[position[i]].draws, teams[position[i]].NRR, teams[position[i]].points);
    }
    Qualifier(n, teams, position);
}

int main(){ 
    printf("-----------------------------------------------------------------\n");
    printf("\t\tTeam-7 (CSE Project): IPL SCHEDULER\n");
    printf("-----------------------------------------------------------------\n");
    int num, i;
    printf("\n\nEnter the number of teams playing:");
    scanf("%d", &num);
    Team teams[num];
    Input(num, teams);      //Function to get team names from the user
    
    // Initializing values to some variables
    for (i = 0; i < num; i++){
        teams[i].homeplay = 0;
        teams[i].won = 0;
        teams[i].pld = 0;
        teams[i].lost = 0;
        teams[i].draws = 0;
        teams[i].points = 0;
        teams[i].NRR = 0.0;
    }
    int option;
    printf("Want to enter scores by yourself(1)/auto-generate scores(2)?...");
    scanf("%d", &option);
    Schedule(num, teams, option);
    PointsTable(num, teams);
}