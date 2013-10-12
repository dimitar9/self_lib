#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
bool isOdd(int index) {
	return ((index % 2) == 1);
}

bool checkNegative(vector<double> vec) {
	for (vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
		if ((*it) > 0)
			return false;
	}
	return true;
}
int main() {
	ifstream infile("test1.txt");
	string line;
	double a, b;
	vector<double> visit_team;
	vector<double> home_team;
	bool home_team_win = false;
	double predict_index = 0;
	for (int j = 0; j < 16; j++) {
			string line;
		double a, b;
		vector<double> visit_team;
		vector<double> home_team;
		bool home_team_win = false;
		double predict_index = 0;
		int i = 0;
		while ((++i<19) && (getline(infile, line)) ){
			
			predict_index++;

			istringstream iss(line);
			iss >> a >> b;
			if ((a > 0) && (isOdd(predict_index))) {
				home_team_win = true;
			} else if ((a < 0) && (isOdd(predict_index))) {
				home_team_win = false;
			}
			if ((home_team_win) && (!isOdd(predict_index))) {
				//cout<< "go home "<< a<<endl;
				home_team.push_back(a);
			} else if ((!home_team_win) && (isOdd(predict_index))) {
				//cout<< "go visit " << a<<endl;
				visit_team.push_back(a);
			}

		}
		if (!checkNegative(home_team)) {
			//cout << "There is positive value in home_team odds, check your code." << endl;
		}
		if (checkNegative(visit_team)) {
			//cout << "There is positive value in visit_team odds, check your code." << endl;
		}
		double sum_home = 0.0;
		double sum_visit = 0.0;
		for (vector<double>::iterator it = home_team.begin();
				it != home_team.end(); ++it) {
			//cout << *it << endl;
			sum_home += *it;
		}
		for (vector<double>::iterator it = visit_team.begin();
				it != visit_team.end(); ++it) {
			//cout << *it << endl;
			sum_visit += *it;
		}
		//cout << "there is " << (int) (predict_index /2)<< " predictions." << endl;
		//cout << "sum home is " << sum_home <<endl;
		if (sum_home < 0)
			sum_home = -((double) sum_home);
		if (sum_visit < 0)
			sum_visit = -((double) sum_visit);
		//cout << "sum_home is " << sum_home << endl;
		//cout << "sum_visit is " << sum_visit << endl;
		double final_odds = (sum_home - sum_visit)
				/ (double) (9);
		if (final_odds >= 0)
			cout << "home team win odds is " << final_odds << endl;
		else
			cout << "visit team win odds is " << -final_odds << endl;
		cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

	}

	return 0;
}
