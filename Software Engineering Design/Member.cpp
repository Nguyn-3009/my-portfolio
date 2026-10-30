// Member.cpp
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <limits>

#include "Member.h"
#include "Member.h"
#include "AuctionSystem.h"
#include "Item.h"

using namespace std;

Member::Member(std::string username, std::string password, std::string fullName,
               std::string phonenumber, std::string email, std::string IDtype,
               std::string IDnumber)
    : username(username), password(password), fullName(fullName), phonenumber(phonenumber),
      email(email), IDtype(IDtype), IDnumber(IDnumber), isAdmin(0), CP(0),
      rating(3.0), itemsWonToDate(0) {}

// setter
void Member::setUsername(std::string username) { this->username = username; }
void Member::setPassword(std::string password) { this->password = password; }
void Member::setFullName(std::string fullName) { this->fullName = fullName; }
void Member::setPhoneNumber(std::string phonenumber) { this->phonenumber = phonenumber; }
void Member::setEmail(std::string email) { this->email = email; }
void Member::setIDType(std::string IDtype) { this->IDtype = IDtype; }
void Member::setIDNumber(std::string IDnumber) { this->IDnumber = IDnumber; }
void Member::setCP(int CP) { this->CP = CP; }
void Member::setRating(float rating) { this->rating = rating; }
void Member::setIsAdmin() { this->isAdmin = 1; }
void Member::setItemsWonToDate(int itemsWonToDate) { this->itemsWonToDate = itemsWonToDate; }

// getter
std::string Member::getUsername() const { return username; }
std::string Member::getPassword() const { return password; }
std::string Member::getFullName() const { return fullName; }
std::string Member::getPhoneNumber() const { return phonenumber; }
std::string Member::getEmail() const { return email; }
std::string Member::getIDType() const { return IDtype; }
std::string Member::getIDNumber() const { return IDnumber; }
int Member::getCP() const { return CP; }
float Member::getRating() const { return rating; }
int Member::getIsAdmin() { return isAdmin; }
int Member::getItemsWonToDate() { return itemsWonToDate; }

// getter / setter
std::vector<Item *> &Member::getActiveItemListings() { return activeItemListings; }
std::unordered_map<Item *, int> &Member::getActiveBid() { return activeBids; }
std::vector<std::string> &Member::getReviewsByOthers() { return reviewsByOthers; }

bool Member::creditCheck(int newBidLimit)
{
  int money = this->CP;
  for (const auto &pair : activeBids)
  {
    money -= pair.second;
  }
  if (money - newBidLimit < 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

void Member::viewDashBoard()
{
  // dashboard
  cout << "Account Overview: " << this->username << endl;
  cout << "----------------------------------------" << endl;
  
  // active item listing
  cout << setw(25) << left << "Active Items Listings: " << this->activeItemListings.size() << "  |  " << setw(20) << left << "Active Bids: " << this->activeBids.size() << endl;
  cout << setw(25) << left << "Items won to date: " << this->getItemsWonToDate() << "  |  " << setw(20) << left << "Account Balance: " << this->CP << " CP" << endl;
  cout << endl;
  cout << "Your active items listings" << endl;
  cout << "--------------------------" << endl;

  cout << setw(3) << left << "No." << " | " << setw(20) << left << "Item ID" << " | " << setw(20) << left << "Item Name" << " | " << setw(20) << left << "Category" << " | " << setw(20) << left << "Highest Bid" << " | " << setw(20) << left << "Current Bidder" << " | " << setw(20) << left << "End Date Time" << endl;

  for (int i = 0; i < activeItemListings.size(); i++)
  {
    cout << setw(3) << left << i + 1 << " | " << setw(20) << left << activeItemListings[i]->getItemId() << " | " << setw(20) << left << activeItemListings[i]->getItemName() << " | " << setw(20) << left << activeItemListings[i]->getCategory() << " | " << setw(20) << left << activeItemListings[i]->getHighestBid() << " | " << setw(20) << left << activeItemListings[i]->getCurrentBidder() << " | " << setw(20) << left << activeItemListings[i]->getEndTime() << endl;
  }
  cout << endl;

  // active bids
  cout << "Your active bids" << endl;
  cout << "----------------" << endl;

  cout << setw(3) << left << "No." << " | " << setw(20) << left << "Item ID" << " | " << setw(20) << left << "Item Name" << " | " << setw(20) << left << "Category" << " | " << setw(20) << left << "Your bid" << " | " << setw(20) << left << "Highest Bid" << " | " << setw(20) << left << "End Date Time" << endl;

  int j = 0; // No. of bid
  // all active Bids
  for (const auto &pair : activeBids)
  {
    Item *itemPtr = pair.first; // Pointer to the Item
    int bidValue = pair.second; // Corresponding bid value

    cout << setw(3) << left << j + 1 << " | " << setw(20) << left << itemPtr->getItemId() << " | " << setw(20) << left << itemPtr->getItemName() << " | " << setw(20) << left << itemPtr->getCategory() << " | " << setw(20) << left << pair.second << " | " << setw(20) << left << itemPtr->getHighestBid() << " | " << setw(20) << left << itemPtr->getEndTime() << endl;
  }
  cout << endl;

  cout << "Reviews by others" << endl;
  cout << "-----------------" << endl;

  // show review by other
  for (int i = 0; i < reviewsByOthers.size(); i++)
  {
    cout << setw(3) << left << i + 1 << ". " << setw(20) << left << reviewsByOthers[i] << endl;
  }
  cout << endl;

  cout << "My rating" << endl;
  cout << "---------" << endl;

  // show current rating
  cout << "Rating: " << this->rating << endl;
}

void Member::topUpCredit()
{
  string pass;
  cout << "-----------------\n";
  cout << "Enter password : ";
  getline(cin, pass);

  if (pass != password)
  {
    cout << "Wrong pass word ! Can not top up credit" << endl; // password authority for top up credit
    return;
  }

  int addCP;
  std::cout << "Enter credit to top up: ";
  std::cin >> addCP;

  // Fix: Clear any leftover input in the buffer
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  CP += addCP;
  cout << "Credit successfully topped up. New balance: " << CP << " CP" << endl;
  cout << "-----------------\n";
}

void Member::changePassword(AuctionSystem &auctionSystem)
{
  cout << "-----------------\n";
  string newPassword;

  do
  {
    newPassword.clear();
    cout << "Enter new password : ";
    getline(cin, newPassword);
    
    // change password with policy
  } while (!auctionSystem.isValidPassword(newPassword));
}

void Member::changeUsername(AuctionSystem &auctionSystem)
{
  string newUsername;

  do
  {
    newUsername.clear();
    cout << "Enter new username : ";
    getline(cin, newUsername);

    // change username with no similarity from other users
  } while (!auctionSystem.isUsernameTaken(newUsername));
  cout << "-----------------\n";
}

void Member::proItemSearch(AuctionSystem &auctionSystem)
{
  cout << "-----------------\n";
  string itemName = "";
  string category = "";
  int minCP = 0;
  int maxCP = 10000; // Default range

  cout << "Enter item name : ";
  getline(cin, itemName);

  cout << "Enter category : ";
  getline(cin, category);

  cout << "Enter minimum CP : ";
  cin >> minCP;

  cout << "Enter maximum CP : ";
  cin >> maxCP;

  cout << "Matching Items : " << endl;
  cout << "-----------------------------------------------" << endl;

  for (Item *item : auctionSystem.getItems())
  {
    if ((itemName.empty() || item->getItemName().find(itemName) != string::npos) && // search by keyword name
        (category.empty() || item->getCategory().find(category) != string::npos) && // search by keyword category
        item->getRatingScore() <= this->rating && // ensure auitable rating
        item->getHighestBid() >= minCP &&
        item->getHighestBid() <= maxCP) //range of price
    {
      // show item info
      cout << setw(20) << left << "Name: " << item->getItemName() << endl;
      cout << setw(20) << left << "Category: " << item->getCategory() << endl;
      cout << setw(20) << left << "Description: " << item->getDescription() << endl;
      cout << setw(20) << left << "End Date Time: " << item->getEndTime() << endl;
      cout << setw(20) << left << "Highest Bid: " << item->getHighestBid() << endl;
      cout << setw(20) << left << "Current Bidder: " << item->getCurrentBidder() << endl;
      cout << setw(20) << left << "Item Id: " << item->getItemId() << endl;
      cout << "-----------------------------------------------" << endl;
    }
  }
  cout << "-----------------\n";
}

void Member::placeBid(AuctionSystem &auctionSystem)
{
  cout << "-----------------\n";
  string itemName;
  string category;
  string description;
  string endTime;
  int bidIncrement;
  float ratingScore;
  
  // prompt input for item info
  cout << "Enter item name: ";
  getline(cin, itemName);

  cout << "Enter end date time: ";
  getline(cin, endTime);

  cout << "Enter category: ";
  getline(cin, category);

  cout << "Enter description: ";
  getline(cin, description);

  cout << "Enter require rating: ";
  cin >> ratingScore;

  cout << "Enter increment: ";
  cin >> bidIncrement;

  Item *newItem = new Item(itemName, category, description, endTime, bidIncrement, ratingScore, this);

  auctionSystem.addItem(newItem); // add item to system
  cout << "-----------------\n";
}

void Member::Bid(AuctionSystem &auctionSystem) {
  cout << "-----------------\n";
    int itemId;

    // Prompt the user to select an item by ID
    std::cout << "Enter item ID to bid on: ";
    std::cin >> itemId;

    // Find the target item
    Item *targetItem = nullptr;
    for (Item *item : auctionSystem.getItems()) {
        if (item->getItemId() == itemId) { // Match the user-provided ID
            targetItem = item;
            break;
        }
    }

    // If no matching item is found, handle the error
    if (targetItem == nullptr) {
        std::cerr << "No item found with the specified ID." << std::endl;
        return;
    }

    // Display item details
    std::cout << "Item details:" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Name: " << targetItem->getItemName() << std::endl;
    std::cout << "Category: " << targetItem->getCategory() << std::endl;
    std::cout << "Description: " << targetItem->getDescription() << std::endl;
    std::cout << "End Date: " << targetItem->getEndTime() << std::endl;
    std::cout << "Highest Bid: " << targetItem->getHighestBid() << std::endl;
    std::cout << "Current Bidder: " << targetItem->getCurrentBidder() << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    // Prompt for the bid amount
    int yourBid;
    std::cout << "Enter your bid: ";
    std::cin >> yourBid;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Check if the user has enough credit points
    if (!this->creditCheck(yourBid)) {
        std::cerr << "Not enough credit points for the bid." << std::endl;
        return;
    }

    // Ensure the bid meets the bid increment requirement
    if (yourBid < targetItem->getHighestBid() + targetItem->getBidIncrement()) {
        std::cerr << "Your bid must be at least " 
                  << targetItem->getBidIncrement() << " CP higher than the current highest bid (" 
                  << targetItem->getHighestBid() << ")." << std::endl;
        return;
    }

    // Place the manual bid
    targetItem->addBidders(this);
    this->getActiveBid()[targetItem] = yourBid;
    targetItem->setHighestBid(yourBid);
    targetItem->setCurrentBidder(this->getUsername());

    // Trigger automatic bidding after the manual bid
    targetItem->placeAutoBids();
    cout << "-----------------\n";
}

void Member::setAutoBidLimit(AuctionSystem &auctionSystem, int itemId, int bidLimit) {
  cout << "-----------------\n";
    Item *targetItem = nullptr;
    for (Item *item : auctionSystem.getItems()) {
        if (item->getItemId() == itemId) {
            targetItem = item;
            break;
        }
    }
    if (targetItem == nullptr) {
        std::cerr << "Item not found." << std::endl;
        return;
    }

    if (!targetItem->isBidLimitConflict(this, bidLimit)) {
        targetItem->setAutoBidLimit(this, bidLimit);
        std::cout << "Automatic bid limit set successfully." << std::endl;
    } else {
        std::cerr << "Bid limit conflict detected. Please choose a different limit." << std::endl;
    }
    cout << "-----------------\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Member::removeBid(AuctionSystem &auctionSystem)
{
  cout << "-----------------\n";
  // show menu of item, which one you want to delete from active item listing ?
  cout << setw(3) << left << "No." << " | " << setw(20) << left << "Item ID" << " | " << setw(20) << left << "Item Name" << " | " << setw(20) << left << "Category" << " | " << setw(20) << left << "Highest Bid" << " | " << setw(20) << left << "End Date Time" << endl;
  for (int i = 0; i < activeItemListings.size(); i++)
  {
    cout << setw(3) << left << i + 1 << " | " << setw(20) << left << activeItemListings[i]->getItemId() << " | " << setw(20) << left << activeItemListings[i]->getItemName() << " | " << setw(20) << left << activeItemListings[i]->getCategory() << " | " << setw(20) << left << activeItemListings[i]->getHighestBid() << " | " << setw(20) << left << activeItemListings[i]->getEndTime() << endl;
  }
  cout << endl;

  int position;
  do
  {
    cout << "Enter item position (No.) on your active item list : ";
    cin >> position;

    if (position > this->getActiveItemListings().size())
    {
      cerr << "There is no item at that position" << endl;
    }
  } while (position > this->getActiveItemListings().size());

  if (this->activeItemListings[position - 1]->getBidders().size() != 0)
  {
    cerr << "There is people bidding on this item" << endl; // if theres people bidding on the item, remove item not allowed for seller
    return;
  }

  // proceed removal
  auctionSystem.removeItem(this->activeItemListings[position - 1]);
  this->activeItemListings.erase(this->activeItemListings.begin() + position - 1);

  cout << "Bid removed successfully!" << endl;
  cout << "-----------------\n";
}

void Member::setItemRating()
{
  cout << "-----------------\n";
  int itemId;
  Item *ratedItem = nullptr;

  // menu to look up for which item will change rating score
  cout << setw(3) << left << "No." << " | " << setw(20) << left << "Item ID" << " | " << setw(20) << left << "Item Name" << " | " << setw(20) << left << "Category" << " | " << setw(20) << left << "Highest Bid" << " | " << setw(20) << left << "Current Bidder" << " | " << setw(20) << left << "End Date Time" << endl;
  for (int i = 0; i < activeItemListings.size(); i++)
  {
    cout << setw(3) << left << i + 1 << " | " << setw(20) << left << activeItemListings[i]->getItemId() << " | " << setw(20) << left << activeItemListings[i]->getItemName() << " | " << setw(20) << left << activeItemListings[i]->getCategory() << " | " << setw(20) << left << activeItemListings[i]->getHighestBid() << " | " << setw(20) << left << activeItemListings[i]->getCurrentBidder() << " | " << setw(20) << left << activeItemListings[i]->getEndTime() << endl;
  }
  cout << endl;

  do
  {
    cout << "Enter items ID on the your active item listing ( above ) to set rating for it : "; // choose item
    cin >> itemId;

    for (Item *item : this->getActiveItemListings())
    {
      if (item->getItemId() == itemId)
      {
        ratedItem = item;
      }
    }

    if (ratedItem == nullptr)
    {
      cout << "No item found" << endl;
    }
  } while (ratedItem == nullptr);

  // proceed change rating score

  float ratingScore;
  cout << "Enter new rating score for that item : ";
  cin >> ratingScore;

  ratedItem->setRatingScore(ratingScore);
  cout << "Rated Item successfully" << endl;
  cout << "-----------------\n";
}

void Member::reviewOther(AuctionSystem &auctionSystem)
{
  cout << "-----------------\n";
  string username;

  do
  {
    username.clear();

    cout << "Who you want to review : "; // choose person to review
    getline(cin, username);

    if (!auctionSystem.checkUserName(username)) // make sure the person existed
    {
      cerr << "User not existed" << endl;
    }

  } while (!auctionSystem.checkUserName(username));

  string review;
  cout << "Enter review : "; 
  getline(cin, review);

  float rating;
  cout << "Rate this person : ";
  cin >> rating;

  for (Member *member : auctionSystem.getMembers())
  {
    if (member->getUsername() == username)
    {
      if (member->getReviewsByOthers().size() != 0)
      {
        float newRating = member->getReviewsByOthers().size() * member->getRating();
        member->getReviewsByOthers().push_back(review); // add review

        newRating = (newRating + rating) / member->getReviewsByOthers().size(); // calculate average rating score from all review
        member->setRating(newRating);
      }
      else
      {
        member->getReviewsByOthers().push_back(review);

        float newRating = rating;
        newRating = (newRating + 3) / 2; // calculte average rating if there has never been anyone rate this person yet
        member->setRating(newRating);
      }
    }
  }

  return;
}

void Member::showReviewsByOther()
{
  int i = 1;
  cout << "Reviews by other : " << endl;
  cout << "-------------------" << endl;

  for (string review : this->reviewsByOthers) // see all review
  {
    cout << setw(3) << left << i << '.' << setw(30) << left << review << endl;
  }
}

void Member::viewAnyProfile(AuctionSystem &auctionSystem)
{
  string username;

  if (this->isAdmin != 1) // admin privelege
  {
    return;
  }

  do
  {
    username.clear();
    cout << "Enter username ot view his / her profile : ";
    getline(cin, username); // get username

    if (!auctionSystem.checkUserName(username))
      cerr << "No user found :<" << endl; // output error when no user has username as such
  } while (!auctionSystem.checkUserName(username));

  for (Member *member : auctionSystem.getMembers())
  {
    if (member->getUsername() == username) // view account using username
    {
      member->viewDashBoard();
      break;
    }
  }
  cout << "-----------------\n";
}