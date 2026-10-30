// Item.cpp
#include "Item.h"
#include "Member.h"
#include "AuctionSystem.h"
#include <iostream>

// constructer
Item::Item(std::string itemName, std::string category, std::string description, std::string endTime, int bidIncrement, float ratingScore, Member *owner)
    : itemName(itemName), category(category), description(description), endTime(endTime),
      bidIncrement(bidIncrement), ratingScore(ratingScore), highestBid(0), owner(owner), currentBidder("N/A"), itemId(0)
{
  static int IDForItems = 0; // create unique Id
  itemId = IDForItems++;
  if (owner != nullptr)
    owner->getActiveItemListings().push_back(this); // set owner of the item
  
}

// setter / getter

std::string Item::getItemName() { return itemName; }
void Item::setItemName(std::string newItemName) { itemName = newItemName; }

std::string Item::getCategory() { return category; }
void Item::setCategory(std::string newCategory) { category = newCategory; }

std::string Item::getDescription() { return description; }
void Item::setDescription(std::string newDescription) { description = newDescription; }

int Item::getBidIncrement() { return bidIncrement; }
void Item::setBidIncrement(int newBidIncrement) { bidIncrement = newBidIncrement; }

std::string Item::getEndTime() { return endTime; }
void Item::setEndTime(std::string newEndTime) { endTime = newEndTime; }

float Item::getRatingScore() { return ratingScore; }
void Item::setRatingScore(float newRatingScore) { ratingScore = newRatingScore; }

int Item::getHighestBid() { return highestBid; }
void Item::setHighestBid(int newHighestBid) { highestBid = newHighestBid; }

std::string Item::getCurrentBidder() { return currentBidder; }
void Item::setCurrentBidder(std::string newCurrentBidder) { currentBidder = newCurrentBidder; }

int Item::getItemId() { return itemId; }
void Item::setItemId(int newId) { itemId = newId; }

std::vector<Member *> Item::getBidders() { return bidders; }
void Item::setBidders(std::vector<Member *> newBidders) { bidders = newBidders; }
void Item::addBidders(Member *member) { bidders.push_back(member); }

Member *Item::getOwner() { return owner; }

void Item::setAutoBidLimit(Member *buyer, int limit) {
    autoBidLimits[buyer] = limit;
}

bool Item::hasAutoBidLimit(Member *buyer) const {
    return autoBidLimits.find(buyer) != autoBidLimits.end();
}

int Item::getAutoBidLimit(Member *buyer) const {
    auto it = autoBidLimits.find(buyer);
    if (it != autoBidLimits.end()) {
        return it->second;
    }
    return -1;
}

void Item::removeAutoBidLimit(Member *buyer) {
    autoBidLimits.erase(buyer);
}

bool Item::isBidLimitConflict(Member *buyer, int newBidLimit) {
    for (const auto &entry : autoBidLimits) {
        if (entry.second == newBidLimit && entry.first != buyer) {
            return true; // Conflict found
        }
    }
    return false; // No conflict
}

void Item::placeAutoBids() {
    for (auto &entry : autoBidLimits) {
        Member *buyer = entry.first;
        int limit = entry.second;

        // Check if the buyer's limit allows a bid increment
        if (highestBid + bidIncrement <= limit) {
            highestBid += bidIncrement;                 // Increment the highest bid
            currentBidder = buyer->getUsername();       // Update the current bidder
            buyer->getActiveBid()[this] = highestBid;   // Record the bid in the buyer's active bids
            std::cout << "Automatic bid placed by " << buyer->getUsername() 
                      << " for " << highestBid << " CP." << std::endl;
        } else {
          std::cout << buyer->getUsername() << " automactic bid stop!";
        }
    }
}