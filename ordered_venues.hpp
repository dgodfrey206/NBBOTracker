static const std::size_t kMaxNumberVenues = 16;

class OrderedVenues {
public:
    struct Venue {
        int8_t id;
        unsigned int quantity;
    };

    OrderedVenues()
      : result_(),
        venues_(),
        size_()
    {
    }

    int8_t* AddSorted(unsigned int quantity, int8_t id);
    Venue* FindVenueId(int8_t id);
    Venue* FindVenueQuantity(unsigned int quantity);
    void clear();
private:
    void Remove(Venue* v);
    void RemoveAll(int8_t id);
    void Insert(unsigned int quantity, int8_t id);

    int8_t result_[kMaxNumberVenues + 1];
    Venue venues_[kMaxNumberVenues];
    size_t size_;
};
