# Simulate a sports tournament, given a .csv file in the command line argument with 16 teams and their relative strength (in numerical points),
# with the first line in the file reading exactly "team,rating"

import csv
import sys
import random

# Number of simluations to run
while True:
    try:
        N = int(input("Number of simulations to run: "))
        if N > 0 and N < 1000001:
            break
        elif N > 1000000:
            print("Number too big!")
    except ValueError:
        print("Number is not valid!")



def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # Read teams into memory from file
    teams = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            team = {"team": [], "rating": []}
            team["team"].append(row["team"])
            team["rating"].append(row["rating"])
            teams.append(team)

    # Simulate N tournaments and keep track of win counts
    counts = {}
    for k in range(N):
        winnert = simulate_tournament(teams)
        if winnert in counts:
            counts[winnert] += 1
        else:
            counts[winnert] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = int(team1["rating"][0])
    rating2 = int(team2["rating"][0])
    print(rating1)
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []
    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])
    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) != 1:
        teams = simulate_round(teams)
    # Returns only the string with the winner team's name
    tourwinner = teams[0]["team"][0]
    return tourwinner


if __name__ == "__main__":
    main()
