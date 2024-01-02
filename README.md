# Snowfall Data Calculator

This C program is designed to calculate the total snowfall height for a specific village in Tirol over a range of days. The program takes user input for the village name and the target day, processes the data from multiple files (each representing a day), and outputs the total snowfall height for the specified village.

## Features

- **User Input:** The program prompts the user to enter the village name and the target day (ranging from 1 to 8).
  
- **Data Processing:** It reads snowfall data from individual files corresponding to each day, extracts the relevant information for the specified village, and calculates the total snowfall height.

- **File Output:** The program generates a new text file containing the calculated total snowfall height for the specified village and day.

## Usage

1. Compile the C program:
   - gcc -Wall -Werror -o snowfall_calculator

3. Run the program:
   - ./snowfall_calculator

5. Follow the prompts to enter the village name and target day.

6. The program will generate a new text file in the "snow_data" directory with the calculated total snowfall height.
