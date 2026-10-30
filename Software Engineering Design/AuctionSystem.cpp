// AuctionSystem.cpp

#include <iostream>

#include "AuctionSystem.h"
#include "Member.h"
#include "Item.h"

using namespace std;

// getter / setter
std::vector<Item *> &AuctionSystem::getItems() { return items; }
std::vector<Member *> &AuctionSystem::getMembers() { return members; }

// check whether username is duplicated or not
bool AuctionSystem::isUsernameTaken(const std::string &username)
{
  for (Member *member : this->members)
  {
    if (member->getUsername() == username)
    {
      cout << "username is taken" << endl;
      return true;
    }
  }
  return false;
}

// password policy
bool AuctionSystem::isValidPassword(const std::string &password)
{
  if (password.length() < 8)
  {
    cerr << "Password must be at least 8 characters long\n";
    return false;
  }
  if (!regex_search(password, regex("[A-Z]")))
  {
    cerr << "Password must contain at least one uppercase letter\n";
    return false;
  }
  if (!regex_search(password, regex("[a-z]")))
  {
    cerr << "Password must contain at least one lowercase letter\n";
    return false;
  }
  if (!regex_search(password, regex("[0-9]")))
  {
    cerr << "Password must contain at least one digit\n";
    return false;
  }
  if (!regex_search(password, regex("[^A-Za-z0-9]")))
  {
    cerr << "Password must contain at least one special character\n";
    return false;
  }
  return true;
}

// check whether the username is existed or not
bool AuctionSystem::checkUserName(std::string username)
{
  for (Member *member : this->getMembers())
  {
    if (member->getUsername() == username)
    {
      return true;
    }
  }

  return false;
}

void AuctionSystem::saveData(const std::string &filename)
{
  std::ofstream outFile(filename);
  if (!outFile.is_open())
  {
    std::cerr << "Error opening file for saving: " << filename << std::endl;
    return;
  }

  // Save items
  outFile << items.size() << "\n";
  for (const auto &item : items)
  {
    outFile << item->getItemName() << "\n";
    outFile << item->getCategory() << "\n";
    outFile << item->getDescription() << "\n";
    outFile << item->getEndTime() << "\n";
    outFile << item->getCurrentBidder() << "\n";
    outFile << item->getHighestBid() << "\n";
    outFile << item->getBidIncrement() << "\n";
    outFile << item->getRatingScore() << "\n";
    outFile << item->getItemId() << "\n";
    outFile << (item->getOwner() ? item->getOwner()->getUsername() : "N/A") << "\n";

    // Save bidders
    outFile << item->getBidders().size() << "\n";
    for (const auto &bidder : item->getBidders())
    {
      outFile << bidder->getUsername() << "\n";
    }
  }

  // Save members
  outFile << members.size() << "\n";
  for (const auto &member : members)
  {
    outFile << member->getUsername() << "\n";
    outFile << member->getPassword() << "\n";
    outFile << member->getFullName() << "\n";
    outFile << member->getPhoneNumber() << "\n";
    outFile << member->getEmail() << "\n";
    outFile << member->getIDType() << "\n";
    outFile << member->getIDNumber() << "\n";
    outFile << member->getIsAdmin() << "\n";
    outFile << member->getItemsWonToDate() << "\n";
    outFile << member->getCP() << "\n";
    outFile << member->getRating() << "\n";

    // Save reviews
    outFile << member->getReviewsByOthers().size() << "\n";
    for (const auto &review : member->getReviewsByOthers())
    {
      outFile << review << "\n";
    }
  }

  outFile.close();
  std::cout << "Data saved to " << filename << std::endl;
}

void AuctionSystem::loadData(const std::string &filename)
{
  std::ifstream inFile(filename);
  if (!inFile.is_open())
  {
    std::cerr << "Error opening file for loading: " << filename << std::endl;
    return;
  }

  // Load items
  size_t itemCount;
  inFile >> itemCount;
  inFile.ignore();
  for (size_t i = 0; i < itemCount; ++i)
  {
    std::string name, category, description, endTime, currentBidder, ownerUsername;
    int highestBid, bidIncrement, itemId;
    float ratingScore;

    std::getline(inFile, name);
    std::getline(inFile, category);
    std::getline(inFile, description);
    std::getline(inFile, endTime);
    std::getline(inFile, currentBidder);
    inFile >> highestBid >> bidIncrement >> ratingScore >> itemId;
    inFile.ignore();
    std::getline(inFile, ownerUsername);

    // Link owner
    Member *owner = nullptr;
    if (ownerUsername != "N/A")
    {
      for (Member *member : members)
      {
        if (member->getUsername() == ownerUsername)
        {
          owner = member;
          break;
        }
      }
    }

    Item *item = new Item(name, category, description, endTime, bidIncrement, ratingScore, owner);
    item->setCurrentBidder(currentBidder);
    item->setHighestBid(highestBid);
    item->setItemId(itemId);

    // Load bidders
    size_t bidderCount;
    inFile >> bidderCount;
    inFile.ignore();
    for (size_t j = 0; j < bidderCount; ++j)
    {
      std::string bidderUsername;
      std::getline(inFile, bidderUsername);
      for (Member *member : members)
      {
        if (member->getUsername() == bidderUsername)
        {
          item->addBidders(member);
          break;
        }
      }
    }

    items.push_back(item);
  }

  // Load members
  size_t memberCount;
  inFile >> memberCount;
  inFile.ignore();
  for (size_t i = 0; i < memberCount; ++i)
  {
    std::string username, password, fullName, phonenumber, email, IDtype, IDnumber;
    int isAdmin, itemsWonToDate, CP;
    float rating;

    std::getline(inFile, username);
    std::getline(inFile, password);
    std::getline(inFile, fullName);
    std::getline(inFile, phonenumber);
    std::getline(inFile, email);
    std::getline(inFile, IDtype);
    std::getline(inFile, IDnumber);
    inFile >> isAdmin >> itemsWonToDate >> CP >> rating;
    inFile.ignore();

    Member *member = new Member(username, password, fullName, phonenumber, email, IDtype, IDnumber);
    member->setIsAdmin();
    member->setItemsWonToDate(itemsWonToDate);
    member->setCP(CP);
    member->setRating(rating);

    // Load reviews
    size_t reviewCount;
    inFile >> reviewCount;
    inFile.ignore();
    for (size_t j = 0; j < reviewCount; ++j)
    {
      std::string review;
      std::getline(inFile, review);
      member->getReviewsByOthers().push_back(review);
    }

    members.push_back(member);
  }

  inFile.close();
  std::cout << "Data loaded from " << filename << std::endl;
}

// add member
void AuctionSystem::addMember(Member *member)
{
  members.push_back(member);
}

// add item
void AuctionSystem::addItem(Item *item)
{
  items.push_back(item);
}

// remove item
void AuctionSystem::removeItem(Item *item)
{
  for (int i = 0; i < this->getItems().size(); i++)
  {
    if (this->getItems()[i] == item)
      this->getItems().erase(this->getItems().begin() + i);
  }
}

// make a member become admin
void AuctionSystem::turnAdmin(Member *member)
{
  member->setIsAdmin();
}
