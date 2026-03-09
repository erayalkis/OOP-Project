/***********************************************************************
// OOP244 Project, milestone 3 : tester program (simplified, no virtuals)
***********************************************************************/
#include <iostream>
#include <fstream>
#include "Drink.h"
#include "Food.h"
using namespace seneca;
using namespace std;

void DrinkTester();
void FoodTester();
void dumpFile(const char* fn);

// Two simple overloads instead of one function with base class reference
void runTest(Drink& D, ifstream& file, ofstream& outfile) {
   cout << endl << "Checking Virtuals: " << endl;
   while (file) {
      D.read(file);
   }
   D.print() << endl;
   D.print(outfile) << endl;
   cout << "Price: " << D.price() << endl;
   cout << (D.ordered() ? "Ordered" : "Not Ordered") << endl;
   cout << "Enter the following:\n2<ENTER>\n<ENTER>(only for food)\n=========>" << endl;
   D.order();
   cout << (D.ordered() ? "Ordered" : "Not Ordered") << endl;
}

void runTest(Food& F, ifstream& file, ofstream& outfile) {
   cout << endl << "Checking Virtuals: " << endl;
   while (file) {
      F.read(file);
   }
   F.print() << endl;
   F.print(outfile) << endl;
   cout << "Price: " << F.price() << endl;
   cout << (F.ordered() ? "Ordered" : "Not Ordered") << endl;
   cout << "Enter the following:\n2<ENTER>\n<ENTER>(only for food)\n=========>" << endl;
   F.order();
   cout << (F.ordered() ? "Ordered" : "Not Ordered") << endl;
}

void print(Drink D) {
   D.print() << endl;
}
void print(Food F) {
   F.print() << endl;
}

void dumpFile(const char* fn) {
   ifstream f(fn);
   char ch;
   cout << fn << ": ==============>" << endl;
   while (f) {
      if (f.get(ch)) cout << ch;
   }
   cout << "<==============" << endl;
}

int main() {
   cout << "Testing Drink Class=============================" << endl;
   DrinkTester();
   cout << "Testing Food Class=============================" << endl;
   FoodTester();
   dumpFile("drinkout.csv");
   dumpFile("foodout.csv");
   return 0;
}

void DrinkTester() {
   cout << "Drink Tester!" << endl;
   Drink D1, D2;
   ifstream file("drinks.csv");
   ofstream fileout("drinkout.csv");
   if (file) {
      double total = 0;
      D1.read(file);
      D2.read(file);
      cout << D1 << endl << D2 << endl;
      print(D1);
      print(D2);
      if (D1.ordered()) {
         cout << "Drinks by default are not ordered!" << endl;
      }
      else {
         cout << "Enter the folowing:\n1<ENTER>\n2<ENTER>\n3<ENTER>\n4<ENTER>\n0<ENTER>\n=========>" << endl;
         while (D2.order()) {
            print(D2);
            total += D2;
         }
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "Total = " << total << endl;
      }
      if (D2.ordered()) {
         cout << "When back is selected, Drink must be set to not-ordered!" << endl;
      }
      cout << "Enter the folowing:\n2<ENTER>\n=========>" << endl;
      D2.order();
      D1 = D2;
      if (D1.ordered() && D2.ordered()) {
         print(D1);
         total = total + D1;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "Total = " << total << endl;
      }
      else {
         cout << D1 << " and " << D2 << " should be in ordered status!" << endl;
      }
      runTest(D1, file, fileout);
   }
   else {
      cout << "drinks.csv is missing!" << endl;
   }
}

void FoodTester() {
   cout << "Food Tester!" << endl;
   Food F1, F2;
   ifstream file("foods.csv");
   ofstream fileout("foodout.csv");
   if (file) {
      double total = 0;
      F1.read(file);
      F2.read(file);
      cout << F1 << endl << F2 << endl;
      print(F1);
      print(F2);
      if (F1.ordered()) {
         cout << "Food by default is not ordered!" << endl;
      }
      else {
         cout << "Enter the folowing:\n1<ENTER>\nwell done\n2<ENTER>\n<ENTER>\n0<ENTER>\n=========>" << endl;
         while (F2.order()) {
            print(F2);
            total += F2;
         }
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "Total = " << total << endl;
      }
      if (F2.ordered()) {
         cout << "When back is selected, Frink must be set to not-ordered!" << endl;
      }
      cout << "Enter the folowing:\n2<ENTER>\n<ENTER>\n=========>" << endl;
      F2.order();
      F1 = F2;
      if (F1.ordered() && F2.ordered()) {
         print(F1);
         total = total + F1;
         cout.setf(ios::fixed);
         cout.precision(2);
         cout << "Total = " << total << endl;
      }
      else {
         cout << F1 << " and " << F2 << " should be in ordered status!" << endl;
      }
      runTest(F1, file, fileout);
   }
   else {
      cout << "foods.csv is missing!" << endl;
   }
}
