#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void print(vector<string> const & v) {
  for (string const & s : v) {
    cout << s << endl;
  }
}

vector<string> split(string const & s) {
  vector<string> output;
  int i = 0;
  for (int j = 1; j < s.size(); j++) {
    if (s[j] == ' ') {
      output.push_back(s.substr(i, j - i));
      i = j + 1;
    }
  }
  if (i < s.size()) {
    output.push_back(s.substr(i, s.size() - i));
  }
  return output;
}

bool placeholder(string const & s) {
  return s[0] == '<';
}

class MergeFind {
  public:
    vector<set<string>> collect() {
      vector<set<string>> output;
      map<string, int> pos;
      for (auto ent : weight) {
        string x = ent.first, p = find(x);
        auto it = pos.find(p);
        if (it != pos.end()) {
          output[it->second].insert(x);
        } else {
          pos.insert(make_pair(p, output.size()));
          set<string> s;
          s.insert(x);
          s.insert(p);
          output.push_back(s);
        }
      }
      return output;
    }

    void merge(string const & a, string const & b) {
      string pa = find(a), pb = find(b);
      auto ita = weight.find(pa), itb = weight.find(pb);
      int wpa = ita != weight.end() ? ita->second : 1;
      int wpb = itb != weight.end() ? itb->second : 1;
      weight.insert(make_pair(pa, wpa));
      weight.insert(make_pair(pb, wpb));
      
      if (find(a) == find(b)) {
        return;        
      }

      if (wpa > wpb) {
        parent.insert(make_pair(pb, pa));
        weight.insert(make_pair(pa, wpa + wpb));
      } else {
        parent.insert(make_pair(pa, pb));
        weight.insert(make_pair(pb, wpa + wpb));
      }
    }

    string find(string const & a) {
      string curr = a;
      map<string, string>::iterator it;
      while (true) {
        it = parent.find(curr);
        if (it == parent.end()) {
          break;
        }
        curr = it->second;
      }
      return curr;
    }

  private:
    map<string, string> parent;
    map<string, int> weight;
};

string matched(string a, string b) {
  vector<string> splita = split(a), splitb = split(b);
  if (splita.size() != splitb.size()) {
    return "-";
  }

  MergeFind mf;
  for (int i = 0; i < splita.size(); i++) {
    string xa = splita[i], xb = splitb[i];
    if (placeholder(xa)) { xa += ":a"; }
    if (placeholder(xb)) { xb += ":b"; }
    mf.merge(xa, xb);
  }
  
  vector<set<string>> sets = mf.collect();
  map<string, string> mapping;
  for (set<string> const & s : sets) {
    string base = "";
    for (string const & x : s) {
      if (!placeholder(x)) {
        if (!base.empty() && (x != base)) {
          return "-";
        }
        base = x;
      }
    }
    if (base == "") {
      base = "dummy";
    }

    for (string x : s) {
      mapping.insert(make_pair(x, base));
    }
  }

  stringstream ss;
  bool first = true;
  for (string const & x : splita) {
    if (first) { first = false; }
    else { ss << " "; }

    string y = x;
    if (placeholder(x)) { y += ":a"; }
    ss << mapping.find(y)->second;
  }
  return ss.str();
}

int main() {
  string Nstr;
  getline(cin, Nstr);
  int N = stoi(Nstr);
  while (N--) {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    cout << matched(a, b) << endl;
  }
    
  return 0;
}
