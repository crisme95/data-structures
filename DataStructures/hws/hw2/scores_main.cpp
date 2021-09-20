#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "scores.h"

// Function that returns total number of players who made strikes
unsigned int check_strikes(const std::vector<Scores> &players)
{
    unsigned int players_strikes = 0;
    for (unsigned int i = 0; i < players.size(); ++i)
    {
        if (players[i].total_strikes() > 0)
        {
            players_strikes += 1;
        }
    }
    return players_strikes;
}

int main(int argc, char *argv[])
{

    // Checks if there are enough command line arguments
    if (argc != 4)
    {
        std::cerr << "Missing command line arguments." << std::endl;
        return 1;
    }

    std::ifstream in_str(argv[1]); // Opens file for reading

    // Checks if opening the file for reading was successful
    if (!in_str)
    {
        std::cerr << "Couldn't open" << argv[1] << " to read." << std::endl;
        return 1;
    }

    std::ofstream out_str(argv[2]); // Opens file for writing

    // Checks if opening the file for writing was successful
    if (!out_str)
    {
        std::cerr << "Couldn't open" << argv[2] << " to write." << std::endl;
        return 1;
    }

    const std::string statistic = argv[3];

    std::vector<Scores> players;
    Scores one_player;

    // Reads all the players in the file
    while (one_player.read(in_str))
    {
        players.push_back(one_player);
    }

    unsigned int max_length = 0;
    for (unsigned int i = 0; i < players.size(); ++i)
    {
        players[i].compute_score();
        unsigned int tmp_length = players[i].first_name().length() + players[i].last_name().length() + 1;
        max_length = std::max(max_length, tmp_length);
    }

    // Sorts players alphabetically
    std::sort(players.begin(), players.end(), less_names);

    out_str << std::string(max_length + 66, '-') << std::endl;
    for (unsigned int i = 0; i < players.size(); ++i)
    {
        unsigned int name_length = players[i].last_name().length() + players[i].first_name().length() + 1;
        out_str << "| ";
        players[i].output_name(out_str);
        out_str << std::string(max_length - name_length, ' ') + " ";
        players[i].output_frame(out_str);
        out_str << "| " << std::string(max_length, ' ') + " ";
        players[i].output_scores(out_str);
        out_str << std::string(max_length + 66, '-') << std::endl;
    }

    // Prints out standard statistic
    if (statistic == "standard")
    {
        // Sorts by scores
        std::sort(players.begin(), players.end(), less_scores);

        out_str << std::endl;
        for (unsigned int i = 0; i < players.size(); ++i)
        {
            unsigned int name_length = players[i].last_name().length() + players[i].first_name().length() + 1;
            players[i].output_name(out_str);
            out_str << std::string(max_length - name_length, ' ') + "  ";

            // Right justifies the scores because the std::right wasn't working for whatever reason
            if (players[i].total_score() < 10)
            {
                out_str << "  " << players[i].total_score() << std::endl;
            }
            else if (players[i].total_score() >= 10 && players[i].total_score() < 100)
            {
                out_str << " " << players[i].total_score() << std::endl;
            }
            else
            {
                out_str << players[i].total_score() << std::endl;
            }
        }
    }
    // Prints out strikes in descending order
    else if (statistic == "custom")
    {
        out_str << std::endl;

        // Sorts by strikes
        std::sort(players.begin(), players.end(), less_strikes);

        // Checks if any players bowled a perfect game
        std::vector<std::string> perfect_game;
        for (unsigned int i = 0; i < players.size(); ++i)
        {
            if (players[i].total_strikes() == 12)
            {
                perfect_game.push_back(players[i].first_name() + " " + players[i].last_name());
            }
        }

        // Prints out people who bowled a perfect game
        if (perfect_game.size() >= 1)
        {
            out_str << "Congrats to the following players who bowled a perfect game:" << std::endl;
            for (unsigned int i = 0; i < perfect_game.size(); ++i)
            {
                out_str << perfect_game[i] << std::endl;
            }
            out_str << std::endl;
        }

        unsigned int players_strikes = check_strikes(players);

        // Prints out sad message if no one made any strikes
        if (players_strikes == 0)
        {
            out_str << "No one made any strikes this game :(" << std::endl;
        }
        // Prints out people who made strikes and how many
        else if (players_strikes >= 1)
        {
            out_str << "The following player(s) made strikes this game:" << std::endl;
            for (unsigned int i = 0; i < players.size(); ++i)
            {
                // Right justifies the scores because the std::right wasn't working for whatever reason
                if (players[i].total_strikes() < 10 && players[i].total_strikes() != 0)
                {
                    unsigned int name_length = players[i].last_name().length() + players[i].first_name().length() + 1;
                    players[i].output_name(out_str);
                    out_str << std::string(max_length - name_length, ' ') + "  ";
                    out_str << "  " << players[i].total_strikes() << std::endl;
                }
                else if (players[i].total_strikes() >= 10 && players[i].total_strikes() < 100 && players[i].total_strikes() != 0)
                {
                    unsigned int name_length = players[i].last_name().length() + players[i].first_name().length() + 1;
                    players[i].output_name(out_str);
                    out_str << std::string(max_length - name_length, ' ') + "  ";
                    out_str << " " << players[i].total_strikes() << std::endl;
                }
            }
        }
    }
    return 0;
}
