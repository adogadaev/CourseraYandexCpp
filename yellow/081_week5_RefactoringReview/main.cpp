#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
 public:
  explicit Human(string name, string job)
      : name_(move(name)), job_(move(job)) {
  }

  virtual void Walk(const string& destination) const {
    cout << job_ << ": " << name_ << " walks to: " << destination << endl;
  }

  string GetName() const {
    return name_;
  }

  string GetJob() const {
    return job_;
  }

 protected:
  string name_, job_;
};

class Student : public Human {
 public:
  explicit Student(string name, string favourite_song)
      : Human(move(name), "Student"), favourite_song_(move(favourite_song)) {
  }

  void Learn() const {
    cout << job_ << ": " << name_ << " learns" << endl;
  }

  void Walk(const string& destination) const override {
    Human::Walk(destination);
    SingSong();
  }

  void SingSong() const {
    cout << job_ << ": " << name_ << " sings a song: " << favourite_song_ << endl;
  }

 protected:
  string favourite_song_;
};

class Teacher : public Human {
 public:
  explicit Teacher(string name, string subject)
      : Human(move(name), "Teacher"), subject_(move(subject)) {
  }

  void Teach() const {
    cout << job_ << ": " << name_ << " teaches: " << subject_ << endl;
  }

 protected:
  string subject_;
};

class Policeman : public Human {
 public:
  explicit Policeman(string name)
      : Human(move(name), "Policeman") {
  }

  void Check(const Human& somebody) const {
    cout << job_ << ": " << name_ << " checks " << somebody.GetJob() << ". ";
    cout << somebody.GetJob() << "'s name is: " << somebody.GetName() << endl;
  }
};

void VisitPlaces(const Human& somebody, const vector<string>& places) {
  for (const auto& place : places) {
    somebody.Walk(place);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");

  s.Learn();
  t.Teach();
  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});

  return 0;
}
