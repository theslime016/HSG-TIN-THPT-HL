#include <bits/stdc++.h>
using namespace std;

int compile(string FILE)
{
  return system(("g++ -std=c++17 " + FILE + ".CPP -o " + FILE).c_str());
}

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);

  string NAME;
  int cases = 3;
  switch (cases)
  {
  case 1:
    NAME = "LIXI";
    break;
  case 2:
    NAME = "BIENSO";
    break;
  case 3:
    NAME = "TIEUTHU";
    break;
  case 4:
    NAME = "CANHDONG";
    break;
  }

  const int time = 100;
  string BRUTE = ("BRUTE_" + NAME).c_str();
  string GEN = ("GEN_" + NAME).c_str();
  string OUT = (NAME + ".OUT").c_str();
  string ANS = (NAME + ".ANS").c_str();

  compile(NAME);
  compile(BRUTE);
  compile(GEN);
  for (int run = 1; run <= time; run++)
  {
    cerr << "TEST: " << run << " - ";
    system(("powershell ./" + GEN).c_str());
    system(("powershell ./" + BRUTE).c_str());
    system(("powershell ./" + NAME).c_str());

    // int f = system(("powershell -Command \" Compare-Object (Get-Content " + OUT + ") (Get-Content " + ANS + ") \"").c_str());
    int f = system(("fc " + OUT + ' ' + ANS).c_str());

    if (f != 0)
    {
      cerr << "!!!!!!!!!";
      return 0;
    }
    else
    {
      cerr << "[AC]\n";
    }
  }

  return 0;
}