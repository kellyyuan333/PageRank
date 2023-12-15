#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <utility>
#include <vector>
#include <iomanip>

using namespace std;

class AdjacencyList
{
    private:
        map<string, vector<pair<string, int>>> adjList; //adjacency list (M)
        map<string, double> ranks; //current rank values for each URL (r)
        void insertHelper(string i, string j, map<string, int> outgoing);
    public:
        void pageRank(int p, std::ostream& os);
        void insert(vector<string> fromValues, vector<string> toValues, int n);
};

//checks some conditions before inserting to determine what parameters to pass in (for example if it has no in degrees, use "" as from string)
void AdjacencyList::insert(vector<string> fromValues, vector<string> toValues, int n)
{
    map<string, int> outgoingDegrees; //holds outgoing degrees of URLs
    for (int j = 0; j < n; j++)
    {
        outgoingDegrees[fromValues[j]]++; //increments the outgoing degree of the from URL
        outgoingDegrees[toValues[j]]++; //inserts the to URL into outgoingDegrees, even though it did not add a new link to it
        outgoingDegrees[toValues[j]]--;
    }
    //add vertices/edge(from->to) to adjacency list from input lines
    for (int j = 0; j < n; j++)
    {
        insertHelper(fromValues[j], toValues[j], outgoingDegrees);
    }
}

//inserts a new link using from and to URLs
void AdjacencyList::insertHelper(string i, string j, map<string, int> outgoing)
{
    pair<string, int> thePair = make_pair(i, outgoing[i]); //pair of from URL and its outgoing degree
    adjList[j].push_back(thePair); //connect the pair to the to URL
    if (adjList.find(i) == adjList.end())
    {
        adjList[i] = {};
    }
}

//calculates and prints the pageranks 
void AdjacencyList::pageRank(int p, std::ostream& os = std::cout)
{
    double initialRank = 1.0/adjList.size(); //every URL's ranks starts with 1/(the size of the adjacency list) or 1/|V|
    for (map<string, vector<pair<string, int>>>::iterator it = adjList.begin(); it != adjList.end(); it++)
    {
        ranks[it->first] = initialRank;
    }
    map<string, double> newRanks; //holds the new ranks
    for (int k = 0; k < p - 1; k++) //iterate (power iterations - 1) times
    {
        for (map<string, vector<pair<string, int>>>::iterator it = adjList.begin(); it != adjList.end(); it++) //iterate through every URL
        {
            double outgoingDeg = 0.0;
            double newRank = 0.0;
            for (long long unsigned int m = 0; m < it->second.size(); m++) //iterate through the vector of pairs for each URL/key in the map
            {
                if (it->second[m].second != 0)
                {
                    outgoingDeg = 1.0/it->second[m].second; //calculate outgoing degree fraction 1/d
                }
                newRank += ranks[it->second[m].first] * outgoingDeg; //multiply the corresponding rank value to the outgoing degree fraction and add it to newRank
            }
            newRanks[it->first] = newRank; //insert newRank value into newRanks map to the corresponding URL
        }
        ranks = newRanks; //change ranks to hold the updated ranks in newRanks
    }
    for (map<string, vector<pair<string, int>>>::iterator it = adjList.begin(); it != adjList.end(); it++) //prints URL's and ranks
    {
        os << it->first << " "; //print URL name
        os << std::fixed << std::showpoint; //round off ranks to two decimal places
        os << std::setprecision(2);
        os << ranks[it->first] << endl; //print URL's rank
    }
}

int main()
{
    //read first number of lines (n) from cin
    int n;
    cin >> n;
    cin.ignore();
    //read the number of power interations (p) from cin
    int p;
    cin >> p;
    cin.ignore();
    AdjacencyList graph; //create a graph object
    vector<string> fromValues; //holds from URLs
    vector<string> toValues; //holds to URLs
    //for each of the next n lines, read in the vertices from and to
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        istringstream in(line);
        //read in the source vertex
        string from;
        in >> from;
        fromValues.push_back(from);
        //read in the destination vertex
        string to;
        in >> to;
        toValues.push_back(to);
    }
    graph.insert(fromValues, toValues, n); //add vertices/edge(from->to) to adjacency list
    graph.pageRank(p); //do power iterations and print the result
    return 0; 
}