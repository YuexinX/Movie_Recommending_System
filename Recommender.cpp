#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"
#include "utility.h"

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
//Recommender:: ~Recommender()
//{
//    delete udb;
//    delete mdb;
//}
Recommender::Recommender(const UserDatabase& user_database,
                         const MovieDatabase& movie_database)
{

    udb = &user_database;
    mdb = &movie_database;
}

vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    //taking in an email address for a user and the count for movie
    //using the email to find all of the movies the user has watched in the past p->gethistory
    User* u = udb->get_user_from_email(user_email);
    std::vector<std::string> history = u->get_watch_history();//this is a bunch of mvie id.
    //determing a compatibilit score
    std::vector<Movie*> watchedMovies;
    TreeMultimap<std::string, int> scores;
    
    unordered_map<std::string, int> scoreM;
    
    std::vector<std::string> ids;
    for(int i = 0; i<history.size();i++)
    {
        //add all the movie into a movie vector
        std::string id = history[i];
        Movie * m = mdb->get_movie_from_id(id);
        watchedMovies.push_back(m);
    }
    for(int j = 0; j<watchedMovies.size(); j++)
    {
        std::string movie_id = history[j];
        //get the director list
        std::vector<std::string> directors = watchedMovies[j]->get_directors();
        //moive.find movies based on director
//        std::vector<std::string> movies;
        for(int k = 0; k<directors.size(); k++)
        {
            if(mdb->get_movies_with_director(directors[k]).size()>1)
            {
                for(int l=0; l<mdb->get_movies_with_director(directors[k]).size();l++)
                {
                    std::string id= mdb->get_movies_with_director(directors[k])[l]->get_id();
                    if(id!=movie_id)
                    {
                        insertMap(scoreM, 20, id);
                    }
                }
            }
        }
        //for the found movies:
        
        //if they are one of the history, disregard, if not map their id with their score.
        //for actors;
        
        
        std::vector<std::string> actors = watchedMovies[j]->get_actors();
        //moive.find movies based on director
//        std::vector<std::string> movies1;
        for(int k = 0; k<actors.size(); k++)
        {
            std::string actor = actors[k];
            if(mdb->get_movies_with_actor(actor).size()>1)
            {
                for(int l=0; l<mdb->get_movies_with_actor(actor).size();l++)
                {
                    std::string id = mdb->get_movies_with_actor(actor)[l]->get_id();
                    if(id!=movie_id)
                    {
                        insertMap(scoreM, 30, id);
                    }
                }
            }
        }
        
        
        //for genre;
        std::vector<std::string> genres = watchedMovies[j]->get_genres();
        //moive.find movies based on genres
//        std::vector<std::string> movies2;
        for(int k = 0; k<genres.size(); k++)
        {
            std::string genre = genres[k];
            if(mdb->get_movies_with_genre(genre).size()>1)
            {
                for(int l=0; l<mdb->get_movies_with_genre(genre).size();l++)
                {
                    std::string id = mdb->get_movies_with_genre(genre)[l]->get_id();
                    if(id!=movie_id)
                    {
                        insertMap(scoreM, 1, id);
                    }
                }
            }
        }
    }
    std::vector<MovieAndRank> List;
    std::unordered_map<std::string, int>::iterator it;
    for(it = scoreM.begin(); it != scoreM.end();)
    {
        if(std::find(history.begin(), history.end(), it->first) != history.end())
            it = scoreM.erase(it);
        else
        {
            MovieAndRank mMovie(it->first, it->second);
            List.push_back(mMovie);
            ++it;
        }
    }
    //calculate the total score for the movies and add to the vector
//
//    for(int i = 0; i<ids.size();i++)
//    {
//        int score=0;
//        TreeMultimap<std::string, int>::Iterator it;
//        it = scores.find(ids[i]);
//        while(it.is_valid())
//        {
//            score +=it.get_value();
//            it.advance();
//        }
//        MovieAndRank nMovieAndRank(ids[i], score);
//        List.push_back(nMovieAndRank);
//    }
    //quick sort the vector using sort function
    quickSort(List, 0, List.size()-1);
    if(movie_count>=List.size())
        return List;
    std::vector<MovieAndRank> finlList;
    for(int i = 0;i<movie_count;i++)
    {
        finlList.push_back(List[i]);
    }
    return finlList;  // Replace this line with correct code.
}

bool Recommender::cmp(const MovieAndRank& m1, const MovieAndRank& m2) const
{
    if(m1.compatibility_score>m2.compatibility_score)
        return true;
    if(m1.compatibility_score<m2.compatibility_score)
        return false;
    else
    {
        Movie* mo1 = mdb->get_movie_from_id(m1.movie_id);
        Movie* mo2 = mdb->get_movie_from_id(m2.movie_id);
        float rate1 = mo1->get_rating();
        float rate2 = mo2->get_rating();
        if(rate1>rate2)
            return true;
        if(rate1<rate2)
            return false;
        else
        {
            std::string s1 = mo1->get_title();
            std::string s2 = mo2->get_title();
            return s1<s2;
        }
    }
}
bool Recommender::lessOrEqual(const MovieAndRank& m1, const MovieAndRank& m2) const
{
    if(m1.compatibility_score>m2.compatibility_score)
        return true;
    if(m1.compatibility_score<m2.compatibility_score)
        return false;
    else
    {
        Movie* mo1 = mdb->get_movie_from_id(m1.movie_id);
        Movie* mo2 = mdb->get_movie_from_id(m2.movie_id);
        float rate1 = mo1->get_rating();
        float rate2 = mo2->get_rating();
        if(rate1>rate2)
            return true;
        if(rate1<rate2)
            return false;
        else
        {
            std::string s1 = mo1->get_title();
            std::string s2 = mo2->get_title();
            return s1<=s2;
        }
    }
}



//void Recommender::RecList(const std::vector<std::string> &movies, const std::vector<std::string> &history, TreeMultimap<std::string, int> &scores, std::vector<std::string> &ids, const int &point) const
//{
//    //for the found movies:
//    if(!movies.empty())
//    {
//        for(int k = 0; k<movies.size();k++)
//        {
//            if(std::find(ids.begin(), ids.end(), movies[k])==ids.end())
//                ids.push_back(movies[k]);
//            scores.insert(movies[k], point);
//        }
//    }
//}
unsigned long Recommender::partitian(std::vector<MovieAndRank> &List, unsigned long low, unsigned long high) const
{
    unsigned long pi = low;
    MovieAndRank pivot = List[low];
    MovieAndRank temp("",0);
    do
    {
        while(low<=high && lessOrEqual(List[low], pivot))
            low++;
        while(cmp(pivot, List[high]))
            high--;
        if(low <high)
        {
            temp = List[low];
            List[low] = List[high];
            List[high] = temp;
        }
        
    }while(low<high);
    temp = List[pi];
    List[pi] = List[high];
    List[high] = temp;
    pi = high;
    return pi;
}
void Recommender::quickSort(std::vector<MovieAndRank> &List, unsigned long low, unsigned long high) const
{
    if(high - low >=1)
    {
        unsigned long pivotIndex = partitian(List, low, high);
        if(pivotIndex != low)
            quickSort(List, low, pivotIndex-1);
        if(pivotIndex != high)
            quickSort(List, pivotIndex+1, high);
    }
}
void Recommender::insertMap(std::unordered_map<std::string, int> &map, const int &score, const std::string &id) const
{
    unordered_map <string,int>::iterator iter = map.find(id);
    if(iter == map.end())
        map[id] = score;
    else
        iter->second += score;
}
