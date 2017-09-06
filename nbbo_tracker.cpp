#include "nbbo_tracker.hpp"

// Find the highest bid, lowest offer. Sum the quantities of those venues.
// The NNBO is single object that contains the highest big and lowest offer in the BBO array
// bid_order is for ordering the venues, ask_order is for ordering the asks

void NBBOTracker::AddBid(int8_t id, std::size_t price, std::size_t qty)
{
  std::size_t xid = id % 16; // The id (character) converted back to an integer
  if (price == nbbo.bid_price_)
  {
    if (bbo_array[xid].bid_price_ == nbbo.bid_price_)
    {
      nbbo.bid_quantity_ -= bbo_array[xid].bid_quantity_;
    }
    nbbo.bid_quantity_ += qty;
    bid_order.AddSorted(id, qty);
  }
  else if (price < nbbo.bid_price_)
  {
    if (bbo_array[xid].bid_price_ == nbbo.bid_price_) {
      nbbo.bid_quantity_ -= qty;
    }
    if (nbbo.bid_quantity_ == 0) {
      // recalculate (for loop find max price & sum the qty)
      
      // Finding the maximum price
      BBO max = bbo_array[0];
      for (size_t i = 1; i < size; ++i)
      {
        if (bbo_array[i].bid_price_ < max.bid_price_)
        {
          max = bbo_array[i];
        }
      }

      // Summing up the quantities of the bbos with the same quantity as the venue with the highest price
      for (size_t i = 0; i < size; ++i)
      {
        if (bbo_array[i].bid_quantity_ == max.bid_quantity_)
        {
          nbbo.bid_quantity_ += bbo_array[i].bid_quantity_;
        }
      }
    }
    else if (price > nbbo.bid_price_)
    {
      nbbo.bid_price_ = price;
      nbbo.bid_quantity_ = qty;
      bid_order.clear();
      bid_order.AddSorted(id, qty);
    }
    bbo_array[xid].bid_quantity_ = qty;
    bbo_array[xid].bid_price_ = price;
  }

}

void NBBOTracker::AddAsk(int8_t id, std::size_t price, std::size_t qty)
{
  std::size_t xid = id % 16; // convert it to work with indicies
  if (price == nbbo.ask_price_)
  {
    if (bbo_array[xid].ask_price_ == nbbo.ask_price_)
    {
      nbbo.ask_quantity_ -= bbo_array[xid].ask_quantity_;
    }
    nbbo.ask_quantity_ += qty;
    ask_order.AddSorted(id, qty);
  }
  else if (price < bbo_array[xid].ask_price_)
  {
    if (bbo_array[xid].ask_price_ == nbbo.ask_price_)
    {
      nbbo.ask_quantity_ -= qty;
    }

    if (nbbo.ask_quantity_ == 0)
    {
      // Recaculate: For loop to find the maximum price, then sum up the quantities of the venues
    }
  }
  else if (price > nbbo.ask_price_)
  {
    nbbo.ask_price_ = price;
    nbbo.ask_quantity_ = qty;
    ask_order.clear();
    ask_order.AddSorted(id, qty);
  }
  bbo_array[xid].bid_quantity_ = qty;
  bbo_array[xid].bid_price_ = price;
}

NBBOTracker::BBO NBBOTracker::NBBO() const
{
    return nbbo;
}
