#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int NUM_OF_TAPES = 5;

class Tape
{
public:
    vector<vector<int>> data;

    Tape() {}

    void SetNewData(int data)
    {
        vector<int> new_data { data };
        this->data.push_back(new_data);
    }

    void SetNewData(vector<int> data)
	{
        this->data.push_back(data);
	}

    vector<int> Pop()
    {
        vector<int> tmp;
        if(data.size() > 0)
        {
            tmp = data.back();
            data.pop_back();
        }
        else
        {
            tmp = vector<int>();
        }
        return tmp;
    }

    vector<int> GetData()
    {
        if(data.size() > 0)
            return data.back();
        else
            return vector<int>();
    }

    void ChangeBack(vector<int> new_vector)
    {
        if(data.size() > 0)
            data.pop_back();

        data.push_back(new_vector);
    }

	friend ostream& operator<< (ostream& out,const Tape& tape)
	{
		for(int i=0; i < tape.data.size(); ++i)
		{
            for(int j=0; j < tape.data[i].size(); ++j)
            {
				cout << tape.data[i][j] << " " << endl;
            }
            cout << endl;
		}

		return out;
	}
};

void PrintTapes(vector<Tape> tapes)
{
	for(int i=0; i< tapes.size(); ++i)
	{
        cout << "TAPE " << i << endl;
		cout << tapes[i];
	}
}

vector<int> merge(vector<int> a, vector<int> b)
{
	vector<int> result_vector;
	bool deleted = false;
	for(auto i = a.begin(); i != a.end(); (!deleted && i != a.end()) ? ++i : i)
	{
        for(auto j = b.begin(); j != b.end() && i != a.end(); !deleted ? ++j : j, deleted = false)
		{
            if(*i < *j)
			{
				result_vector.push_back(*i);
				i = a.erase(i);
				deleted = true;
			}
			else
			{
				result_vector.push_back(*j);
				j = b.erase(j);
				deleted = true;
			}
		}
	}

	result_vector.insert(result_vector.end(), a.begin(), a.end());
	result_vector.insert(result_vector.end(), b.begin(), b.end());
	return result_vector;
}

int main()
{
	vector<Tape> tapes;

    vector<int> data;

	cout << "BEFORE SORTING: " << endl;
	for(int i = 0; i < 20; i++)
    {
		data.push_back(rand() % 1000);
		cout << data.back() << endl;
    }

	//add tapes
	for(int i = 0; i < NUM_OF_TAPES; ++i)
	{
		tapes.push_back(Tape());
    }

	int startTape = 0;
	while(!data.empty())
    {
        //select data and write to tapes
        for(int i = startTape; i < startTape + NUM_OF_TAPES - 1 && !data.empty(); ++i)
        {
            int selected_tape = i % NUM_OF_TAPES;
            tapes[selected_tape].SetNewData(data.back());
            data.pop_back();

            cout << "Write data to tape #" << selected_tape << endl;
        }

        //merge data
        int tape_to_merge = (startTape + NUM_OF_TAPES - 1) % NUM_OF_TAPES;
        for(int i = startTape; i < startTape + NUM_OF_TAPES - 1; ++i)
        {
            int selected_tape = i % NUM_OF_TAPES;
            tapes[tape_to_merge].ChangeBack(merge(tapes[tape_to_merge].GetData(),
                                                  tapes[selected_tape].Pop()));

            cout << "Merge data from tape #" << selected_tape << " to tape #" << tape_to_merge << endl;
        }

        startTape++;
    }

    //final merge
	if(count_if(tapes.begin(),tapes.end(), [] (Tape tape) { return !tape.data.empty(); }) > 1)
    {
        int tape_to_merge = (startTape + NUM_OF_TAPES - 1) % NUM_OF_TAPES;
        for(int i = startTape; i < startTape + NUM_OF_TAPES - 1; ++i)
        {
            int selected_tape = i % NUM_OF_TAPES;
            tapes[tape_to_merge].ChangeBack(merge(tapes[tape_to_merge].GetData(),
                                                  tapes[selected_tape].Pop()));

            cout << "Merge data from tape #" << selected_tape << " to tape #" << tape_to_merge << endl;
        }
	}
	cout << "AFTER SORTING (TAPES STATE): " << endl;
    PrintTapes(tapes);

	return 0;
}
