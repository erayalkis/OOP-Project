#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"

namespace seneca {

class Food : public Billable {
   bool m_ordered{false};
   bool m_child{false};
   char* m_customize{nullptr};

   void setCustomize(const char* text);

public:
   Food();
   Food(const Food& other);
   Food& operator=(const Food& other);
   ~Food();

   std::ostream& print(std::ostream& ostr = std::cout) const override;
   bool order() override;
   bool ordered() const override;
   std::ifstream& read(std::ifstream& file) override;
   double price() const override;
};

}

#endif // !SENECA_FOOD_H

