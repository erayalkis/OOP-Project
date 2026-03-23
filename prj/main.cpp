#include <iostream>
#include "Menu.h"
#include "Ordering.h"

using namespace std;
using namespace seneca;

int main() {
   Ordering ord("drinks.csv", "foods.csv");

   if (!ord) {
      cout << "Failed to open data files or the data files are corrupted!"
           << endl;
      return 0;
   }

   Menu appMenu("Seneca Restaurant ", "End Program");
   appMenu << "Order"
           << "Print Bill"
           << "Start a New Bill"
           << "List Foods"
           << "List Drinks";

   size_t selection{};
   while (true) {
      selection = appMenu.select();

      if (selection == 0) {
         if (ord.hasUnsavedBill()) {
            Menu confirm(
               "You have bills that are not saved, are you sue you want to exit?",
               "No");
            confirm << "Yes";

            if (confirm.select() == 1) return 0;
            continue;
         }
         break;
      }

      switch (selection) {
         case 1: {
            Menu orderMenu("Order Menu", "Back to main menu", 1);
            orderMenu << "Food" << "Drink";

            size_t orderSel{};
            do {
               orderSel = orderMenu.select();
               if (orderSel == 1) ord.orderFood();
               if (orderSel == 2) ord.orderDrink();
            } while (orderSel);
            break;
         }
         case 2:
            ord.printBill(cout);
            break;
         case 3:
            ord.resetBill();
            break;
         case 4:
            ord.listFoods();
            break;
         case 5:
            ord.listDrinks();
            break;
         default:
            break;
      }
   }

   return 0;
}

