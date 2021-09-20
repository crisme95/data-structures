#ifndef _inventory_h_
#define _inventory_h_

#include <list>
#include <string>

class Inventory
{

public:
    // Accessors
    std::string get_name() const { return name_; }
    int get_total_copies() const { return total_copies_; }
    int get_copies() const { return copies_; }
    bool available() const { return copies_ > 0; }

    // Modifiers
    void set_name(const std::string &name) { name_ = name; }
    void set_total_copies(const int total_copies);
    void add_copies(const int copies);
    void shipped() { copies_ -= 1; }
    void returned() { copies_ += 1; }

private:
    std::string name_;
    int total_copies_; // Total copies in the system
    int copies_;       // Total copies available
};

#endif