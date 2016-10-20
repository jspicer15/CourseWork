#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Course
{
	public:
		Course(const string &name, const unsigned int number, const string &section): name_(name), number_(number), section_(section)
		{
			students_.push_back("Stephen");
			students_.push_back("Jeremy");
			students_.push_back("Taylor");
			cout << "Constructor" << endl;
		}

		~Course()
		{
			cout << "Destructor" << endl;
		}

		inline string name() const
		{
			return name_;
		}

		void display_students()
		{
			for(vector<string>::const_iterator it = students_.begin(); it != students_.end(); ++it)
			{
				cout << *it << endl;
			}
		}
	private:
		string name_;
		unsigned int number_;
		string section_;
		vector<string> students_;
};

int main(int argc, char* argv[])
{
	Course cs385("Algorithms", 385, "A");
	cout << cs385.name() << endl;
	Course *cs115 = new Course("Intro", 115, "A");
	cout << cs115->name() << endl;
	cs115->
	delete cs115;
}
