#include "ordered_venues.hpp"

class NBBOTracker
{
public:
  typedef OrderedVenues::Venue Venue;

  struct BBO
  {
      int ask_quantity_;
      double ask_price_;
      int bid_quantity_;
      double bid_price_;

      BBO() : ask_quantity_(), ask_price_(), bid_quantity_(), bid_price_() { }
  };

  NBBOTracker() : bid_order(), ask_order(), bbo_array(), size(), nbbo() { }
  void AddBid(int8_t, std::size_t, std::size_t);
  void AddAsk(int8_t, std::size_t, std::size_t);

  BBO NBBO() const;
private:
  OrderedVenues bid_order;
  OrderedVenues ask_order;
  BBO  bbo_array[kMaxNumberVenues];

  size_t size;
  BBO nbbo;
};
