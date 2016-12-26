#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

void episode();
int getAction(int state);
vector<int> getPossible(int state);
double getQ(int state,int action);
void showQ();
void over100Q();
void findRoute(int startState);
vector<int> getMax(int state);

const int numRooms = 8;
const int goalState = 7;
const double gamma = 0.8;
const int numEpisodes = 100;
int biggestValue = 0;

vector<vector<double> > QMatrix(numRooms, vector<double>(numRooms));

int RMatrix[numRooms][numRooms] = { {-1, -1, 0, -1, 0, -1, -1, -1},
                                    {-1, -1, 0, -1, -1, -1, -1, 100},
                                    {0, 0, -1, 0, -1, 0, -1, -1},
                                    {-1, -1, 0, -1, 0, -1, -1, -1},
                                    {0, -1, -1, 0, -1, 0, 0, -1},
                                    {-1, -1, 0, -1, 0, -1, -1, 100},
                                    {-1, -1, -1, -1, 0, -1, -1, -1},
                                    {-1, 0, -1, -1, -1, 0, -1, 100}};

int main()
{
    srand(time(NULL));
    int startRoom;

    for(int i = 0;i < numEpisodes;i++)
    {
        cout << "-------Episode: " << i << endl;
        episode();
        showQ();
    }

    cout << "************* ";
    cout << endl;
    cout << endl;
    cout << endl;

    while(true)
    {
        cout << "--------------" << endl;
        cout << "find Shortest from: ";
        cin >> startRoom;
        findRoute(startRoom);
    }
}

void findRoute(int startState)
{
    int nextState;
    vector<int> result;

    while(startState != goalState)
    {
        result = getMax(startState);
        nextState = result[0];
        cout << "nextRoom is: " << nextState << endl;
        startState = nextState;
    }

}
void showQ()
{
    for(int i = 0; i < numRooms;i++)
    {
        for (int j = 0; j < numRooms;j++)
        {
            cout << QMatrix[i][j] << ", ";

        }
        cout << "." << endl;
    }

    cout << "#############" << endl;
}

vector<int> getPossible(int state)
{
    vector<int> possibleActions;
    int tank;
    //cout << "--possible actions: " << endl;
    for(int i = 0; i < numRooms;i++)
    {
        tank = RMatrix[state][i];
        if(tank != -1)
        {
            possibleActions.push_back(i);
            //cout << i << endl;
        }
    }

    return possibleActions;

}
int getAction(int state)
{
    vector<int> possibleActions = getPossible(state);
    int index;
    int action;
    int toRand = possibleActions.size();

    index = rand() % toRand;

    action = possibleActions[index];

    return action;
}

vector<int> getMax(int state)
{
    vector<int> possibleActions = getPossible(state);
    int tank;
    int biggest = 0;
    int index;
    vector<int> result;

    //cout << "--all Q: " << endl;

    result.push_back(0);
    result.push_back(0);

    for(int i = 0;i < possibleActions.size();i++)
    {
        tank = QMatrix[state][possibleActions[i]];
        //cout << tank << endl;

        if(tank >= biggest)
        {
            biggest = tank;
            index = i;
        }
    }

    result[0] = possibleActions[index];
    result[1] = biggest;

    return result;

}

double getQ(int state,int action)
{
    int Max;
    int reward;
    double Q;
    vector<int> result = getMax(action);

    Max = result[1];
    reward = RMatrix[state][action];
    Q = reward  + (gamma * Max);

    if(Q > biggestValue)
    {
        biggestValue = Q;
    }

    return Q;
}
void episode()
{
    int newState;
    int newAction;
    int newQ;
    int toRand = numRooms;

    newState = rand() % toRand;

    while(true)
    {
        newAction = getAction(newState);
        //cout << "newactio: " << newAction << endl;

        newQ = getQ(newState,newAction);

        //cout << "newQ: " << newQ << endl;

        QMatrix[newState][newAction] = newQ;

        newState = newAction;

        if(newState = goalState)
        {
            break;
        }
    }
}

