// Member.h
#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <unordered_map>

class AuctionSystem;
class Item;

class Member
{
private:
  std::string username;
  std::string password;
  std::string fullName;
  std::string phonenumber;
  std::string email;
  std::string IDtype;
  std::string IDnumber;
  int isAdmin;
  int itemsWonToDate;
  int CP;
  float rating;
  std::vector<Item *> activeItemListings;
  std::unordered_map<Item *, int> activeBids;
  std::vector<std::string> reviewsByOthers;

public:
  Member(std::string username = "", std::string password = "", std::string fullName = "",
         std::string phonenumber = "", std::string email = "", std::string IDtype = "",
         std::string IDnumber = "");

  void setUsername(std::string username);
  void setPassword(std::string password);
  void setFullName(std::string fullName);
  void setPhoneNumber(std::string phonenumber);
  void setEmail(std::string email);
  void setIDType(std::string IDtype);
  void setIDNumber(std::string IDnumber);
  void setCP(int CP);
  void setRating(float rating);
  void setIsAdmin();
  void setItemsWonToDate(int itemsWonToDate);

  std::string getUsername() const;
  std::string getPassword() const;
  std::string getFullName() const;
  std::string getPhoneNumber() const;
  std::string getEmail() const;
  std::string getIDType() const;
  std::string getIDNumber() const;
  int getCP() const;
  float getRating() const;
  int getIsAdmin();
  int getItemsWonToDate();

  std::vector<Item *> &getActiveItemListings();
  std::unordered_map<Item *, int> &getActiveBid();
  std::vector<std::string> &getReviewsByOthers();

  bool creditCheck(int newBidLimit);

  void viewDashBoard();
  void topUpCredit();
  void changePassword(AuctionSystem &auctionSystem);
  void changeUsername(AuctionSystem &auctionSystem);
  void proItemSearch(AuctionSystem &auctionSystem);
  void placeBid(AuctionSystem &auctionSystem);
  void Bid(AuctionSystem &auctionSystem);
  void removeBid(AuctionSystem &auctionSystem);
  void setItemRating();
  void reviewOther(AuctionSystem &auctionSystem);
  void showReviewsByOther();
  void viewAnyProfile(AuctionSystem &auctionSystem);
  void setAutoBidLimit(AuctionSystem &auctionSystem, int itemId, int bidLimit);
};

#endif // MEMBER_H