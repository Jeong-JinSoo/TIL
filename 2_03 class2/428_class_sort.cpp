//클래스 정렬하기 //함수 전달

#include <iostream>
#include <algorithm>		//algorithm
using namespace std;

/*
// 일반 배열 정렬하기 //sort 함수

	bool compare(int a, int b) {
		return a > b;
	}

	int main(void) {
		int a[10] = { 9, 3, 5, 4, 1, 10, 8, 6, 7, 2 };
		sort(a, a + 10, compare);
		for (int i = 0; i < 10; i++) {
			cout << a[i] << ' ';
		}
	}
*/

class Student {
public:
	string name;
	int score;
	Student(string name, int score) {
		this->name = name;	this->score = score;
	}

	//// 정렬 기준은 '점수가 작은 순서' //연산자 오버로드 
	//bool operator <(Student& student) {
	//	return this->score < student.score;
	//}
};

bool compare(Student a, Student b) {
	return a.score > b.score;
}

int main(void)
{
	Student students[] = {
		Student("상욱", 93),
		Student("동빈", 90),
		Student("준기", 87),
		Student("일종", 92),
		Student("태은", 97)
	};

	sort(students, students + 5, compare);		//sort 함수

	for (int i = 0; i < 5; i++) {
		cout << students[i].name << ' ' << students[i].score << endl;
	}
}

//sort 함수의 기본 형태는 다음과 같다.
// #include <algorithm> 필요
// 
//sort(start, end)를 이용하면[start, end) 범위의 인자를 오름차순(기본값, default)으로 정렬해 준다.
//sort(start, end, compare)를 이용하면 사용자가 정한 함수(compare)를 기준으로 정렬을 하게 된다.
//sort(start, end, grearter<자료형>())를 이용하면 [start, end) 범위의 인자를 내림차순으로 정렬해 준다.


/*
//STL - vector

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<string, pair<int, int> > a, pair<string, pair<int, int> > b)
{
	if (a.second.first == b.second.first) // 점수가 동일하면 생년월일 느린사람(높은사람)순으로 정렬
	{	
		return a.second.second > b.second.second;
	}
	else	// 점수 내림차순
	{	
		return a.second.first > b.second.first;
	}
}
int main(void)
{
	vector<pair<string, pair<int, int> > > v;
	v.push_back(pair<string, pair<int, int> >("지훈", make_pair(90, 19910329)));
	v.push_back(pair<string, pair<int, int> >("건우", make_pair(98, 19990305)));
	v.push_back(pair<string, pair<int, int> >("슬기", make_pair(92, 19940210)));
	v.push_back(pair<string, pair<int, int> >("예린", make_pair(94, 19960903)));
	v.push_back(pair<string, pair<int, int> >("지수", make_pair(94, 19940221)));

	sort(v.begin(), v.end(), compare);

	for (int i = 0; i < 5; i++)
	{
		cout << v[i].first << '(' << v[i].second.second; cout << "):" << v[i].second.first << endl;
	}
	return 0;
}​
*/