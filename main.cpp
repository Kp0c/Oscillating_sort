#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static int NUM_OF_TAPES = 5;

class Tape
{
public:
	vector<int> data;
	int max_size;

	Tape()
	{
		max_size = 0;
	}

	void SetNewData(int data)
	{
		this->data.push_back(data);

		max_size = max_size < 1 ? 1 : max_size;
	}

	friend ostream& operator<< (ostream& out,const Tape& tape)
	{
		for(int i=0; i < tape.data.size(); ++i)
		{
			cout << tape.data[i] << " " << endl;
		}

		return out;
	}
};

void PrintTapes(vector<Tape> tapes)
{
	for(int i=0; i< tapes.size(); ++i)
	{
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

	vector<int> data = {3,5,3000,7000,12000,1,123,12,31,23,123,12,35,34,123123,34,45,12,34};

	//add tapes
	for(int i = 0; i < NUM_OF_TAPES; ++i)
	{
		tapes.push_back(Tape());
	}

	tapes[NUM_OF_TAPES - 1].data = vector<int>();

	int level = 0;
	//start sorting
	while (data.size() > 0)
	{
		//fill
		if(data.size() < NUM_OF_TAPES - 1)
		{
			int data_stored = data.size();
			for(int i = 0; i < data.size(); ++i)
			{
				tapes[i].SetNewData(data[data.size() - 1]);
				data.pop_back();
			}

			for(int i = 0; i < data_stored; ++i)
			{
				tapes[NUM_OF_TAPES - 1].data = merge(tapes[NUM_OF_TAPES - 1].data, tapes[i].data);
				tapes[i].data.clear();
			}
		}
		else
		{
			for(int i = 0; i < NUM_OF_TAPES - 1 && data.size() != 0; ++i)
			{
				tapes[i].SetNewData(data[data.size() - 1]);
				data.pop_back();
			}
			//merge
			//..select max level of merge
			int max_level_of_merge = pow(NUM_OF_TAPES-1,level);
			for(int i = 0, j = 0; i <= max_level_of_merge; i = pow(NUM_OF_TAPES-1,j), ++j)
			{
				int count_on_level = count_if(tapes.begin(),tapes.end(),[=] (Tape a)
				{
					return a.max_size == i;
				});

				if(count_on_level == NUM_OF_TAPES - 1)
				{
					for (int var = 0; var < count_on_level; ++var) {
						tapes[NUM_OF_TAPES - 1].data = merge(tapes[NUM_OF_TAPES - 1].data, tapes[var].data);
						tapes[var].data.clear();
					}
				}
			}
			++level;
		}
	}

	PrintTapes(tapes);

	return 0;
}
