// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include <unordered_map>

class AuctionSystem;
class Member;

class Item
{
private:
  std::string itemName;
  std::string category;
  std::string description;
  std::string endTime;
  std::string currentBidder;
  std::vector<Member *> bidders; // people that are biding on this items
  std::unordered_map<Member *, int> autoBidLimits;
  Member *owner;
  int bidIncrement;
  float ratingScore;
  int itemId;
  int highestBid;

public:
  // constructor
  Item(std::string itemName = "", std::string category = "", std::string description = "",
       std::string endTime = "", int bidIncrement = 0, float ratingScore = 0,
       Member *owner = nullptr);

  // setter / getter

  std::string getItemName();
  void setItemName(std::string newItemName);

  std::string getCategory();
  void setCategory(std::string newCategory);

  std::string getDescription();
  void setDescription(std::string newDescripton);

  int getBidIncrement();
  void setBidIncrement(int newBidIncrement);

  std::string getEndTime();
  void setEndTime(std::string newEndTime);

  float getRatingScore();
  void setRatingScore(float newRatingScore);

  int getHighestBid();
  void setHighestBid(int newHighestBid);

  std::string getCurrentBidder();
  void setCurrentBidder(std::string newCurrentBidder);

  int getItemId();
  void setItemId(int Id);

  Member *getOwner();
  std::vector<Member *> getBidders();
  void setBidders(std::vector<Member *> newBidders);
  void addBidders(Member *member);

  bool isBidLimitConflict(Member *buyer, int newBidLimit);
  void placeAutoBids();

  
  void setAutoBidLimit(Member *buyer, int limit);
  bool hasAutoBidLimit(Member *buyer) const;
  
  int getAutoBidLimit(Member *buyer) const;
  void removeAutoBidLimit(Member *buyer);
};

#endif // ITEM_H