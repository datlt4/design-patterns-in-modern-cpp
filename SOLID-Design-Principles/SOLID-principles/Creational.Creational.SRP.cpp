#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Represents a journal with a title and a collection of journal entries.
 */
struct Journal
{
    std::string title;
    std::vector<std::string> entries;

    explicit Journal(const std::string &title) : title{title}
    {
    }

    void add(const std::string &entry);

    // persistence is a separate concern
    void save(const std::string &filename);
};

/**
 * Add a journal entry to the journal.
 */
void Journal::add(const std::string &entry)
{
    static int count = 1;
    entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
}

/**
 * Save the journal's entries to a file with the given filename.
 */
void Journal::save(const std::string &filename)
{
    std::ofstream ofs(filename);
    for (auto &s : entries)
        ofs << s << std::endl;
}

/**
 * Saves the journal entries to a file with the given filename.
 */
struct PersistenceManager
{
    static void save(const Journal &j, const std::string &filename)
    {
        std::ofstream ofs(filename);
        for (auto &s : j.entries)
            ofs << s << std::endl;
    }
};

int main()
{
    Journal journal{"Dear Diary"};
    journal.add("I ate a bug");
    journal.add("I cried today");

    // journal.save("diary.txt");

    // PersistenceManager pm;
    // pm.save(journal, "diary.txt");
    PersistenceManager::save(journal, "diary.txt");

    return 0;
}
