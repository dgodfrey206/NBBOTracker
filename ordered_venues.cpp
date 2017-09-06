#include "ordered_venues.hpp"

void OrderedVenues::clear()
{
  std::memset(venues_, 0, sizeof venues_);
}

OrderedVenues::Venue* OrderedVenues::FindVenueId(int8_t id) {
  for (size_t i = 0; i < size_; ++i)
  {
    if (venues_[i].id == id)
    {
      return &venues_[i];
    }
  }
  return NULL;
}

OrderedVenues::Venue* OrderedVenues::FindVenueQuantity(unsigned int quantity)
{
  Venue* pos = std::lower_bound(venues_, venues_ + size_, quantity);
  if (pos != venues_ + size_)
  {
    return pos;
  }
  return NULL;
}

// order by quantity
bool operator<(OrderedVenues::Venue const& v, unsigned int quantity)
{ return v.quantity < quantity; }
// order by quantity
bool operator<(unsigned int quantity, OrderedVenues::Venue const& v)
{ return quantity < v.quantity; }

void OrderedVenues::Remove(Venue* v)
{
  std::memmove(v, v + 1, (kMaxNumberVenues - size_) * sizeof(Venue));
  venues_[kMaxNumberVenues - 1].id = 0;
  venues_[kMaxNumberVenues - 1].quantity = 0;
  --size_;
}

void OrderedVenues::RemoveAll(int8_t id)
{
  for (Venue* vit = FindVenueId(id); vit != NULL; vit = FindVenueId(id))
  {
    Remove(vit);
  }
}

void OrderedVenues::Insert(unsigned int quantity, int8_t id)
{
    Venue* venuesEnd = venues_ + size_;
    // find the value in the sorted array
    
    Venue* pos = venuesEnd;
    for (size_t i = 0; i < size_; ++i)
    {
      if (quantity >= venues_[i].quantity)
      {
        pos = &venues_[i];
        break;
      }
    }

    if (pos != venuesEnd) // if there's no value lesser, then insert at front
    {
      if (size_ != 0) // if there are no elements then there's no point in copying
      {
        std::memmove(pos + 1, pos, (kMaxNumberVenues - size_ - 1) * sizeof(Venue)); // move the rest of the elements to the right
      }
      pos->quantity = quantity; // insert
      pos->id = id; // insert
    }
    else
    {
        Venue temp;
        temp.id = id;
        temp.quantity = quantity;
        venues_[size_] = temp; // if it's the smallest found, insert at end
    }
    ++size_;
}

int8_t* OrderedVenues::AddSorted(unsigned int quantity, int8_t id)
{
  Venue* vit = FindVenueId(id);
  if (quantity == 0) // if we want to delete
  {
    if (vit != NULL)
    {
      Remove(vit);
    }
  }
  else // otherwise
  {
      if (vit != NULL) // if the element is found and we don't want to delete it, then we're changing its quantity
      {
        int count = 1; // how many elements to insert
        for (; vit != NULL; vit = FindVenueId(id)) { // keep finding venues with their id equal to the parameter id
          Remove(vit); // remove them so we can add them in sorted order later
          ++count;
        }

        while (count--)
        {
          Insert(quantity, id); // insert sorted
        }
      }
      else if (size_ < kMaxNumberVenues) // if we want to change the priority
      {
        Insert(quantity, id);
      }
      else
      {
        return result_; // return if the array is full
      }
  }

  // both of the above cases, if control passes here, modify venue, so we copy again
  for (size_t i = 0; i < size_; ++i)
  {
      result_[i] = venues_[i].id;
  }

  std::memset(result_ + size_, 0, kMaxNumberVenues - size_);
  return result_;
}
