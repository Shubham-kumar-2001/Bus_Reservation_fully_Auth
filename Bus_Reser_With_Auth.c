#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants
#define MAX_USERS 50
#define MAX_BUSES 100
#define MAX_RESERVATIONS 1000
#define FILENAME "bus_reservations.txt"

// Define structures for user
struct User
{
    char username[50];
    char password[50];
};
// Define structures for bus and reservation
struct Bus
{
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
};

struct Reservation
{
    int reservationID;
    int busNumber;
    char passengerName[50];
    int seatNumber;
};

// Global arrays to store user, bus and reservation data
struct User users[MAX_USERS];
struct Bus buses[MAX_BUSES];
struct Reservation reservations[MAX_RESERVATIONS];

// Global counters for bus and reservation data
int userCount = 0;
int busCount = 0;
int reservationCount = 0;
int loggedInUserIndex = -1;

// Function prototypes
void displayMenu();
void registerUser();
void loginUser();
void addBus();
void displayBuses();
void bookSeat();
void cancelReservation();
void displayReservations();
void saveDataToFile();
void loadDataFromFile();

int main() {
    // Load data from a file at the start of the program
    loadDataFromFile();

    int choice;

    do {
        if (loggedInUserIndex == -1) {
            printf("You are not logged in. Please register or log in.\n");
            printf("1. Register\n");
            printf("2. Log In\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loginUser();
                    break;
                case 3:
                    saveDataToFile();
                    printf("Exiting the program.\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            displayMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addBus();
                    break;
                case 2:
                    displayBuses();
                    break;
                case 3:
                    bookSeat();
                    break;
                case 4:
                    cancelReservation();
                    break;
                case 5:
                    displayReservations();
                    break;
                case 6:
                    saveDataToFile();
                    printf("Exiting the program.\n");
                    break;
                case 7:
                    loggedInUserIndex = -1; // Log out the user
                    printf("Logged out successfully.\n");
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != 7);

    return 0;
}

void displayMenu() {
    printf("\n===== Bus Reservation System =====\n");
    printf("1. Add Bus\n");
    printf("2. Display Buses\n");
    printf("3. Book a Seat\n");
    printf("4. Cancel Reservation\n");
    printf("5. Display Reservations\n");
    printf("6. Save Data\n");
    printf("7. Log Out\n");
}
void registerUser() {
    if (userCount < MAX_USERS) {
        struct User newUser;
        printf("Enter username: ");
        scanf("%s", newUser.username);

        // Check if the username is already taken
        for (int i = 0; i < userCount; i++) {
            if (strcmp(users[i].username, newUser.username) == 0) {
                printf("Username already exists. Please choose a different username.\n");
                return;
            }
        }

        printf("Enter password: ");
        scanf("%s", newUser.password);

        users[userCount] = newUser;
        userCount++;
        printf("User registered successfully.\n");
    } else {
        printf("Maximum number of users reached.\n");
    }
}

void loginUser() {
    char username[50];
    char password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            loggedInUserIndex = i;
            printf("Logged in as %s.\n", username);
            return;
        }
    }

    printf("Login failed. Please check your username and password.\n");
}
void addBus()
{
    if (busCount < MAX_BUSES)
    {
        struct Bus newBus;
        printf("Enter bus number: ");
        scanf("%d", &newBus.busNumber);
        printf("Enter source: ");
        scanf("%s", newBus.source);
        printf("Enter destination: ");
        scanf("%s", newBus.destination);
        printf("Enter total seats: ");
        scanf("%d", &newBus.totalSeats);
        newBus.availableSeats = newBus.totalSeats;

        buses[busCount] = newBus;
        busCount++;
        printf("Bus added successfully.\n");
    }
    else
    {
        printf("Maximum number of buses reached.\n");
    }
}

void displayBuses()
{
    if (busCount == 0)
    {
        printf("No buses available.\n");
        return;
    }

    printf("\n===== Available Buses =====\n");
    for (int i = 0; i < busCount; i++)
    {
        printf("Bus Number: %d\n", buses[i].busNumber);
        printf("Source: %s\n", buses[i].source);
        printf("Destination: %s\n", buses[i].destination);
        printf("Total Seats: %d\n", buses[i].totalSeats);
        printf("Available Seats: %d\n", buses[i].availableSeats);
        printf("----------------------------\n");
    }
}

void bookSeat()
{
    if (busCount == 0)
    {
        printf("No buses available to book a seat.\n");
        return;
    }

    int busNumber, seatNumber;
    printf("Enter bus number: ");
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < busCount; i++)
    {
        if (buses[i].busNumber == busNumber)
        {
            busIndex = i;
            break;
        }
    }

    if (busIndex != -1)
    {
        if (buses[busIndex].availableSeats > 0)
        {
            struct Reservation newReservation;
            printf("Enter passenger name: ");
            scanf("%s", newReservation.passengerName);
            seatNumber = buses[busIndex].totalSeats - buses[busIndex].availableSeats + 1;

            newReservation.reservationID = reservationCount + 1;
            newReservation.busNumber = busNumber;
            newReservation.seatNumber = seatNumber;

            reservations[reservationCount] = newReservation;
            reservationCount++;

            buses[busIndex].availableSeats--;
            printf("Seat booked successfully.\n");
        }
        else
        {
            printf("No available seats on this bus.\n");
        }
    }
    else
    {
        printf("Bus not found.\n");
    }
}

void cancelReservation()
{
    if (reservationCount == 0)
    {
        printf("No reservations to cancel.\n");
        return;
    }

    int reservationID;
    printf("Enter reservation ID: ");
    scanf("%d", &reservationID);

    int reservationIndex = -1;
    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].reservationID == reservationID)
        {
            reservationIndex = i;
            break;
        }
    }

    if (reservationIndex != -1)
    {
        int busIndex = -1;
        for (int i = 0; i < busCount; i++)
        {
            if (buses[i].busNumber == reservations[reservationIndex].busNumber)
            {
                busIndex = i;
                break;
            }
        }

        buses[busIndex].availableSeats++;
        for (int i = reservationIndex; i < reservationCount - 1; i++)
        {
            reservations[i] = reservations[i + 1];
        }
        reservationCount--;
        printf("Reservation canceled successfully.\n");
    }
    else
    {
        printf("Reservation not found.\n");
    }
}

void displayReservations()
{
    if (reservationCount == 0)
    {
        printf("No reservations available.\n");
        return;
    }

    printf("\n===== Reservations List =====\n");
    printf("Reservation ID | Bus Number | Passenger Name | Seat Number\n");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < reservationCount; i++)
    {
        printf("%-15d | %-10d | %-15s | %-10d\n",
               reservations[i].reservationID,
               reservations[i].busNumber,
               reservations[i].passengerName,
               reservations[i].seatNumber);
    }
    printf("---------------------------------------------------------\n");
}

void saveDataToFile() {
    // Save user data to a text file
    FILE *userFile = fopen("users.txt", "w");
    if (userFile == NULL) {
        printf("Error opening user data file for writing.\n");
        return;
    }
    
    for (int i = 0; i < userCount; i++) {
        fprintf(userFile, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(userFile);

    // Save bus data to a text file
    FILE *busFile = fopen("buses.txt", "w");
    if (busFile == NULL) {
        printf("Error opening bus data file for writing.\n");
        return;
    }

    for (int i = 0; i < busCount; i++) {
        fprintf(busFile, "%d %s %s %d %d\n", buses[i].busNumber, buses[i].source, buses[i].destination, buses[i].totalSeats, buses[i].availableSeats);
    }

    fclose(busFile);

    // Save reservation data to a text file
    FILE *reservationFile = fopen("reservations.txt", "w");
    if (reservationFile == NULL) {
        printf("Error opening reservation data file for writing.\n");
        return;
    }

    for (int i = 0; i < reservationCount; i++) {
        fprintf(reservationFile, "%d %d %s %d\n", reservations[i].reservationID, reservations[i].busNumber, reservations[i].passengerName, reservations[i].seatNumber);
    }

    fclose(reservationFile);

    printf("Data saved to files successfully.\n");
}

void loadDataFromFile() {
    // Load user data from the text file
    FILE *userFile = fopen("users.txt", "r");
    if (userFile == NULL) {
        printf("Error opening user data file for reading.\n");
        return;
    }

    while (fscanf(userFile, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
        userCount++;
    }

    fclose(userFile);

    // Load bus data from the text file
    FILE *busFile = fopen("buses.txt", "r");
    if (busFile == NULL) {
        printf("Error opening bus data file for reading.\n");
        return;
    }

    while (fscanf(busFile, "%d %s %s %d %d", &buses[busCount].busNumber, buses[busCount].source, buses[busCount].destination, &buses[busCount].totalSeats, &buses[busCount].availableSeats) != EOF) {
        busCount++;
    }

    fclose(busFile);

    // Load reservation data from the text file
    FILE *reservationFile = fopen("reservations.txt", "r");
    if (reservationFile == NULL) {
        printf("Error opening reservation data file for reading.\n");
        return;
    }

    while (fscanf(reservationFile, "%d %d %s %d", &reservations[reservationCount].reservationID, &reservations[reservationCount].busNumber, reservations[reservationCount].passengerName, &reservations[reservationCount].seatNumber) != EOF) {
        reservationCount++;
    }

    fclose(reservationFile);

    printf("Data loaded from files successfully.\n");
}
