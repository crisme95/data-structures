#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include "scores.h"

// Reads the input file
bool Scores::read(std::ifstream &in_str)
{
   std::string first_name, last_name;
   // If there is no first name, then we've reached the end of the file
   if (!(in_str >> first_name))
   {
      return false;
   }

   in_str >> last_name;

   name_ = Name(first_name, last_name);

   // Reads pins knocked down into vector
   pins.clear();
   unsigned int points;
   while (in_str >> points)
   {
      pins.push_back(points);
   }

   // Clears input stream for next row
   in_str.clear();

   return true; // Reading was successful
}

// Computes total score for each game as well as score per frame and strikes per game
void Scores::compute_score()
{
   total_score_ = 0;
   total_strikes_ = 0;
   unsigned int frame = 1;
   for (unsigned int i = 0; i < get_pins().size(); ++i)
   {
      if (frame == 10)
      {
         while (i < get_pins().size())
         {
            if (get_pins()[i] == 10)
            {
               total_strikes_ += 1;
            }
            total_score_ += get_pins()[i];

            i += 1;
         }
         frame_score.push_back(total_score_);
         break;
      }
      else
      {
         // If throw was a strike, 10 points and the next two throws' points get added on
         if (get_pins()[i] == 10)
         {
            total_score_ += get_pins()[i] + get_pins()[i + 1] + get_pins()[i + 2];
            total_strikes_ += 1;
            frame_score.push_back(total_score_);
            frame += 1;
         }
         // If last two throws were a spare, 10 points and the next throw's points get added on
         else if ((get_pins()[i] + get_pins()[i + 1]) == 10)
         {
            total_score_ += get_pins()[i] + get_pins()[i + 1] + get_pins()[i + 2];
            frame_score.push_back(total_score_);
            frame += 1;
            i += 1;
         }
         // If last two throws weren't a spare, the points from both get added on
         else
         {
            total_score_ += get_pins()[i] + get_pins()[i + 1];
            frame_score.push_back(total_score_);
            frame += 1;
            i += 1;
         }
      }
   }
}

// Outputs the first and last name of player
std::ostream &Scores::output_name(std::ostream &out_str) const
{
   out_str << first_name() << " " << last_name();
   return out_str;
}

// Outputs how many pins where knocked down per frame
std::ostream &Scores::output_frame(std::ostream &out_str) const
{
   out_str << "|";
   unsigned int frame = 1;
   for (unsigned int i = 0; i < get_pins().size(); ++i)
   {
      // Prints out last frame
      if (frame == 10)
      {
         // If last 3 throws are strikes
         if (get_pins()[i] == 10 && get_pins()[i + 1] == 10 && get_pins()[i + 2] == 10)
         {
            out_str << " X X X |";
            break;
         }
         // If last 3 throws are strikes except last one
         else if (get_pins()[i] == 10 && get_pins()[i + 1] == 10 && get_pins()[i + 2] < 10)
         {
            out_str << " X X " << get_pins()[i + 2] << " |";
            break;
         }
         // If last 3 throws are a spare and a strike
         else if ((get_pins()[i] + get_pins()[i + 1]) == 10 && get_pins()[i + 2] == 10)
         {
            out_str << " " << get_pins()[i] << " / X |";
            break;
         }
         // If last 3 throws are a strike and a spare
         else if (get_pins()[i] == 10 && (get_pins()[i + 1] + get_pins()[i + 2]) == 10)
         {
            out_str << " X " << get_pins()[i + 1] << " / |";
            break;
         }
         // If first 2 throws aren't a spare
         else
         {
            // Checks if first throw was no pins
            if (get_pins()[i] == 0)
            {
               out_str << " -";
            }
            else
            {
               out_str << " " << get_pins()[i];
            }
            // Checks if second throw was no pins
            if (get_pins()[i + 1] == 0)
            {
               out_str << " -   |";
            }
            else
            {
               out_str << " " << get_pins()[i + 1] << "   |";
            }
            break;
         }
      }
      // Prints out each frame
      else
      {
         // If throw was a strike, this prints out an X
         if (get_pins()[i] == 10)
         {
            out_str << "   X |";
            frame += 1;
         }
         // If the 2 throws were a spare, it prints out the first throw then a slash
         else if ((get_pins()[i] + get_pins()[i + 1]) == 10)
         {
            // Checks if first throw knocked down no pins
            if (get_pins()[i] == 0)
            {
               out_str << " - / |";
            }
            else
            {
               out_str << " " << get_pins()[i] << " / |";
            }

            frame += 1;
            i += 1;
         }
         // If the 2 throws weren't a spare, then it prints out the 2 throws
         else
         {
            // Checks if first throw hit no pins
            if (get_pins()[i] == 0)
            {
               out_str << " -";
            }
            else
            {
               out_str << " " << get_pins()[i];
            }

            // Checks if second throw hit no pins
            if (get_pins()[i + 1] == 0)
            {
               out_str << " - |";
            }
            else
            {
               out_str << " " << get_pins()[i + 1] << " |";
            }

            frame += 1;
            i += 1;
         }
      }
   }
   out_str << std::endl;
   return out_str;
}

// Prints out score per frame
std::ostream &Scores::output_scores(std::ostream &out_str) const
{
   unsigned int frame = 1;
   out_str << "|";
   for (unsigned int i = 0; i < frame_score.size(); ++i)
   {
      // Checks if it's last frame
      if (frame == 10)
      {
         // Checks if the score is less than 2 digits
         if (frame_score[i] < 10)
         {
            out_str << "     " << frame_score[i] << " |";
         }
         // Checks if the score has 2 digits
         else if (frame_score[i] >= 10 && frame_score[i] < 100)
         {
            out_str << "    " << frame_score[i] << " |";
         }
         // Checks if the score has 3 digits
         else
         {
            out_str << "   " << frame_score[i] << " |";
         }
         break;
      }
      else
      {
         // Checks if score has less than 2 digits
         if (frame_score[i] < 10)
         {
            out_str << "   " << frame_score[i] << " |";
            frame += 1;
         }
         // Checks if score has 2 digits
         else if (frame_score[i] >= 10 && frame_score[i] < 100)
         {
            out_str << "  " << frame_score[i] << " |";
            frame += 1;
         }
         // Checks if score has 3 digits
         else
         {
            out_str << " " << frame_score[i] << " |";
            frame += 1;
         }
      }
   }
   out_str << std::endl;
   return out_str;
}

// Sorts alphabetically by last name then first name
bool less_names(const Scores &player1, const Scores &player2)
{
   return player1.last_name() < player2.last_name() || (player1.last_name() == player2.last_name() && player1.first_name() < player2.first_name());
}

// Sorts by scores
bool less_scores(const Scores &player1, const Scores &player2)
{
   return player1.total_score() > player2.total_score();
}

// Sorts by strikes
bool less_strikes(const Scores &player1, const Scores &player2)
{
   return player1.total_strikes() > player2.total_strikes();
}
