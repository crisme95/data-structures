#ifndef __scores_h_
#define __scores_h_
#include <iostream>
#include <string>
#include <vector>
#include "name.h"

class Scores
{
public:
    //Accessors
    const std::string &first_name() const { return name_.first(); }
    const std::string &last_name() const { return name_.last(); }
    const int total_score() const { return total_score_; }
    const int total_strikes() const { return total_strikes_; }
    const std::vector<int> get_pins() const { return pins; }
    const std::vector<int> get_frame() const { return frame_score; }

    //Modifiers
    bool read(std::ifstream &in_str);
    void compute_score();

    //Print functions
    std::ostream &output_name(std::ostream &out_str) const;
    std::ostream &output_frame(std::ostream &out_str) const;
    std::ostream &output_scores(std::ostream &out_str) const;

private:
    Name name_;
    std::vector<int> pins;
    unsigned int total_score_;
    std::vector<int> frame_score;
    unsigned int total_strikes_;
};

// Sort by names function
bool less_names(const Scores &player1, const Scores &player2);

// Sort by scores function
bool less_scores(const Scores &player1, const Scores &player2);

// Sort by strikes function
bool less_strikes(const Scores &player1, const Scores &player2);

#endif