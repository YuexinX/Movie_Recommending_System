#ifndef Recommender_h
#define Recommender_h

#include <string>
#include <vector>
#include "MovieDatabase.h"
#include "UserDatabase.h"
#include <unordered_map>


struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};


class Recommender
{
public:
    Recommender(const UserDatabase& user_database,
                const MovieDatabase& movie_database);
//    ~Recommender();
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email,
                                               int movie_count) const;
    
private:
    const UserDatabase *udb;
    const MovieDatabase *mdb;
    bool cmp(const MovieAndRank &m1,  const MovieAndRank &m2) const;
    bool lessOrEqual(const MovieAndRank& m1, const MovieAndRank& m2) const;
    unsigned long partitian(std::vector<MovieAndRank> &List, unsigned long low, unsigned long high) const;
    void quickSort(std::vector<MovieAndRank> &List, unsigned long low, unsigned long high) const;
    
//    void RecList(const std::vector<std::string> &movies, const std::vector<std::string> &history, TreeMultimap<std::string, int> &scores, std::vector<std::string> &ids,const int &point) const;
    void insertMap(std::unordered_map<std::string, int> &map, const int &score, const std::string &id)const;
};

#endif // RECOMMENDER_INCLUDED

